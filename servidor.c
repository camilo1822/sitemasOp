#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#define SHMSZ 27

int main(){
	char c;
	int shmid;
	key_t key;
	char *shm,*s;
	
	/*Nombre del segmento de memoria compartida ="1234"*/
	key=1234;
	
	/*se crea el segmento de memoria*/
	if((shmid=shmget(key,SHMSZ,IPC_CREAT | 0666)) < 0){
		perror("shmget");
		exit(1);
	}
	
	/*el programa se adhiere (attach) al segemento ya creado*/
	if((shm=shmat(shmid,NULL,0)) == (char *) -1){
		perror("shmat");
		exit(1);
	}
	
	/*se ponen algunos datos en el segmento para que el proceso cliente los lea*/
	s=shm;
	for(c='a';c<='z';c++){
		*s++ = c;
	}
	*s=NULL;
	
	/*por ultimo,se espera a que el proceso cliente cambie el primer caracter de la memoria compartida a '*' indicando que ya leyo l ainformacion*/
	while(*shm != '*'){
		sleep(1);
	}
	return 0;
}










/*Para trabajar con un segmento de memoria compartida, es necesario crear un vínculo (attachment) entre la memoria local del proceso interesado y el segmento compartido. Esto se realiza con la función shmat. El proceso que vincula un segmento de memoria compartida cree estar trabajando con ella como si fuera cierta área de memoria local. Para deshacer el vínculo está la función shmdt.*/

/*shmget - obtiene un segmento de memoria compartida. */
/* int shmget( key_t key, size_t size, int shmflg);
Descripción

La función shmget retorna el identificador de memoria compartida asociada a key. Un identificador de memoria compartida y la estructura de datos asociada se crearán para key si una de las siguientes condiciones se cumple:

- Si key es igual a IPC_PRIVATE. Cuando esto ocurre se creará un nuevo identificador, si existen disponibilidades, este identificador no será devuelto por posteriores invocaciones a shmget mientras no se libere mediante la función shmctl. El identificador creado podrá ser utilizado por el proceso invocador y sus descendientes; sin embargo esto no es un requerimiento. El segmento podrá ser accedido por cualquier proceso que posea los permisos adecuados.

- Si key aún no tiene asociado un identificador de memoria compartida y además shmflg & IPC_CREAT es verdadero.

Como consecuencia de la creación, la estructura de datos asociada al nuevo identificador se inicializa de la siguientes manera: shm_perm.cuid y shm_perm.uid al identificador de usuario efectivo del proceso invocador, shm_perm.gcuid y shm_perm.guid al identificador de grupo efectivo del proceso invocador, los 9 bits menos significativos de shm_perm.mode se inicializan a los 9 bits menos significativos del parámetro shmflg, shm_segsz al valor especificado por size, shm_ctime a la fecha y hora que el sistema poseía en el momento de la invocación y por último se ponen a cero shm_lpid, shm_nattach, shm_atime y shm_dtime.

Si la ejecución se realiza con éxito, entonces retornará un valor no negativo denominado identificador de segmento compartido. En caso contrario, retornará -1 y la variable global errno tomará en código del error producido. */

/* Operaciones de control

shmctl - Realiza operaciones de control en una región de memoria compartida.

Sintaxis

#include <sys/shm.h>

int smctl(int shmid, int cmd, struct shmid_ds *buff);
Descripción

La función shmctl permite realizar un conjunto de operaciones de control sobre una zona de memoria compartida identificada por shmid. El argumento cmd se usa para codificar la operación solicitada. Los valores admisibles para este parámetro son:

IPC_STAT: lee la estructura de control asociada a shmid y la deposita en la estructura apuntada por buff.

IPC_SET: actualiza los campos shm_perm.uid, shm_perm.gid y shm_perm.mode de la estructura de control asociada a shmid tomando los valores de la estructura apuntada por buff.

IPC_RMID: elimina el identificador de memoria compartida especificado por shmid del sistema, destruyendo el segmento de memoria compartida y las estructuras de control asociadas. Si el segmento está siendo utilizado por más de un proceso, entonces la clave asociada toma el valor IPC_PRIVATE y el segmento de memoria es eliminado, el segmento desaparecerá cuando el último proceso que lo utiliza notifique su desconexión del segmento. Esta operación sólo la podrán utilizar aquellos procesos que posean privilegios de acceso a recurso apropiados, para llevar a cabo esta comprobación el sistema considerará el identificador de usuario efectivo del proceso y lo comparará con los campos shm_perm_id y shm_perm_cuid de la estructura de control asociada a la región de memoria compartida.

SHM_LOCK: bloquea la zona de memoria compartida especificada por shmid. Este comando sólo puede ejecutado por procesos con privilegios de acceso apropiados.

SHM_UNLOCK: desbloquea la región de memoria compartida especificada por shmid. Esta operación, al igual que la anterior, sólo la podrán ejecutar aquellos procesos con privilegios de acceso apropiados.

La función shmctl retornará el valor 0 si se ejecuta con éxito, o -1 si se produce un error, tomando además la variable global errno el valor del código del error producido.*/
