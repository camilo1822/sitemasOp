#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	pid_t child_pid;
	/*creacion dle proceso hijo*/
	child_pid=fork();
	if(child_pid > 0){
		/*este es el proceso padre le cual duerme por 40s*/
		sleep(40);
	}else{
		/*este es el proceso hijo el cual culmina inmediatamente*/
		exit(0);
	}

	return 0;
}
