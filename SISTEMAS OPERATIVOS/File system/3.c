#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>



int main(int argc, char **argv){

	mode_t mask = umask(0027);


	/*if(argc < 2){
		printf("Fallo al usar el programa\n");
		return -1;
	}*/

	struct stat fichero;
	
	int j = stat("/etc", &fichero);

	
	printf("Major: %i\n", major(fichero.st_dev) );
	printf("Major: %i\n", minor(fichero.st_dev) );
	printf("Numero de inodo: %i\n", fichero.st_ino);
	if(S_ISREG(fichero.st_mode)){
		printf("Fichero regular\n");
	}
	if(S_ISDIR(fichero.st_mode)){
		printf("Directorio\n");
	}
	if(S_ISLNK(fichero.st_mode)){
		printf("Enlace simbolico\n");
	}
	printf("Hora de acceso: %i\n", fichero.st_atime);

	umask(mask);

	return 0;


}