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

int main(int argc, char ** argv){

	if (argc != 4)
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
		printf("Socket caca\n");
		return -1;
	}

	int on = 1;
	int off = 0;

	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void*)&on,sizeof(int));
	setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY, (void*)&off,sizeof(int));


	
	struct sockaddr_storage msg;
	socklen_t msglen = sizeof(msg);
	
	freeaddrinfo(resultado);

	char buf[256] = "";
	




		
		
		ssize_t envio = sendto(sock, argv[3], strlen(argv[3])+1, 0,resultado->ai_addr,resultado->ai_addrlen);

		if (envio == -1)
			printf("Fallo al enviar el mensaje\n");


		ssize_t recibido = recvfrom(sock, buf, 256*sizeof(char), 0,resultado->ai_addr,&(resultado->ai_addrlen));

		if (recibido == -1)
			printf("Fallo al recibir el mensaje\n");

		else{
			buf[recibido] = '\0';
			printf("%s\n", buf );
		}
		if (recibido == 0)
			printf("Saliendo del socket\n");
		if (buf == "q\n")
			printf("Solicitando salida\n");


	



	
	close(sock);

	return 0;


}