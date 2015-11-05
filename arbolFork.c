#include <stdio.h>
#include <unistd.h>

int main(int argc,char *argv[]){
	pid_t pid_h1, pid_h2, pid_h3;
	pid_t pid_n;
	int i = 0;
	pid_h1=fork();
	if(pid_h1==0){
		pid_n=fork();
		printf("me vine2 ");
		if(pid_n==0){
			i++;
			printf("NIeto: i=%d\n",i);
		}else{
			i++;
			printf("Hijo 1:i=%d\n",i);
		}
	}else{
		pid_h2=fork();
		if(pid_h2==0){
			i++;
			printf("Hijo 2: i=%d\n",i);
		}else{
			pid_h3=fork();
			if(pid_h3==0){
				i++;
				printf("Hijo 3: i=%d\n",i);
			}else{
				i++;
				printf("PAPA: i=%d\n",i);
			}
		}
	}
	return 0;
}
