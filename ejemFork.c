#include <stdio.h>
#include <unistd.h>

int main(int argc,char *argv[]){
	pid_t pid_hijo;
	
	printf("ejemplo fork.Este programa creara otro procesos\n\n");
	printf("el pid del pro prin es:%d\n",(int)getpid());
	switch(pid_hijo=fork()){
		case -1:/*codigo ejecutado en caso de error*/
			printf("error al crear proceso");
			return -1;
		case 0:/*codigo ejecutado por el hijo*/
			printf("processo hijo:\n");
			printf("PID del hijo %d\n",(int)pid_hijo);
			break;
		default:/*codigo ejecutado por el padre*/
			printf("proce padre: proce hijo con pid %d creado \n",(int)pid_hijo);
	}
	/*esta linea sera ejecutada por el padre y por el hijo*/
	printf("fin del proc cuyo hijo es %d\n",(int)pid_hijo);

	return 0;
}
