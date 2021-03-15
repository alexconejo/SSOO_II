/***********************************************************
 * Project         : Practica 1 de Sistemas Opertivos II
 * 
 * Program Name    : PD.c
 * 
 * Author          : Álex Conejo
 * 
 * Purpose         : Limpieza de archivos en caso de que 
 *                   el manejador salte
 * *********************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

void removeDirectory(void){

    //Comprobamos que el directorio estudiantes existe y lo borramos
    if(opendir("./utils/estudiantes")){
        system("rm -rf ./utils/estudiantes");
    }  
} 

int main (){
    removeDirectory();
    exit(0);
    return 0;
}
