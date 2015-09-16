#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/utsname.h>

int main(){


uid_t user;
uid_t euser;
user = getuid();
euser = geteuid();

if (user == euser){
	printf("Uid : %i = Euid: %i \n", user, euser );
}
else{
	printf("Uid : %i\n", user);
	printf("Euid : %i\n", euser);	
}
/**
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
	**/
	return 0;
}