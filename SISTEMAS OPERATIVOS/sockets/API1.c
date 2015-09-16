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
	if (sock==-1)
	{
		printf("Error al crear el socket\n");
		return -1;
	}

	struct in_addr dir4;

	if (inet_pton(AF_INET, argv[1], &dir4)<0)
	{
		printf("Error al obtener direccion\n");
		return -1;
	}
	
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(2014);
	addr.sin_addr = dir4;

	if (bind(sock, (const struct sockaddr *)&addr, sizeof(addr))){
		printf("Error en bind\n");
		return -1;
	}
	printf("Socket binded\n");

	
	if (listen(sock,12) == -1){
		printf("Error en listen\n");
		return -1;
	}

	printf("Socket listenning\n");


	close(sock);

	return 0;


}