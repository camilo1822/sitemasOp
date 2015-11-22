#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	printf("Ejecutable: \n");
	char *args[]={"/bin/ls","-l",".",NULL};
	
	//forma3: con execvp
	printf("Forma 3: \n");
	execvp("/bin/ls",args);
	return 0;
}
