#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	printf("Ejecutable: \n");
	char *args[]={"/bin/ls","-l",".",NULL};
	//forma1:con execl
	printf("Forma 1: \n");
	execl("/bin/ls","/bin/ls","-l",".",NULL);
	return 0;
}
