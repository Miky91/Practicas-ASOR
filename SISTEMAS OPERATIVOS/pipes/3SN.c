#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv){

	/**if (argc <2){
		printf("Caca\n");
	}**/

	int pad_h[2];
	int hij_p[2];

	pid_t pid = fork();
	int nfd;
	printf("general\n");
	
	switch(pid){
		case -1: printf("Fail\n");return -1;
		case 0:

			close(pad_h[1]);

			close(hij_p[0]);

			char mensaje[256];
			
			char msgpadre = 'l';

			printf("hijo\n");
			int i;
			for(i = 0; i<10;i++){
				ssize_t longi = read(pad_h[0], mensaje, 256);

				mensaje[longi] = '\0';
				if( i == 9)
					msgpadre = 'q';
				write(hij_p[1], msgpadre, 1);


			}

			close(hij_p[1]);
			close(pad_h[0]);
			exit(0);

			break;

		default:
			close(pad_h[0]);
			close(hij_p[1]);

			char men[256];
			printf("padre\n");
			char msghijo = 'l';

			while (msghijo != 'q'){
				ssize_t longi = read(0, men, 256);
				men[longi] = '\0';

				longi = write(pad_h[1], men, longi+1);

				while (msghijo != 'q' && msghijo != 'l'){
					read(hij_p[0],men,1);


				}


				close(hij_p[0]);
				close(pad_h[1]);
				exit(0);	
			}
			
			break;
	}
/**

	int fd = open("./tuberia", O_WRONLY);

	if (fd==-1)
	{
		printf("Error al abrir tuberia\n");
		return -1;
	}

	write(fd,argv[1],strlen(argv[1]));
	close(fd);
**/return 0;
}