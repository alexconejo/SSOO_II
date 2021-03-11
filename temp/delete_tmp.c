#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

int main (){
    time_t t= time(NULL);
    pid_t pid;
    char *const parmList[] = {"-r", "./" ,"~/Escritorio/SSOO2/temp" NULL};
    char *const envParms[] = {NULL};
    struct tm tiempoLocal = *localtime(&t);
    if((pid=fork())==-1)
        perror("fork error \n");
    else if (pid == 0){
        execve("/bin/cp", parmList, envParms);
        printf("Error inesperado \n");
        exit(EXIT_FAILURE);
    }
    return 0;
}