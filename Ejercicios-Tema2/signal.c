#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void manejador(int sig);

int main (int argc, char *argv[]){

    int estado;
    pid_t pid = fork();

    if(pid==0){
        signal(SIGUSR1, manejador);
        printf("Proceso hijo %d a la espera de captura de senial\n", getpid());
        sleep(2);
        kill(getppid(), SIGUSR2);
    }
    else{
        signal(SIGUSR2, manejador);
        printf("Proceso padre %d a la espera de captura de senial\n", getpid());
        sleep(2);
        kill(pid, SIGUSR1);
        wait(&estado);
    }

}

void manejador(int sig){
    if(sig==SIGUSR1)
        printf("Senial enviada por el padre: %d\n", sig);
    else
        printf("Senial enviada por el hijo: %d\n", sig);
}