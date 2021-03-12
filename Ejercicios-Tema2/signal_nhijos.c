#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>


void manejador(int sig);

int main (int argc, char *argv[]){
    int estado;
    int causa;
    int N=3;
    FILE *file;
    int numeros_escritos;
    for(int i=0;i<N;i++){
        pid_t p = fork();
        char numeroProceso[5];
        if(p==0){
            signal(SIGUSR1, manejador);
            printf("Proceso hijo %d a la espera de captura de senial\n", getpid());
            if(file = fopen("./numeros_hijos.txt", "w+")){
                fputs("El proceso hijo",file);
                sprintf(numeroProceso, "%d", getpid());
                fputs(numeroProceso, file);
                fputs(" ha escrito los numeros: ", file);
                for (int i=0;i<10;i++){
                    sprintf(numeroProceso, "%d", numeros_escritos);
                    fputs(numeroProceso, file);
                    fputs(", ", file); 
                    numeros_escritos++;
                }
                fputs("\n", file);
                fclose(file);
            }   
            sleep(2);
            kill(getppid(), SIGUSR2);
        }
        else{
            signal(SIGUSR2, manejador);
            printf("Proceso padre %d a la espera de captura de senial\n", getpid());
            sleep(2);
            kill(p, SIGUSR1);
            wait(&estado);
        }
    }
    
}

void manejador(int sig){
    if(sig==SIGUSR1)
        printf("Senial enviada por el padre: %d\n", sig);
    else
        printf("Senial enviada por el hijo: %d\n", sig);
}