#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define numHilos 3



int num1;
int num2;
struct parameters{
	int down;
	int up;
	int num;
	
};

void *sumkn(void *param);

int main(int argc, char *argv[]){

	if (argc != 4){
		printf("error: debe ingesar asi: ./a.out <numero1><numero2><limite>\n");
		exit(0);
	}
	num1=atoi(argv[1]);
	num2=atoi(argv[2]);
	int limite=atoi(argv[3]);
	//int numHilos=atoi(argv[4]);
	int j;

	pthread_t tid[numHilos];
	unsigned char cnt =0;
	int sum=0; 	
	
	int *response[numHilos];

	struct parameters params[numHilos];
	
	params[0].num=atoi(argv[1]);
	params[1].num=atoi(argv[2]);
	params[2].num=num1*num2;
	
	
	int i;
	
	params[0].down = 1;
	params[0].up = limite;
	for(i=1;i<numHilos;i++){
		params[i].down = 1;
		params[i].up = limite;
	}

	for(cnt=0; cnt < numHilos; cnt++){ 	
		pthread_create(&tid[cnt], NULL, sumkn, (void*)&params[cnt]);
	}

	for(cnt=0; cnt < numHilos; cnt++){
		pthread_join(tid[cnt], (void**) &response[cnt]);
		if(cnt==2){
			sum-=*response[cnt];
		}else{
		sum += *response[cnt];
		}
	}
	

	printf("Total result = %d\n",sum);


	return 0;
}

void *sumkn(void *param)
{
	int i =	0;
	int j =	0;
	struct parameters *ptr_params = (struct parameters *)param;
	int lower = ptr_params->down;
	int upper = ptr_params->up;
	int numero= ptr_params->num;
	int sum = 0;

	int *ptr = (void *) malloc(sizeof(int));
	
	printf("lower: %d     upper: %d \n",lower,upper);
	
	for (i = lower; i < upper; i++){
		if(i % numero == 0){
			sum += i;
		}
		
		
	}

	*ptr = sum;	
		
	pthread_exit(ptr);
}
