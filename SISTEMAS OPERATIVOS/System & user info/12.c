#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int main(){

	int i;
	i =	setuid(0);
	if (i == -1){
		perror("Caca");
	}

	return 1;
}