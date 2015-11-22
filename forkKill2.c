#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char *argv[]){
	pid_t pid_hijo;
	pid_hijo=getpid();
	printf("el id del proceso es: %d\n",(int)pid_hijo);
	printf("el id del padre del proceso es: %d\n",(int)getppid());
	printf("Hola mundo. \n");
	printf("Hola mundo. \n");
	printf("Hola mundo. \n");
	printf("Hola mundo. \n");
	printf("Hasta la vista baby. \n");
	kill(pid_hijo,9);//forma alternativa: kill(pid_hijo,SIGKILL);
	printf("Hasta la vista baby. \n");
	printf("Hasta la vista baby. \n");
	printf("Hasta la vista baby. \n");
	return 0;
}
