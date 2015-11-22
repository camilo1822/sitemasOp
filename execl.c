#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	printf("Ejecutable: \n");
	char *args[]={"/bin/ls","-l",".",NULL};
	//forma1:con execl
	printf("Forma 1: \n");
	execl("/bin/ls","/bin/ls","-l",".",NULL);
	//Forma2:con execv
	printf("Forma 2: \n");
	execv("/bin/ls",args);
	//forma3: con execvp
	printf("Forma 3: \n");
	execvp("/bin/ls",args);
	return 0;
}
