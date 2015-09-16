#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <time.h>

int main(){

	long ini = 0;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	ini = tv.tv_usec;
	int i = 0;
	for(i = 0; i < 10000; i++);
	long fin = 0;
	gettimeofday(&tv, NULL);
	fin = tv.tv_usec;
	printf("Tiempo de bucle: %li\n", fin-ini );
//	printf("Directorio home: %s\n", passuser->pw_dir );
//	printf("Información de usuario: %s\n", passuser->pw_gecos );
	return 0;
}