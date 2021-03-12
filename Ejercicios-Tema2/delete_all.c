#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main (){
    pid_t pid;
    char *const parmList[] = {"./", "-name", "*.tmp", "-print", "delete", NULL};
    char *const envParms[] = {NULL};

    if((pid=fork())==-1)
        perror("fork error \n");
    else if (pid == 0){
        execve("/bin/find", parmList, envParms);
        printf("Error inesperado \n");
        exit(EXIT_FAILURE);
    }
    return 0;
}