#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char *argv[]){
    int estado;
    int causa;
    pid_t p = fork();
    unsigned long long n=0;
    
    if(argc>=2){
        int numero=atoi(argv[1]);
        printf("numero %i", )
        if(p==-1){
            perror("Error al crear proceso hijo");
            return EXIT_FAILURE;
        }
        else if(p==0){
            printf("Proceso hijo\n");
            if(numero>0){
                    n=1;
                    for(int j=1;j<=numero;j++){
                        n*=j;
                    }
                    printf("El factorial de n hecho por el proceso hijo %i es %d \n", getpid(), estado);
            }
            exit(n);
        }
        else{
            printf("Proceso padre\n");
            wait(&estado);
            pid_t p=fork();
            

            if(p==-1){
                perror("Error al crear proceso hijo");
                return EXIT_FAILURE;
            }
            else if(p==0){
                int n=0;
                for(int j=1;j<=numero;j++){
                    for(int k=2;k<=j;k++){
                        if(j%k==0){
                            n++;
                        }
                    }
                }
               
            }   
            else{
                wait(&estado);
            }
        }
    }
}