#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#define NUMTHREADS 200
#define MAXCNT  1000

/*varaibles globales-shared between threads*/
double counter = 0;
sem_t sem;
/*declaracion de funciones*/
void* counting(void *);

int main(void){
	pthread_t tid[NUMTHREADS];
	int i=0;
	
	/*iniciar semaforo*/
	/*sem_init(identificador,si es hilo es 0)*/
	sem_init(&sem,0,1);
	
	for(i=0;i<NUMTHREADS;i++){
		pthread_create(&tid[i],NULL,&counting,NULL);
	}
	for(i=0;i<NUMTHREADS;i++){
		pthread_join(tid[i],NULL);
	}
	
	/*destriur semaforo*/
	sem_destroy(&sem);
	
	printf("\ncounter must be in: %d\n",MAXCNT*NUMTHREADS);
	printf("\nCounter value is: %.0f\n\n",counter);
	
	return 0;
}

void* counting(void * unused){
	int i = 0;
	/*decrementa el semaforo,si su valor es menor q cero bloquea los procesos, sirve para mirar si el recurso esta ocupado*/
	sem_wait(&sem);
	for(i=0;i<MAXCNT;i++){
		counter++;
	}
	/*incrementamos el semaforo es lo q se usa cuando se libera el recurso*/
	sem_post(&sem);
	return NULL;
}
