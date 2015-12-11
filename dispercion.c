#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(){
	double vec[30]={3,2.5,4,2,4.9};
	double x;
	int i,j;
	double suma=0.0;
	float resta=0.0;
	for(i=0;i<5;i++){
		double valor = vec[i];
		suma+=valor;
	}
	x=suma/5;
	for(j=0;j<5;j++){
		float valor1 = vec[i]-x;
		float y=pow(valor1,2);
		
		resta+=y;
	}
	float resultado=resta/4;
	float resultado1 = sqrt(resultado);
	printf("dispercion: %f \n",resultado1);
	return 0;
}
