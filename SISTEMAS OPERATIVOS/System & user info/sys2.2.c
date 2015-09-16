#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/utsname.h>

int main(){

	struct utsname datos;

	int i;
	i = uname(&datos);
	if (i == -1){
		perror(errno);
		return -1;
	}
	printf("Nombre del sistema: %s\n", datos.sysname );
	printf("Nodo: %s\n", datos.nodename );
	printf("Release: %s\n", datos.release );
	printf("Version: %s\n", datos.version );
	printf("Maquina: %s\n", datos.machine );
	
	return 0;
}