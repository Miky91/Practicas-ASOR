#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <time.h>

int main(){

	
	struct tm *fecha;
	time_t t;
	char c[1000];
	time(&t);
	fecha = localtime(&t);

	strftime(c,1000, "%A, %H:%M", fecha);
	printf("Hoy es: %s\n", c );
//	printf("Directorio home: %s\n", passuser->pw_dir );
//	printf("Información de usuario: %s\n", passuser->pw_gecos );
	return 0;
}