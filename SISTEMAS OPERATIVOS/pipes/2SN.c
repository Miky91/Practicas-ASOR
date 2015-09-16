#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv){

	if (argc <2){
		printf("Caca\n");
	}

	int tub[2];
	pipe(tub);

	pid_t pid = fork();
	int nfd;

	switch(pid){
		case -1: printf("Fail\n");return -1;
		case 0:;
			close(tub[1]);
			nfd = dup2(tub[0],0);
			close(tub[0]);
			execlp(argv[3], argv[3], argv[4], NULL);
			break;

		default:;
			close(tub[0]);
			nfd = dup2(tub[1],1);
			close(tub[1]);
			execlp(argv[1], argv[1], argv[2], NULL);
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