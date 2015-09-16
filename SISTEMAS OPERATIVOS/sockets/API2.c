#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netdb.h>
#include <stdio.h>


int main(int argc, char ** argv){

	if (argc != 2)
	{
		printf("Error de uso\n");
		return -1;
	}

	int sock = socket(AF_INET, SOCK_STREAM, 0);


	
	struct addrinfo informacion;
	struct addrinfo *resultado;

	informacion.ai_flags = AI_PASSIVE;
	informacion.ai_family = AF_UNSPEC;
	informacion.ai_socktype = 0;
	informacion.ai_protocol = 0;
	//informacion.ai_addrlen = 256;
	informacion.ai_addr = NULL;
	informacion.ai_canonname = NULL;
	informacion.ai_next = NULL;

	
	if(getaddrinfo(argv[1],NULL,&informacion,&resultado) != 0){
		printf("Error al obtener direcciones\n");
		return -1;
	} 
	
	char dir4[INET_ADDRSTRLEN+1] = "";
	char dir6[INET6_ADDRSTRLEN+1] = "";

	while(resultado != NULL){

		struct sockaddr_in *ip4;
		if(resultado->ai_family == AF_INET){
			ip4 = resultado->ai_addr;
			if(inet_ntop(AF_INET,&(ip4->sin_addr),dir4,INET_ADDRSTRLEN +1) == NULL){
				printf("Error en inet_ntop\n");
				return -1;
			}
			printf("Host: %s , familia: AF_INET   ", dir4 );

		}


		struct sockaddr_in6 *ip6;
		if(resultado->ai_family == AF_INET6){
			ip6 = resultado->ai_addr;
			if(inet_ntop(AF_INET6,&(ip6->sin6_addr),dir6,INET6_ADDRSTRLEN +1) == NULL){
				
				printf("Error en inet_ntop(ipv6\n");
				return -1;
			}
			
			printf("Host: %s , familia: AF_INET6   ", dir6 );

		}


		if(resultado->ai_socktype == SOCK_STREAM)
			printf(" SOCK_STREAM\n");

		else if(resultado->ai_socktype == SOCK_DGRAM)
				printf(" SOCK_DGRAM\n");

			else
				printf(" SOCK_RAW\n");


		resultado = resultado->ai_next;

	}

	freeaddrinfo(resultado);
	

	return 0;


}