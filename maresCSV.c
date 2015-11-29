#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Macros
#define MAXSUBJ 20
#define NUMCHARNAME 80
typedef unsigned int uint;

typedef struct{
	char nombre[NUMCHARNAME];
	float nota;
	uint creditos;
}strMateria;

int numeroMaterias();
void leerDatos(uint *,strMateria *pMateria,FILE *file);
void mostrarDatos(uint *,strMateria *pMateria);
float calculaProm(uint *, strMateria *pMateria);
void imprimir(uint *,strMateria *pMateria,FILE *file,float);

int main(int argc, char *argv[]){
	/* abrir archivo*/
	FILE *inFile;
	char *fileName="materias.csv";
	inFile = fopen(fileName, "r");
	if(inFile == NULL){
		printf("No se puede abrir el fichero: %s\n", fileName);
		exit(EXIT_FAILURE);
	}
	
	/*numero de materias*/
	uint num;
	num = numeroMaterias(inFile);
	printf("numero de materias: %d\n",num);
	
	/*leer los datos y mandarlos a dinamica*/
	strMateria *pMateria;
	pMateria=(strMateria *)malloc(sizeof(strMateria)*num);
	leerDatos(&num,pMateria,inFile);
	
	mostrarDatos(&num,pMateria);
	
	
	float promedio;
	promedio=calculaProm(&num,pMateria);
	printf("promedio ponderado: %f\n",promedio);
	
	FILE *outFile;
	char *fileNombre="mares1.txt";
	outFile = fopen(fileNombre, "w");
	imprimir(&num,pMateria,outFile,promedio);
	
	uint value;
	uint value1;
	free(pMateria);
	fclose(inFile);
	fclose(outFile);
	
	return 0;
}

int numeroMaterias(FILE *file){
	int numero=0;
	char buffer[NUMCHARNAME];
	fgets(buffer,NUMCHARNAME,file);
	while(!feof(file)){
		fgets(buffer,NUMCHARNAME,file);
		puts(buffer);
		numero++;
	}
	rewind(file);
	return numero-1;
}

void leerDatos(uint *num,strMateria *pMateria,FILE *file){
	int i = 0;
	char buffer[NUMCHARNAME];
	fgets(buffer,NUMCHARNAME,file);
	for(i=0; i< *num; i++){
		fgets(buffer,NUMCHARNAME,file);
		char *aux;
		aux=strtok(buffer,";");
		strcpy(pMateria->nombre, aux);
		aux=strtok(NULL,";");
		pMateria->nota=atof(aux);
		aux=strtok(NULL,";");
		pMateria->creditos=atoi(aux);
		pMateria++;					
	}
}

void mostrarDatos(uint *num,strMateria *pMateria){
	int i;
	for(i=0;i<*num;i++){
		printf("\nMateria: %s\n",pMateria->nombre);
		printf("Nota: %f\n",pMateria->nota);
		printf("Credits: %d\n",pMateria->creditos);
		pMateria++;
	}
}

float calculaProm(uint *num, strMateria *pMateria){
	int i = 0;
	float prom = 0;
	int numCred=0;
	for(i=0; i<*num; i++){
		float not=0;
		int cred=0;
		int notMat=0;		
		not=pMateria->nota;
		cred=pMateria->creditos;
		numCred+=cred;
		notMat=not*cred;
		prom+=notMat;
		pMateria++;
	}
	prom = prom/numCred;
	return prom;
}

void imprimir(uint *num,strMateria *pMateria,FILE *file,float prom){
	
	int i = 0;
	int ganadas=0;
	int perdidas=0;
	printf("\n%-10s %-5s %-8s\n", "Nombre", "Nota", "Creditos" );
	fprintf(file,"\n%-10s %-5s %-8s\n", "Nombre", "Nota", "Creditos" );

	for(i=0; i<*num; i++){		
		printf("%-10.10s %-5.1f %-8d\n", pMateria->nombre,pMateria->nota,pMateria->creditos);
		fprintf(file,"%-10.10s %-5.1f %-8d\n", pMateria->nombre,pMateria->nota,pMateria->creditos);
		float nott = pMateria->nota;
		if(nott>=3){
			ganadas++;
		}else{
			perdidas++;
		}
		pMateria++;
	}
	printf("Total materias: %d\n",*num);
	fprintf(file,"Total materias: %d\n",*num);
	printf("Materias Ganadas: %d\n",ganadas);
	fprintf(file,"Materias Ganadas: %d\n",ganadas);
	printf("Materias Perdidas: %d\n",perdidas);
	fprintf(file,"Materias Perdidas: %d\n",perdidas);
	printf("El promedio ponderado es: %.1f \n", prom);
	fprintf(file,"El promedio ponderado es: %.1f \n", prom);
}

