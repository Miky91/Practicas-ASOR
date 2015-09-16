#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>

int main(int argc, char ** argv){

	if (argc != 2)
	{
		printf("Error de uso\n");
		return -1;
	}

	


	
	struct in_addr inaddr;


	struct addrinfo informacion;
	struct addrinfo *resultado;

	informacion.ai_flags = AI_PASSIVE;
	informacion.ai_family = AF_UNSPEC;
	informacion.ai_socktype = SOCK_STREAM;
	informacion.ai_protocol = 0;
	//informacion.ai_addrlen = 256;
	informacion.ai_addr = NULL;
	informacion.ai_canonname = NULL;
	informacion.ai_next = NULL;

	if(getaddrinfo("::",argv[1],&informacion,&resultado) != 0){
			printf("Error al obtener direcciones\n");
			return -1;
		} 




	int sock = socket(resultado->ai_family, SOCK_STREAM, resultado->ai_protocol);

	if(sock == -1){
		printf("Socket caca\n");
		return -1;
	}

	int on = 1;
	int off = 0;

	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void*)&on,sizeof(int));
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void*)&off,sizeof(int));


	if (bind(sock, resultado->ai_addr, resultado->ai_addrlen ) == -1){
		printf("Error en bind\n");
		return -1;
	}

	printf("Socket binded\n");


	freeaddrinfo(resultado);

	if (listen(sock,12) == -1){
		printf("Error en listen\n");
		return -1;
	}

	char buf[256] = "";
	struct sockaddr_storage msg;
	socklen_t msglen = sizeof(msg);


	

		int aceptado = accept(sock,&msg, &msglen );

		if(aceptado == -1){
			printf("Error al aceptar la conexion\n");
			return -1;
		}

		char hostname[NI_MAXHOST+1] = "";
		char port[NI_MAXSERV+1] = "";
		//char mensaje[256] = "";

		if(-1 == getnameinfo(&msg,msglen,hostname, NI_MAXHOST+1, port, NI_MAXSERV+1,0)){
			printf("Error al obtener nombre de host y puerto\n");
		}
		printf("Conexion desde  %s  puerto  %s\n", hostname,port );

		while(buf[0] != 'q'){
			ssize_t tammsg;

			

				tammsg = recv(aceptado, buf, 256*sizeof(char), 0);
				printf("%i\n", tammsg );
				printf("%s\n", buf );
				if(tammsg ==-1){
					printf("Error, mensaje demasiado largo\n");
				}
				
				else{
					if(buf[0] == 'r'){
						char usuario[256];
						sscanf(buf,"u %s", usuario);
						struct passwd *datos;
						datos = getpwnam(usuario);
						strcat(buf, datos->pw_name);
						strcat(buf, "\n");
						printf("%s\n", buf);
						strcat(buf, "contraseña: ");
						strcat(buf, datos->pw_passwd);
						strcat(buf, "\n");
						printf("%s\n", buf );
						//strcat(buf, (char)datos->pw_uid);
						//printf("%s\n", buf );
						//strcat(buf, "\n");
						//strcat(buf, (char)datos->pw_gid);
						//strcat(buf, "\n");
						strcat(buf, datos->pw_gecos);
						strcat(buf, "\n");
						strcat(buf, datos->pw_dir);
						strcat(buf, "\n");
						strcat(buf, datos->pw_shell);
						strcat(buf, "\n");
						printf("%s\n",buf );
						buf[255] = "\0";
						ssize_t envio = send(aceptado, buf, 256*sizeof(char), 0);
						if (envio == -1)
						printf("Fallo al enviar el mensaje\n");

					}
					
					


					
					
				}

				
		



		}

		printf("Finalizando conexion\n");
		close(aceptado);
		printf("Cierre de socket hecho: %i \n", aceptado);
			
	
	
	


	
	close(sock);
	//exit(0);
	return 0;


}