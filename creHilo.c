#include <pthread.h>
#include <stdio.h>

/*imprime 'x' en la salida del error stderr.
El parametro no es usado.No tiene retorno*/

void* imprime_x(void* unused){
	while(1) fputc('x',stderr);
	return NULL;

}

int main(){
	pthread_t id_hilo;
	/*crea un nuevo hilo sobre la funcion imprime_x*/
	/*identificador,null,metodo,argumentos*/
	pthread_create(&id_hilo,NULL,&imprime_x,NULL);
	/*Imprime 'o' en la salida del error stederr*/
	while(1) fputc('o',stderr);
	return 0;
}
