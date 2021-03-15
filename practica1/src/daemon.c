/***********************************************************
 * Project         : Practica 1 de Sistemas Opertivos II
 * 
 * Program Name    : daemon.c
 * 
 * Author          : Álex Conejo
 * 
 * Purpose         : Proceso demonio que va haciendo una 
 *                   copia de seguridad cada minuto
 * *********************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <syslog.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>

int DaemonCode(void);
int main (){
    DaemonCode();
    exit(0);
    return 0;
}

int DaemonCode(void){
    //Creamos el nuevo SID para el proceso hijo
    pid_t sid = setsid();

    //Cambiamos el modo de la máscara de creacion de archivo
    umask(0);
    
    if (sid < 0) {
        perror("new SID failed\n");
        exit(EXIT_FAILURE);
    }
    while (1) {
        //Comprobamos la existencia del directorio estudiantes y copiamos su carpeta en el backup
        if(opendir("./utils/estudiantes")){
            system("cp -r ./utils/estudiantes ./utils/backup");
        }

        sleep(60); /* se activa cada 60 segundos*/
    }
    
    return 0;
        
}
