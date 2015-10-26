/*hice todo*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXCHAR 20
#define MAXITEMS 100


typedef struct{
	int codigo;
	char descripcion[MAXCHAR];
	int valor;
}str_item;

int numeroItems();
void leerDatos(int *,str_item *pItem,FILE *file);
void newBill(int *codes,int *values,char nom[]);
void printBill(FILE *file,int n, int *quantity, int *value, int total, int *totals, int *code);
void checkItem(int *codes, char (*description)[MAXCHAR], int *values);
void nuevoArticulo(FILE *file);


int main(int argc, char *argv[]){
	
	/*int codes[MAXITEMS] = {101,102,103,104,105,106};
	char descriptions[MAXITEMS][MAXCHAR] = {"Articulo#1", "Articulo#2", "Articulo#3","Articulo#4","Articulo#5", "Articulo#6"};
	int values[MAXITEMS]={300,500,250,100,900,600};*/

	if (argc != 3){
		printf("error: debe ingesar asi: ./a.out <fichero entrda> <fichero salida>\n");
		exit(0)	;
	}
	
	/* abrir archivo*/
	FILE *inFile;
	char *fileName=argv[1];
	inFile = fopen(fileName, "rt");
	if(inFile == NULL){
		printf("No se puede abrir el fichero: %s\n", fileName);
		exit(EXIT_FAILURE);
	}
	
	int num;
	num = numeroItems(inFile);

	str_item *pItem;
	pItem=(str_item *)malloc(sizeof(str_item)*num);
	leerDatos(&num,pItem,inFile);
	
	


	char option;

	while(option!='q'){

		printf("Ingrese \n a. Nueva factura \n b. Consultar articulo \n c. Ingresar articulo \n q. Salir \n");
		setbuf(stdin, NULL);
		scanf("%c", &option);

		 if (option=='a'){
		 	//Creating a new ticket
			
			newBill(&pItem->codigo, &pItem->valor,argv[2]);
		 	//newBill(&codes, &values );
		 } else  if(option=='b'){
		 	//Checking an item
			checkItem(&pItem->codigo, (char (*)[MAXCHAR])pItem->descripcion, &pItem->valor);
		 	//checkItem(codes, (char (*)[MAXCHAR])descriptions[0], values);
		 } else  if(option=='c'){
		 	nuevoArticulo(inFile);
		 	
		 } else  if(option=='q'){
		 	return 0;
		 } else{
		 	 printf("Opcion no valida\n");
		 }
	}
	fclose(inFile);
	
	return 0;
}

void nuevoArticulo(FILE *file){
	int numero=0;
	char buffer[MAXCHAR];
	while(!feof(file)){
		fgets(buffer,MAXCHAR,file);
	}
	int ncod,nval;
	char ndesc[MAXCHAR];
	printf("Ingrese codigo: \n");
	scanf("%d",&ncod);
	
	printf("Ingrese descripcion: \n");
	scanf("%s",ndesc);
	
	printf("Ingrese valor: \n");
	scanf("%d",&nval);
	fprintf(file,"%d",&ncod);
	fprintf(file,"%s",ndesc);
	fprintf(file,"%d",&nval);
	rewind(file);
}

int numeroItems(FILE *file){
	int numero=0;
	char buffer[MAXCHAR];
	while(!feof(file)){
		fgets(buffer,MAXCHAR,file);
		numero++;
	}
	rewind(file);
	return numero/3;
}

void leerDatos(int *num,str_item *pItem,FILE *file){
	int i = 0;
	for(i=0; i< *num; i++){
		fscanf(file, "%d", &pItem->codigo);
		fscanf(file, "%s", pItem->descripcion);
		fscanf(file, "%d", &pItem->valor);
		pItem++;					
	}
}

void newBill(int *codes, int *values,char nom[]){
	int numItems;
	int inCode;
	int flag=0;
	int i=0;
	int j=0;

	int *pCodes;	
	int *pQuantities;
	int *pTotalPerCode;
	int total = 0;

	printf("Numero de articulos a facturar: ");
	scanf("%d", &numItems);

	pCodes = (int *)malloc(sizeof(int)*numItems);
	pQuantities = (int *)malloc(sizeof(int)*numItems);
	pTotalPerCode = (int *)malloc(sizeof(int)*numItems);

	while ( i<numItems ){
		setbuf(stdin, NULL);
		printf("\n\nArticulo #%d\n", i+1);
		printf("Codigo: \n");
		scanf("%d", &inCode);
		flag=0;
		//Para validar que el codigo es de un articulo existente		
		for (j=0; j<MAXITEMS;j++){
			if(inCode == codes[j]){
				pCodes[i] = inCode;

				printf("Cantidad: \n" );
				scanf("%d", pQuantities+i);
	
				pTotalPerCode[i] = values[j]*pQuantities[i];
				total += pTotalPerCode[i];

				printf("Valor: %d --- Acumulado:  %d \n", pTotalPerCode[i], total);
		
				flag=1;
				i++;
break;
			}	
		}
		if(flag==0){
			printf("El articulo con codigo %d no se encontró\n", inCode);
		}
		
	}
	FILE *outFile;
	char *fileNombre=nom;
	outFile = fopen(fileNombre, "w");
	printBill(outFile,numItems, pQuantities,  values, total, pTotalPerCode,pCodes );
	
}

void printBill(FILE *file,int n, int *quantity, int *value, int total, int *totals, int *code){
	printf("\n\n\t\tFactura de Venta\n");
	fprintf(file,"\n\n\t\tFactura de Venta\n");
	printf("\t\t Nombre Empresa \n");
	fprintf(file,"\t\t Nombre Empresa \n");
	
	printf("Cantidad  | Codigo | V. unit   | Total\n");
	fprintf(file,"Cantidad  | Codigo | V. unit   | Total\n");
	int i;
	for (i=0; i<n;i++){
		printf("%-8d  | %-5d  | %-10.2d| %d\n", quantity[i], code[i], value[i], totals[i] );
		fprintf(file,"%-8d  | %-5d  | %-10.2d| %d\n", quantity[i], code[i], value[i], totals[i] );
	}
	printf("Total: %d\n\n",total );
	fprintf(file,"Total: %d\n\n",total );
	fclose(file);
}

void checkItem(int *codes, char (*description)[MAXCHAR], int *values){

	int inCode;
	int flag = 0;
	printf("\nCodigo Articulo: ");
	scanf("%d", &inCode);

	int cnt;
	for (cnt=0; cnt<MAXITEMS;cnt++){
		if(inCode==codes[cnt]){
			printf("%s --> %d \n\n", (char *)(description+cnt), *(values+cnt) );	
			flag=1;		
		}
	}
	if(flag == 0)
		printf("El articulo con codigo %d no se encontró\n", inCode);
}
