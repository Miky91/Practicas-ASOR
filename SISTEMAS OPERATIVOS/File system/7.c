#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/file.h>



int main(int argc, char **argv){


	struct flock cerrojo;
	if(argc < 2){
		printf("Fallo al usar el programa\n");
		return -1;
	}




	int i;
	printf("directorio: %s\n", argv[1]);
	i = open(argv[1], O_CREAT | O_RDWR);
	if (i == -1){
		printf("Fallo de creación de fichero\n");
		return -1;
	}


	cerrojo.l_type = F_WRLCK;
	cerrojo.l_whence = SEEK_SET;
	cerrojo.l_start = 0;
	cerrojo.l_len = 0;
	cerrojo.l_pid = getpid();


	int valor = fcntl(i,F_GETLK, &cerrojo);

	if(valor == -1){
		printf("Fichero bloqueado\n" );
		return -1;
	}
	else{

	//	struct tm *fecha;
	time_t t;
	//char c[1000];
	time(&t);
	//fecha = localtime(&t);

	//int long_real = strftime(c,1000, "%A, %H:%M", fecha);
	printf("Hoy es: %i\n", t );
		write(i,t,sizeof(t));

		sleep(39);

		cerrojo.l_type = F_UNLCK;
		fcntl(i,F_SETLK,&cerrojo);
		close(i);


	}

	
	return 0;


}