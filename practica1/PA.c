#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void manejador(int sig);
void createDirectory(FILE *file){
    char buffer[100];
    char separator[] = " ";

    while(fgets(buffer,100,(FILE *) file) != NULL){    
        char *DNI = strtok(buffer, separator);
        char directoryName [18]= "./estudiantes/";
        strcat(directoryName, DNI);
        mkdir("./estudiantes", 0777);
        mkdir(directoryName, 0777);
    }
} 

int main (){
    FILE *file;
    char DNI [8];
    signal(SIGINT, &manejador);

    if(file=fopen("estudiantes_p1.text","r")){
        createDirectory(file);
        fclose(file);
        exit(0);
        return 0;
    }

    printf("Archivo no existente \n"); 
    exit(-1);   
    return -1;
}


void manejador(int sig){
    printf("Process kill: %d\n",getpid());
    exit(0);
}