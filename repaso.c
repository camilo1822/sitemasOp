#include <stdio.h>
#include <unistd.h>

main(){
 printf("hola");
 fork();
 printf("mundo");
 fork();
 printf("!");
}
