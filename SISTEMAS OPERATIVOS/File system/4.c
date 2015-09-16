#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>



int main(int argc, char **argv){



	if(argc < 2){
		printf("Fallo al usar el programa\n");
		return -1;
	}




	int i;
	printf("directorio: %s\n", argv[1]);
	i = open(argv[1], O_CREAT | O_RDWR);
	if (i == -1){
		printf("Fallo de creación de fichero\n");
		return -1;
	}
	int nuevo = dup2(i,1);
	if (nuevo == -1){
		printf("Fallo de creación de fichero\n");
		return -1;
	}


	printf("Duplicado descriptor\n");


	return 0;


}