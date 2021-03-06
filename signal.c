#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>

void my_handler (int sig);/*function prototype*/

int main(void){
	/*parte1: Catch SIGINT*/
	signal (SIGINT,my_handler);
	printf("Catching SIGINT\n");
	sleep(3);
	printf("No SIGINT within 3 seconds\n");
	/*parte2: Ignore SIGINT*/
	signal (SIGINT,SIG_IGN);
	printf("Ignoring SIGINT\n");
	sleep(3);
	printf("No SIGINT within 3 seconds\n");
	/*parte3: Default action for SIGINT*/
	signal (SIGINT,SIG_DFL);
	printf("Default action for SIGINT\n");
	sleep(3);
	printf("No SIGINT within 3 seconds\n");
	return 0;
}

/*User-defined signal handlre function*/
void my_handler(int sig){
printf("I got SIGINT, number %d\n",sig);
exit(0);
}
