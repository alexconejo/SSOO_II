#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

void manejador(int sig);

int createExtension(char * grade, char *DNI){
    FILE* fileGrade;
    char txtPath [100]="./utils/estudiantes/";
    int minimumGrade, minimumGradeRest;
    char minimumGradeArray[2];
    

    strcat(txtPath, DNI);
    strcat(txtPath, "/nota.txt");

    minimumGrade=atoi(grade);
    minimumGradeRest=10-minimumGrade;
    sprintf(minimumGradeArray, "%d", minimumGradeRest);

    if(fileGrade = fopen(txtPath, "w+")){
        fputs("La nota que debes obtener en este nuevo examen para superar la prueba es ", fileGrade);
        fputs(minimumGradeArray, fileGrade);
        fclose(fileGrade);
    }    
    return minimumGrade;

}

float createDirectory(FILE *file){
    char buffer[100];
    char separator[] = " ";
    int minimumGrade=0, numberStudents=0;

    while(fgets(buffer,100,(FILE *) file) != NULL){    
        char *DNI = strtok(buffer, separator);
        strtok(NULL,separator);
        char *grade =strtok(NULL, separator);
        minimumGrade+=createExtension(grade, DNI); 
        numberStudents++;
    }
    return (minimumGrade/numberStudents);

} 

int main (int argc, char *argv[]){
    FILE *file;
    char DNI [8];
    int minimumGrade=0;
    int average;
    char msg[8];
    signal(SIGINT, &manejador);

    
    if(file=fopen("utils/estudiantes_p1.text","r")){
        average= createDirectory(file);
        printf("%i", average);
        fclose(file);
        sprintf(msg, "%d", average);
        write(atoi(argv[0]), msg, strlen(msg)+1);
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