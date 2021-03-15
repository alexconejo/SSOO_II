/***********************************************************
 * Project         : Practica 1 de Sistemas Opertivos II
 * 
 * Program Name    : PC.c
 * 
 * Author          : Álex Conejo
 * 
 * Purpose         : Creacion del archivo nota.txt en el 
 *                   directorio de cada alumno y calculo de
 *                   la media
 * *********************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

void Handler(int sig);
int WriteNote(char * grade, char *DNI);
float CreateNote(FILE *file);

int main (int argc, char *argv[]){
    FILE *p_file;
    int  minimum_grade = 0;
    int  average       = 0;
    char msg[8]        = "";

    //Activamos el manejador 
    signal(SIGINT, &Handler);

    if(p_file=fopen("utils/estudiantes_p1.text","r")){
        average = CreateNote(p_file);
        fclose(p_file);
        //Escribimos la media para pasarla por la tuberia al proceso padre
        sprintf(msg, "%d", average);
        write(atoi(argv[0]), msg, strlen(msg)+1);
        return 0;
    }

    printf("Archivo no existente \n"); 
    exit(-1);   
    return -1;
}

int WriteNote(char * grade, char *DNI){
    FILE* p_file_grade;
    char txtPath [100]           = "./utils/estudiantes/";
    int  minimum_grade           = 0;
    int  minimum_grade_rest      = 0;
    char minimum_grade_array[2]  = "";
    
    //Creamos una cadena con la ruta del fichero
    strcat(txtPath, DNI);
    strcat(txtPath, "/nota.txt");

    //Calculamos la nota minima que el estudiante debe sacar en el 
    //proximo examen para aprobar
    minimum_grade=atoi(grade);
    minimum_grade_rest=10-minimum_grade;
    sprintf(minimum_grade_array, "%d", minimum_grade_rest);

    //Escribimos en nuestro fichero la nota que hemos calulado anteriormente
    if(p_file_grade = fopen(txtPath, "w+")){
        fputs("La nota que debes obtener en este nuevo examen para superar la prueba es ", p_file_grade);
        fputs(minimum_grade_array, p_file_grade);
        fclose(p_file_grade);
    } 

    //Devolvemos la nota leida del fichero para calcular la media
    return minimum_grade;

}

float CreateNote(FILE *file){
    char buffer[100]   = "";
    char separator[]   = " ";
    int  minimum_grade = 0, number_students = 0;
    char *p_dni        = "";
    char *p_grade      = "";

    while(fgets(buffer,100,(FILE *) file) != NULL){  
        //Leemos el dni y la nota del fichero estudiantes_p1.text
        p_dni = strtok(buffer, separator);
        strtok(NULL,separator);
        p_grade =strtok(NULL, separator);
        //Calculamos y sumamos las notas de todos los estudiantes
        minimum_grade+=WriteNote(p_grade, p_dni); 
        number_students++;
    }

    //Devolvemos la media de las notas
    return (minimum_grade/number_students);

} 

void Handler(int sig){
    printf("Process kill: %d\n",getpid());
    exit(0);
}