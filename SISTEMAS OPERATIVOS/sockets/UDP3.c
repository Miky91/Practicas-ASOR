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

	char mensaje[3] = "";
	struct sockaddr_storage msg;
	char hostname[NI_MAXHOST+1]= "";
	char port[NI_MAXSERV+1]= "";

	socklen_t msg_len = sizeof(msg);
	

	while(mensaje[0] != 'q'){

		ssize_t tammsg;

		fd_set set;
		FD_ZERO(&set);
		FD_SET(sock, &set);
		FD_SET(0, &set);

		int cambios = select(sock+1, &set, NULL, NULL, NULL);

		if(FD_ISSET(sock, &set))
				tammsg = recvfrom(sock,&mensaje, 3*sizeof(char), 0, &msg,&msg_len);
		else
				tammsg = read(0, mensaje, 3*sizeof(char));

		 

		
		if (tammsg != -1){

			getnameinfo(&msg, msg_len,hostname,NI_MAXHOST+1, port,NI_MAXSERV+1,0);
			
			printf("Recibidos %i bytes de %s , puerto: %s\n",tammsg, &hostname, &port );

			if(mensaje[0] == 't'){

				time_t t;
				time(&t);
				char hora[100];
				strcpy(hora, ctime(&t));
				printf("%s\n", hora );
				if(FD_ISSET(sock, &set))
					if (-1 == sendto(sock, hora, strlen(hora)+1, 0, &msg, msg_len))
						printf("We have a problem\n");
				printf("Mandando mensaje de hora\n");

			}
			else if (mensaje[0] == 'd'){
				time_t t;
				time(&t);
				struct tm *horacompleta = localtime(&t);
				char fecha[100];
				strftime(fecha, 100, "%A, %H: %M", horacompleta);
				printf("%s\n", fecha );
				if(FD_ISSET(sock, &set))
					if (-1 == sendto(sock, fecha, strlen(fecha)+1, 0, &msg, msg_len))
						printf("We have a problem, yeah\n");
				printf("Mandando mensaje de fecha\n");

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