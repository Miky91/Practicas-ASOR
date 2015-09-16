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





void ejecutar(int socket, int numHijo, int numero){

	char mensaje[2] = "";
	struct sockaddr_storage msg;
	char hostname[NI_MAXHOST+1]= "";
	char port[NI_MAXSERV+1]= "";

	socklen_t msg_len = sizeof(msg);


	while(mensaje[0] != 'q'){

			ssize_t tammsg = recvfrom(socket,&mensaje, 2*sizeof(char), 0, &msg,&msg_len); 

			
			if (tammsg != -1){

				getnameinfo(&msg, msg_len,hostname,NI_MAXHOST+1, port,NI_MAXSERV+1,0);
				
				printf("[H: %i, %i] Host: %s , puerto: %s\n",numHijo, numero, &hostname, &port );

				if(mensaje[0] == 'a'){

					
					if (-1 == sendto(socket, hostname, strlen(hostname)+1, 0, &msg, msg_len))
						printf("We have a problem\n");
					printf("Mandando datos IP del host cliente\n");


				}
				else if (mensaje[0] == 'p'){
					
					if (-1 == sendto(socket, port, strlen(port)+1, 0, &msg, msg_len))
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



}






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
	informacion.ai_family = AF_INET6;
	informacion.ai_socktype = SOCK_DGRAM;
	informacion.ai_protocol = 0;
	//informacion.ai_addrlen = 256;
	informacion.ai_addr = NULL;
	informacion.ai_canonname = NULL;
	informacion.ai_next = NULL;

	if(getaddrinfo("::",argv[1],&informacion,&resultado) != 0){
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

	

	pid_t pid = getpid();
	pid_t pid2 = getpid();


	while (pid){

		pid = fork();


		if (pid == -1){
			printf("Error en fork\n");
			return -1;
		}

		if(pid == 0){
			
			ejecutar(sock,pid,1);


		}
		else{
			int status;
			pid2 = fork();
			if (pid2 == -1){
				printf("Error en segundo fork\n");
				return -1;
			}

			if(pid2 == 0){
				ejecutar(sock,pid,2);

			}
			else{
				pid_t hijo1 = wait(&status);
				printf("[PADRE]Terminó la ejecución del programa del hijo 1 codigo de salida: %i\n", status);

				pid_t hijo2 = wait(&status);
				printf("[PADRE]Terminó la ejecución del programa del hijo 2 codigo de salida: %i\n", status);

				sleep(300);
			}
		}


		



	}

	
	close(sock);

	return 0;


}