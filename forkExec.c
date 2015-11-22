#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	pid_t pid_h1,pid_h2;
	int status;
	pid_h1=fork();
	if(pid_h1==0){
		//proceso hijo el cual ejecuta ls
		execl("/bin/ls","/bin/ls","/",NULL);
	}else{
		pid_h2=fork();
		if(pid_h2==0){
			//proceso hijo q ejecuta date
			execl("/bin/date","/bin/date",NULL);
		}else{
			//proceso padre
			wait(&status);//esperar un proceso
			wait(&status);//esperar el otro proceso
			printf("hasta la vista baby \n");
		}
	}
	
	return 0;
}
