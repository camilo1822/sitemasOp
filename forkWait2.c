#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main(){
	pid_t pid_h1,pid_h2,pid_h3;
	int status_h1,status_h2,status_h3;
	pid_t pid_n;
	int status_n;
	int i = 0;
	pid_h1=fork();
	if(pid_h1==0){
		pid_n = fork();
		if(pid_n==0){
			i++;
			printf("NIeto: i = %d\n",i);
		}
		else{
			wait(&status_n);// papa(hijo 1) esperando hijo(nieto)
			i++;
			printf("HIjo 1: i = %d\n",i);
		}
	}
	else{
		pid_h2 = fork();
		if(pid_h2==0){
			i++;
			printf("HIjo 2: i = %d\n",i);
		}
		else{
			pid_h3 = fork();
			if(pid_h3==0){
				i++;
				printf("Hijo 3: i =%d\n",i);
			}
			else{
				//el papa decidio esperar todos los hijo al final
				wait(&status_h1);//papa esperando hijo 1
				wait(&status_h2);//papa esperando hijo 2
				wait(&status_h3);//papa esperando hijo 3
				i++;
				printf("PAPA: i = %d\n",i);
			}
		}
	}

	return 0;
}




