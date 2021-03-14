#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void Handler(int sig);
void CreateDirectories(FILE *file);

int main (){
    FILE *file;
    
    //Activamos el manejador
    signal(SIGINT, &Handler);

    if(file=fopen("utils/estudiantes_p1.text","r")){
        CreateDirectories(file);
        fclose(file);
        exit(0);
        return 0;
    }

    printf("Archivo no existente \n"); 
    exit(-1);   
    return -1;
}

void CreateDirectories(FILE *file){
    char buffer[100]        = "";
    char separator[]        = " ";
    char *p_dni             = "";
    char directory_name[50] = "";

    while(fgets(buffer,100,(FILE *) file) != NULL){    
        strcpy(directory_name, "");
        //Leemos el dni del fichero estudiantes_p1.text
        p_dni = strtok(buffer, separator);
        strcat(directory_name, "./utils/estudiantes/");
        strcat(directory_name, p_dni);
        //Creamos el directorio estudiantes y un directorio por estudiante
        //donde su nombre sera el dni del estudiante.
        mkdir("./utils/estudiantes", 0777);
        mkdir(directory_name, 0777);
    }
} 

void Handler(int sig){
    printf("Process kill: %d\n",getpid());
    exit(0);
}