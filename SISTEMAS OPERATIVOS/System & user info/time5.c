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
	time(&t);
	fecha = localtime(&t);

	printf("Año: %i\n", 1900 + fecha->tm_year );
//	printf("Directorio home: %s\n", passuser->pw_dir );
//	printf("Información de usuario: %s\n", passuser->pw_gecos );
	return 0;
}