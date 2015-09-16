#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netdb.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <dirent.h>
#include "assert.h"

void showstring(char *cadena, int lenght){

	printf("cadena: \"%s\" longitud: %i\n",cadena, lenght );
	int i= 0;
	for(i = 0; i<=lenght;++i){
		printf("Elemento %i  : %i\n",i, (int)cadena[i] );
	}

}

#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))


int main(int argc, char ** argv){

	if (argc != 3)
	{
		printf("Error de uso\n");
		return -1;
	}


	
	struct in_addr inaddr;


	struct addrinfo informacion;
	struct addrinfo *resultado;

	informacion.ai_flags = AI_PASSIVE;
	informacion.ai_family = AF_UNSPEC;
	informacion.ai_socktype = SOCK_DGRAM;
	informacion.ai_protocol = 0;
	//informacion.ai_addrlen = 256;
	informacion.ai_addr = NULL;
	informacion.ai_canonname = NULL;
	informacion.ai_next = NULL;

	if(getaddrinfo(argv[1],argv[2],&informacion,&resultado) != 0){
			printf("Error al obtener direcciones\n");
			return -1;
		} 


	

	int sock = socket(resultado->ai_family, SOCK_DGRAM, resultado->ai_protocol);

	if(sock == -1){
		printf("Fallo al crear el socket\n");
		return -1;
	}

	int on = 1;
	int off = 0;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void*)&on,sizeof(int));
	setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY, (void*)&off,sizeof(int));



	if (bind(sock, resultado->ai_addr, resultado->ai_addrlen )){
		printf("Error en bind\n");
		return -1;
	}

	freeaddrinfo(resultado);

	printf("Socket binded\n");

	char mensaje[256] = "";
	struct sockaddr_storage msg;
	char hostname[NI_MAXHOST+1]= "";
	char port[NI_MAXSERV+1]= "";

	socklen_t msg_len = sizeof(msg);

	while(mensaje[0] != 'q'){

		ssize_t tammsg = recvfrom(sock,&mensaje, 256*sizeof(char), 0, &msg,&msg_len); 

		
		if (tammsg != -1){

			getnameinfo(&msg, msg_len,hostname,NI_MAXHOST+1, port,NI_MAXSERV+1,0);
			
			printf("Recibidos %i bytes de %s , puerto: %s\n",tammsg, &hostname, &port );

			if(mensaje[0] == 't'){

				time_t t;
				time(&t);
				char hora[100];
				strcpy(hora, ctime(&t));
				printf("%s\n", hora );
				if (-1 == sendto(sock, hora, strlen(hora)+1, 0, &msg, msg_len))
					printf("We have a problem\n");
				printf("Mandando mensaje de hora\n");


			}
			else if (mensaje[0] == 'l' && mensaje[1] == 's'){
				char ruta[256] = "";
				sscanf(mensaje,"ls %s", ruta);
				printf("%s\n", ruta);
				DIR * dir = opendir(ruta);
				struct dirent *actual;
				if (dir == NULL){
					printf("Directorio no valido\n");
				}
				else{
									
					do{
						actual = readdir(dir);	
						if(actual != NULL){
							char *abspath = malloc(sizeof(char)*(strlen(ruta) + strlen(actual->d_name) +3));
							strcpy(abspath, ruta);
							strcat(abspath,"/");
							strcat(abspath,actual->d_name);
							

							struct stat fichero;
							if(-1 == stat(abspath,&fichero)){
								printf("Error en stat\n");
								free(abspath);
								return -1;
							}
							
							char datos[512] = "";
							//char *nombres = malloc(128*sizeof(char));
							char nombres[128] = "";
							strcpy(nombres,actual->d_name);
							//por si acaso el nombre de fichero es muy largo
							assert(strlen(actual->d_name) < ARRAY_LENGTH(nombres)-1);
							strcat(nombres, "\n");
							showstring(nombres,strlen(nombres));


							if(S_ISREG(fichero.st_mode)){
								if(S_IXUSR & fichero.st_mode)
									strcat(datos,"*");
								printf("Fichero regular\n");
							
							}
							if(S_ISDIR(fichero.st_mode)){
								printf("Directorio\n");
							
							}
							if(S_ISLNK(fichero.st_mode)){
								printf("Enlace simbolico\n");
								char *linkname = malloc(fichero.st_size+1);
								readlink(abspath,linkname, fichero.st_size+1);

								if (-1 == sendto(sock, linkname, strlen(linkname)+1, 0, &msg, msg_len))
									printf("We have a problem, yeah\n");

								free(linkname);
							
							}
							else if (-1 == sendto(sock, nombres, ARRAY_LENGTH(nombres), 0, &msg, msg_len))
									printf("We have a problem, yeah\n");
							printf("Mandando mensaje de fecha\n");


							//free(nombres);
							free(abspath);

						}

						

					}while(actual!=NULL);

					closedir(dir);

				}


			}
			else if (mensaje[0] == 'q'){
					printf("Saliendo\n");
				}
		

			}
			else
				printf("Fallo de mensaje: %i, %s\n", tammsg, mensaje);

	}
	close(sock);

	return 0;


}