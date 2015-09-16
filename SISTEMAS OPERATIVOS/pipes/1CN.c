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

	int fd = open("./tuberia", O_WRONLY);

	if (fd==-1)
	{
		printf("Error al abrir tuberia\n");
		return -1;
	}

	write(fd,argv[1],strlen(argv[1]));
	close(fd);

}