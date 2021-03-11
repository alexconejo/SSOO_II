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
    char output[10]; //array donde guardo la fecha
    strftime(output,10,"%d/%m/%y",tlocal); //formato para guardar la fecha obtenido en *tlocal como dd/mm/yyyy
    printf("%s\n",output);
    
    if((pid=fork())==-1)
        perror("fork error \n");
    else if (pid == 0){
        execve("/bin/cp", parmList, envParms);
        printf("Error inesperado \n");
        exit(EXIT_FAILURE);
    }
    return 0;
}