#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char *argv[]){
	printf("el id del proceso es: %d\n",(int)getpid());
	printf("el id del padre del proceso es: %d\n",(int)getppid());
	
	for(;;){
		pause();
	}
	return 0;
}
