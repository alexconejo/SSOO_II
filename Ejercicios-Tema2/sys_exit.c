#include <stdio.h>
#include <stdlib.h>

int main (){
    FILE *file;

    if(file=fopen("hola","r")){
        fclose(file);
        printf("Archivo existente \n");
        exit(0);
        return 0;
    }

    printf("Archivo no existente \n"); 
    exit(-1);   
    return -1;

}