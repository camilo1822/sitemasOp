#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#define SHMSZ 27

main(){
	int shmid;
	key_t key;
	char *shm,*s;
	
	/*se requiere el segemento llamado 1234 creado por el servidor*/
	key=1234;
	
	/*ubica el segmento*/
	if((shmid=shmget(key,SHMSZ,0666)) < 0){
		perror("shmget");
		exit(1);
	}
	
	/*se adhiere le segmento para poder hacer uso de el*/
	if((shm=shmat(shmid,NULL,0)) == (char *) -1){
		perror("shmat");
		exit(1);
	}
	
	/*lee lo que el servidor puso en la memoria*/
	for(s=shm;*s != NULL; s++){
		putchar(*s);
	}
	putchar('\n');
	
	/*finalmente, cambia el valor del primer caracter indicando que ha leido el segmento*/
	*shm = '*';
	exit(0);
	
}






