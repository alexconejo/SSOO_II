#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <syslog.h>
#include <fcntl.h>
#include <errno.h>

#define LECTURA 0
#define ESCRITURA 1

void Handler(int sig);
void WriteLog(char log_text[300]);


int main (int argc, char *argv[]){

    pid_t pid_a, pid_b, pid_c, pid_daemon;
    int  tuberia[2]        = {};
    int  estado_a          = 0;
    int  estado_b          = 0;
    int  estado_c          = 0;
    char *const PARMLIST[] = {NULL};
    char *const ENVPARMS[] = {NULL};
    char wr_tuberia[100]   = "", buffer_pipe[4] = "";
    char log_text[300]     = "";

    //Activamos el manejador
    signal(SIGINT, &Handler);

    //Abrimos la tuberia que usaremos para conseguir la media calculada
    //por PC
    pipe(tuberia);
    sprintf(wr_tuberia, "%d", tuberia[ESCRITURA]);

    strcat(log_text, "******** Log del sistema ********\n");
    WriteLog(log_text);
    
    //Creamos el proceso hijo que ejecutara el codigo de PA
    if((pid_a=fork())==-1){
        perror("El proceso A ha generado un error de fork \n");
    }
    else if (pid_a==0){
        printf("El proceso hijo A con pid: %d ha iniciado\n", getpid());
        execve("./exec/PA.o", PARMLIST, ENVPARMS);
    }
    else{
        printf("El proceso manager con pid: %d ha iniciado\n", getpid());
        wait(&estado_a);
        //Esperamos la finalizacion del proceso y confirmamos la creacion de directorios
        strcat(log_text, "Creación de directorios finalizada.\n");
        WriteLog(log_text);

        //Creamos el proceso hijo que ejecutara el codigo de PB
        pid_b=fork();
        if(pid_b==-1){
            perror("El proceso B ha generado un error de fork \n");
            exit(1);
        }
        else if(pid_b==0){
            printf("El proceso hijo B con pid: %d ha iniciado\n", getpid());
            execve("./exec/PB.o", PARMLIST, ENVPARMS);
        }
        else{
            //Creamos el proceso hijo que ejecutara el codigo de PC
            if((pid_c=fork())==-1){
                perror("El proceso C ha generado un error de fork \n");
                exit(1);
            }
            else if(pid_c==0){
                printf("El proceso hijo C con pid: %d ha iniciado\n", getpid());
                if(execl("./exec/PC.o", wr_tuberia, NULL)==-1){
                    perror("El proceso C ha generado un error de execl\n");
                    exit(1);
                }
            }
            else{
                wait(&estado_b);

                //Leemos la nota media de la tuberia
                read(tuberia[LECTURA], buffer_pipe, sizeof(buffer_pipe));
                //Esperamos la finalizacion del proceso y confirmamos la copia de los modelos de examen
                strcat(log_text, "Copia de modelos de examen, finalizada.\n");
                WriteLog(log_text);
            }
            wait(&estado_c);

            //Esperamos la finalizacion de los procesos ,confirmamos la creacion del archivo nota.txt y escribimos la nota media
            //en el archivo log
            strcat(log_text, "Creación de archivos con nota necesaria para alcanzar la nota de corte, finalizada.\n");
            strcat(log_text, "La nota media de la clase es: ");
            strcat(log_text, buffer_pipe);
            WriteLog(log_text);

            if((pid_daemon=fork())==-1){
                perror("El proceso C ha generado un error de fork \n");
                exit(1);
            }
            else if(pid_daemon==0){
                printf("El proceso Daemon con pid: %d ha iniciado\n", getpid());
                if(execve("./exec/daemon.o", PARMLIST, ENVPARMS)==-1){
                    perror("El proceso Daemon ha generado un error de execl\n");
                    exit(1);
                }
            }
            //Confirmamos en el archivo Log el fin del programa
            strcat(log_text, "\nFIN DE PROGRAMA");
            WriteLog(log_text);
        }
    }
    return EXIT_SUCCESS;
}

void Handler(int sig){
    pid_t pid_d;
    char *const PARMLIST[] = {NULL};
    char *const ENVPARMS[] = {NULL};

    printf("Process kill: %d\n",getpid());
    //Creamos el proceso hijo que ejecutara el codigo de PD en caso de que salte
    //el manejador
    if((pid_d=fork())==-1){
        perror("El proceso D ha generado un error de fork \n");
    }
    else if (pid_d==0){
        printf("El proceso hijo D con pid: %d ha iniciado\n", getpid());
        if(execve("./exec/PD.o", PARMLIST, ENVPARMS)==-1){
            perror("El proceso D ha generado un error de execl\n");
        }
    }
    
    exit(0);
}

void WriteLog(char log_text[300]){

    FILE *p_file_log;
    
    if(p_file_log = fopen("./utils/log.txt", "w")){
        fputs(log_text, p_file_log);
        fclose(p_file_log);
    }  
}

