#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define NUMTHREADS 3

int values[]={11,2,3,4,5,6,7,8,9,10,11,12};
struct parameters{
	int down;
	int up;
};



//int sum = 0; /* this data is shared by the thread(s) */
void *runner(void *param); /* threads call this function */

int main(int argc, char *argv[])
{
	
	pthread_t tid[NUMTHREADS]; /* the thread identifier */
	unsigned char cnt =0;
	int sum=0; 	
	
	int *response[NUMTHREADS];
	//int value = atoi(argv[1]);
	
	struct parameters params[NUMTHREADS];
	
	
	
	params[0].down = 1;
	params[0].up = 4;
	params[1].down = 5;
	params[1].up = 8;
	params[2].down = 9;
	params[2].up = 12;

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

/* The thread will begin control in this function */
void *runner(void *param)
{
	int i =	0;
	struct parameters *ptr_params = (struct parameters *)param;
	int lower = ptr_params->down;
	int upper = ptr_params->up;
	int sum = 0;
	int *ptr = (void *) malloc(sizeof(int));
	
	printf("lower: %d     upper: %d \n",lower,upper);
	for (i = lower; i <= upper; i++){
		int valor= values[i-1];
		
		sum += valor;
	}
	*ptr = sum;	
		
	pthread_exit(ptr);
}
