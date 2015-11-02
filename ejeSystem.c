#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	int valor_retornado;
	printf("el id del proceso es: %d\n",(int)getpid());
	printf("el id del proceso padre es: %d\n",(int)getppid());
	valor_retornado=system("cal");
	valor_retornado=system("ls -l");
	return valor_retornado;
}
