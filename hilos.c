/*
	Example: data spliting using Threads
	
	compile: gcc -Wall -o threads 4_pthreads.c -lpthread
	To execute: ./threads 5 
	
*/


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

struct parameters{
	int down;
	int up;
};
int NUMTHREADS;
int value;

void *runner(void *param); 

int main(int argc, char *argv[])
{
	printf("Ingrese numero de hilos: \n");
	scanf("%d",&NUMTHREADS);
	printf("limites: \n");
	scanf("%d",&value);
	pthread_t tid[NUMTHREADS];
	unsigned char cnt =0;
	int sum=0; 	
	
	int *response[NUMTHREADS];
	
	struct parameters params[NUMTHREADS];
	
	
	if (value < NUMTHREADS ) {
		fprintf(stderr,"%d must be >= 0\n",value);
		return -1;
	}
	int i;
	int pro = value/NUMTHREADS;
	int aux=pro;
	params[0].down = 1;
	params[0].up = pro;
	for(i=1;i<NUMTHREADS;i++){
		params[i].down = pro+1;
		pro+=aux;
		params[i].up = pro;
	}


	/* create the thread */
	for(cnt=0; cnt < NUMTHREADS; cnt++){ 	
		pthread_create(&tid[cnt], NULL, runner, (void*)&params[cnt]);
	}
	/* wait for the thread to exit */
	for(cnt=0; cnt < NUMTHREADS; cnt++){
		pthread_join(tid[cnt], (void**) &response[cnt]);
		sum += *response[cnt];
	}	
	
	for(cnt=0; cnt < NUMTHREADS; cnt++){
		printf("Parcial result %d\n", *response[cnt]);
	}	
	
	printf("Total result = %d\n",sum);
	
	return EXIT_SUCCESS;
}

void *runner(void *param)
{
	int i =	0;
	struct parameters *ptr_params = (struct parameters *)param;
	int lower = ptr_params->down;
	int upper = ptr_params->up;
	int sum = 0;
	int *ptr = (void *) malloc(sizeof(int));
	
	printf("lower: %d     upper: %d \n",lower,upper);
	for (i = lower; i <= upper; i++)
		sum += i;
	
	*ptr = sum;	
		
	pthread_exit(ptr);
}
