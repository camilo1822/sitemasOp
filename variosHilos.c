#include <pthread.h>
#include <stdio.h>

/*esta estructura sirve para pasar parametros al hilo*/
struct parametros_hilo{
	/*par1: caracter a imprimir*/
	char caracter;
	/*par2: numero de veces que se desea imprmir*/
	int contador;
};

/*esta funcion improme un numero de caracteres a la salida
del error, tal y como lo indica el parametro de la funcion.*/
void* imprimir_caracter(void* parametros){
	/*se hace un cast al tipo de dato correcto*/
	struct parametros_hilo* p=(struct parametros_hilo*)parametros;
	int i;
	for(i=0;i < p->contador;i++){
		fputc(p->caracter,stderr);
	}
	return NULL;
}

/*programa principal*/
int main(){
	pthread_t id_hilo_1;
	pthread_t id_hilo_2;
	struct parametros_hilo hilo1_param;
	struct parametros_hilo hilo2_param;
	
	/*crea un hilo para imprimir 30,000 x */
	hilo1_param.caracter='x';
	hilo1_param.contador=30000;
	pthread_create(&id_hilo_1,NULL,&imprimir_caracter,&hilo1_param);
	
	/*crea un hilo para imprimir 20,000 o */
	hilo2_param.caracter='o';
	hilo2_param.contador=20000;
	pthread_create(&id_hilo_2,NULL,&imprimir_caracter,&hilo2_param);
	
	/*INSRERTAR AQUI*/
	pthread_join(id_hilo_1,NULL);
	pthread_join(id_hilo_1,NULL);
	
	return 0;
}
