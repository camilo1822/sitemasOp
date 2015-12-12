#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>

sem_t synch;
sem_t synch1;

void *s1(void *arg);
void *s2(void *arg);
void *s3(void *arg);

int main(){
	int i,cnt,b;
	pthread_t h1_id,h2_id,h3_id;
	
	sem_init(&synch,0,0);
	sem_init(&synch1,0,0);
	
	pthread_create(&h1_id,NULL,&s3,NULL);
	pthread_create(&h2_id,NULL,&s2,NULL);
	pthread_create(&h3_id,NULL,&s1,NULL);
	
	pthread_join(h1_id,NULL);
	pthread_join(h2_id,NULL);
	pthread_join(h3_id,NULL);
	
	sem_destroy(&synch);
	sem_destroy(&synch1);
	printf("\nDONE!!!!\n");

	return 0;
}

void *s1(void *arg){
	printf("\nS1 Executing...\n");
	sem_post(&synch);
	
	return 0;
}

void *s2(void *arg){
	//printf("\nS2 Waiting...\n");
	sem_wait(&synch);
	printf("\nS2 Executing...\n");
	sem_post(&synch1);
	
	return 0;
}

void *s3(void *arg){
	sem_wait(&synch1);
	printf("\nS3 Executing...\n");
	
	return 0;
}
