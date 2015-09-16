#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>



int main(int argc, char **argv){

	mode_t mask = umask(0027);

	/*if(argc < 2){
		printf("Fallo al usar el programa\n");
		return -1;
	}*/

	int i;
	printf("directorio: %s\n", argv[1]);
	i = open("prueba2.txt", O_CREAT | O_RDONLY, 00777);
	if (i == -1){
		printf("Fallo de creación de fichero\n");
		return -1;
	}

	printf("Fichero creado con exito\n");

	umask(mask);

	return 0;


}