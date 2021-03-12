#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void manejador(int sig);
void removeDirectory(void){

    system("rm -rf ./estudiantes");
} 

int main (){
    FILE *file;
    char DNI [8];
    signal(SIGINT, &manejador);
    removeDirectory();
    exit(0);
    return 0;
}


void manejador(int sig){
    printf("Process kill: %d\n",getpid());
    exit(0);
}