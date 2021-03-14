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
