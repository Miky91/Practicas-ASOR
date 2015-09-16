#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/utsname.h>
#include <pwd.h>

int main(){


uid_t user;
uid_t euser;
user = getuid();
euser = geteuid();
struct  passwd *passuser;
passuser = getpwuid(user);



if (user == euser){
	printf("Uid : %i = Euid: %i \n", user, euser );
}
else{
	printf("Uid : %i\n", user);
	printf("Euid : %i\n", euser);	
}

	printf("Nombre de usuario: %s\n", passuser->pw_name );
	printf("Directorio home: %s\n", passuser->pw_dir );
	printf("Información de usuario: %s\n", passuser->pw_gecos );
	return 0;
}