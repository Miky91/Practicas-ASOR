#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <time.h>

int main(){

	time_t t;
	t = time(NULL);
	char * hora;
	hora = ctime(&t);
	

	printf("Hora del sistema: %s\n", hora );
//	printf("Directorio home: %s\n", passuser->pw_dir );
//	printf("Información de usuario: %s\n", passuser->pw_gecos );
	return 0;
}