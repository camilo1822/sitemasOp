#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int values[40];
struct parameters{
	int down;
	int up;
	
};


//int sum = 0; /* this data is shared by the thread(s) */
int numeroItems();
void leerDatos(int *,FILE *file);
void *runner(void *param); /* threads call this function */

int main(int argc, char *argv[])
{
	if (argc != 2){
		printf("error: debe ingesar asi: ./a.out <numero hilos>\n");
		exit(0)	;
	}
	int numHilos=atoi(argv[1]);
	
	struct timeval ti,tf;
	double tiempo;
	pthread_t tid[numHilos]; /* the thread identifier */
	unsigned char cnt =0;
	int sum=0; 	
	
	int *response[numHilos];
	//int value = atoi(argv[1]);
	
	struct parameters params[numHilos];
	//int tamano,j,l;
	FILE *inFile;
	char *fileName="vector.txt";
	inFile = fopen(fileName, "r");
	if(inFile == NULL){
		printf("No se puede abrir el fichero: %s\n", fileName);
		exit(EXIT_FAILURE);
	}
	
	int num;
	num = numeroItems(inFile);
	
	
	leerDatos(&num,inFile);
	fclose(inFile);
	int i;
	int pro = num/numHilos;
	int aux=pro;
	params[0].down = 1;
	params[0].up = pro;
	for(i=1;i<numHilos;i++){
		params[i].down = pro+1;
		pro+=aux;
		params[i].up = pro;
	}

	/* create the thread */
	for(cnt=0; cnt < numHilos; cnt++){ 	
		pthread_create(&tid[cnt], NULL, runner, (void*)&params[cnt]);
	}
	/* wait for the thread to exit */
	for(cnt=0; cnt < numHilos; cnt++){
		pthread_join(tid[cnt], (void**) &response[cnt]);
		sum += *response[cnt];
	}	
	gettimeofday(&ti,NULL);
	for(cnt=0; cnt < numHilos; cnt++){
		printf("Parcial result %d\n", *response[cnt]);
	}	
	gettimeofday(&tf,NULL);
	tiempo=(tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
	printf("Total result = %d\n",sum);
	printf("Tiempo = %g\n",tiempo);
	
	return EXIT_SUCCESS;
}

int numeroItems(FILE *file){
	int numero=0;
	char buffer[50];
	while(!feof(file)){
		fgets(buffer,50,file);
		numero++;
	}
	rewind(file);
	return numero;
}

void leerDatos(int *num,FILE *file){
	int j;
	
	for(j=0;j<*num;j++){
		fscanf(file, "%d", &values[j]);
	}
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
