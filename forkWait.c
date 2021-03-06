#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main(int argc,char *argv[]){
	pid_t pid_hijo,pid_padre;
	int estado;
	printf("el pid del programa pricncipal es: %d\n",(int)getpid());
	switch(pid_hijo=fork()){
		case -1:/*codigo ejecutado en caso de error*/
			printf("error al crear proceso");
			return -1;
		case 0:/*codigo ejecutado por el hijo*/
			printf("Procesos hijo:\n");
			printf("PID del proceso: %d\n",(int)pid_hijo);
			printf("PID del padre: %d\n",(int)getppid());
			exit(0);
			printf("esta nunca se ejecutara en el hijo\n");
			break;
		default:/*codigo ejecutado por el padre*/
			wait(&estado);
			printf("Proceso padre:proceso hijo con pID %d creado \n",(int)pid_hijo);
			printf("PID del hijo: %d\n",(int)pid_hijo);
			printf("pid del padre: %d\n",(int)getppid());
			
	}
	
	return 0;
}
