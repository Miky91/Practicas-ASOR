#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/utsname.h>
#include <stdlib.h>

int main(){

	struct utsname datos;

	int i;
	//i = uname(&datos);
	/**if (i == -1){
		perror(errno);
		return -1;
	}**/
	printf("Longitud máxima de argumentos: %li\n", sysconf(_SC_ARG_MAX) );
	printf("Número máximo de hijos: %li\n", sysconf(_SC_CHILD_MAX));
	printf("Número máximo de ficheros: %li\n", sysconf(_SC_OPEN_MAX) );
	//printf("Version: %s\n", sysconf );
	//printf("Maquina: %s\n", datos.machine );
	
	return 0;
}