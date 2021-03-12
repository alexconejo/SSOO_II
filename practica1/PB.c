#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void manejador(int sig);

void introducePDF(char * examType, char *DNI){
    char command [100];

    strcpy(command, "cp ./MODELO");
    strcat(command, examType);
    strcat(command, ".pdf ./estudiantes/");
    strcat(command, DNI);
    system(command);
    //Comprobar que el archivo existe o hacer enlace duro con ln
}

void createDirectory(FILE *file){
    char buffer[100];
    char separator[] = " ";

    while(fgets(buffer,100,(FILE *) file) != NULL){    
        char *DNI = strtok(buffer, separator);
        char *examType = strtok(NULL,separator);
        introducePDF(examType, DNI);
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