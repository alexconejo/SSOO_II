#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h>

void Handler(int sig);

void CommandCpModelFile(char * p_exam_type, char *p_dni){
    char command_cp [100] = "";
    char model_name [20]  = "./utils/MODELO";
    
    strcat(model_name, p_exam_type);
    strcat(model_name, ".pdf");

    //Comprobamos que el directorio estudiantes y los ficheros de los modelos
    //existen.
    if(opendir("./utils/estudiantes") && fopen(model_name, "r")){
        strcpy(command_cp, "cp ./utils/MODELO");
        strcat(command_cp, p_exam_type);
        strcat(command_cp, ".pdf ./utils/estudiantes/");
        strcat(command_cp, p_dni);
        //Copiamos el correspondiente fichero del modelo en los directorios de
        //los estudiantes dependiendo el modelo de examen 
        system(command_cp);
    }
}

void CopyModelFile(FILE *p_file){
    char buffer[100]  = "";
    char separator[]  = " ";
    char *p_dni       = "";
    char *p_exam_type = "";

    while(fgets(buffer,100,(FILE *) p_file) != NULL){
        //Leemos el dni y el tipo de examen del fichero estudiantes_p1.text    
        p_dni = strtok(buffer, separator);
        p_exam_type = strtok(NULL,separator);
        CommandCpModelFile(p_exam_type, p_dni);
    }
} 

int main (){
    FILE *p_file;

    //Activamos el manejador
    signal(SIGINT, &Handler);

    if(p_file=fopen("utils/estudiantes_p1.text","r")){
        CopyModelFile(p_file);
        fclose(p_file);
        exit(0);
        return 0;
    }

    printf("Archivo no existente \n"); 
    exit(-1);   
    return -1;
}

void Handler(int sig){
    printf("Process kill: %d\n",getpid());
    exit(0);
}