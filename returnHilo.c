#include <pthread.h>
#include <stdio.h>

void* calcular_primo(void* arg);

int main(){
	pthread_t hilo_id;
	int cual_primo=5000;
	int primo;
	
	/*inicia le hilo,serequiere el 5000-esimo numero primo*/
	pthread_create(&hilo_id,NULL,&calcular_primo,&cual_primo);
	/*puedo hacer algo miesntras...si quiero*/
	/*espero q se el num sea calculado y entregado*/
	pthread_join(hilo_id,(void*)&primo);
	/*imprimo el numero entregado*/
	printf("el numero primo es: %d. \n",primo);
	 
	return 0;
}

/*calcula los numero primos sucesivamente retorna el 
n-esimo numero primo donde n es el valor apuntado por *arg*/
void* calcular_primo(void* arg){
	int candidato = 2;
	int n= *((int*)arg);
	while(1){
		int factor;
		int es_primo=1;
		for(factor=2;factor<candidato;++factor)
			if(candidato % factor==0){
				es_primo=0;
				break;	
			}
		if(es_primo){
			if(--n == 0)
				return (void*)candidato;
		}
		++candidato;
		
		
	}
	
	return NULL;
}




















