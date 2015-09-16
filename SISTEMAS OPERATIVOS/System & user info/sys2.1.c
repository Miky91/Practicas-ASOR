#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/utsname.h>

int main(int argc, char ** argv){

	if(argc<2){
		printf("Error\n");
		return -1;
	}


	
	printf("Numero maximo de enlaces: %li\n", pathconf(argv[1], _PC_LINK_MAX));
	printf("Tamaño maximo de ruta: %li\n", pathconf(argv[1], _PC_PATH_MAX ));
	printf("Tamaño maximo de nombre: %li\n", pathconf(argv[1], _PC_NAME_MAX ));

	
	return 0;
}