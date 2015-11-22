#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	printf("Ejecutable: \n");
	char *args[]={"/bin/ls","-l",".",NULL};

	//Forma2:con execv
	printf("Forma 2: \n");
	execv("/bin/ls",args);
	
	return 0;
}
