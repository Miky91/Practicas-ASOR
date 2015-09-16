#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv){

	/**if (argc <2){
		printf("Caca\n");
	}**/


	mkfifo("tuberia", 0644);
	mkfifo("tuberia2", 0644);

	char buf[256];
	int longitud = 0;

	int pipe1 = open("tuberia", O_RDONLY | O_NONBLOCK);

	int pipe2 = open("tuberia2", O_RDONLY | O_NONBLOCK);

	int cambios, tuberiaactual;


	do{
		fd_set set;
		FD_ZERO(&set);
		FD_SET(pipe1, &set);
		FD_SET(pipe2, &set);

		cambios = select((pipe1 < pipe2) ? pipe2 +1 : pipe1 +1, &set, NULL, NULL, NULL);
		
		
		if (cambios>0){
			if(FD_ISSET(pipe1, &set))
				tuberiaactual = pipe1;
			else
				tuberiaactual = pipe2;	

			int i;
			ssize_t tam = read(tuberiaactual, buf,256);
			if(tam == -1){
				printf("Mensaje muy largo\n");
				return -1;
			}
			buf[tam] = '\0';
			printf("Tuberia: %s\n", buf);
			printf("teta\n");
		}




	}while (cambios != -1);

	close(pipe1);
	close(pipe2);
	
return 0;
}