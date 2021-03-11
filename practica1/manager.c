#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LECTURA 0
#define ESCRITURA 1

void manejador(int sig);
void writelog(char logText[300]);

int main (int argc, char *argv[]){

    int tuberia[2];
    int estado1, estado2, estado3;
    pid_t pidA, pidB, pidC;
    char *const parmList[] = {NULL};
    char *const envParms[] = {NULL};
    char wr_tuberia[100], buffer_pipe[4];
    char logText[300];

    strcat(logText, "******** Log del sistema ********\n");
    writelog(logText);
    
    signal(SIGINT, manejador);
    pipe(tuberia);
    sprintf(wr_tuberia, "%d", tuberia[ESCRITURA]);

    if((pidA=fork())==-1){
        perror("El proceso A ha generado un error de fork \n");
    }
    else if (pidA==0){
        printf("El proceso hijo A con pid: %d ha iniciado\n", getpid());
        execve("./PA", parmList, envParms);
    }
    else{
        printf("El proceso manager con pid: %d ha iniciado\n", getpid());
        wait(&estado1);
        strcat(logText, "Creación de directorios finalizada.\n");
        writelog(logText);

        pidB=fork();
        if(pidB==-1){
            perror("El proceso B ha generado un error de fork \n");
            exit(1);
        }
        else if(pidB==0){
            printf("El proceso hijo B con pid: %d ha iniciado\n", getpid());
            execve("./PB", parmList, envParms);
        }
        else{
            if((pidC=fork())==-1){
                perror("El proceso C ha generado un error de fork \n");
                exit(1);
            }
            else if(pidC==0){
                printf("El proceso hijo C con pid: %d ha iniciado\n", getpid());
                if(execl("./PC", wr_tuberia, NULL)==-1){
                    perror("El proceso C ha generado un error de execl\n");
                    exit(1);
                }
            }
            else{
                wait(&estado2);
                read(tuberia[LECTURA], buffer_pipe, sizeof(buffer_pipe));
                strcat(logText, "Copia de modelos de examen, finalizada.\n");
                writelog(logText);
            }
            wait(&estado3);  
            strcat(logText, "Creación de archivos con nota necesaria para alcanzar la nota de corte, finalizada.\n");
            strcat(logText, "La nota media de la clase es: ");
            strcat(logText, buffer_pipe);
            writelog(logText);
            writelog(logText);
            writelog(logText);
            
        }
    }
    return EXIT_SUCCESS;
}

void manejador(int sig){
    printf("Process kill: %d\n",getpid());
    exit(0);
}

void writelog(char logText[300]){

    FILE *fileLog;
    
    
    if(fileLog = fopen("./log.txt", "w")){
        fputs(logText, fileLog);
        fclose(fileLog);
    }  
}