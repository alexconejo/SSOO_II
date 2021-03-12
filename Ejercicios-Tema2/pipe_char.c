#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include <string.h>


int main(int argc, char *argv[]){
    int tuberiaHijoPadre[2], nbytesTuberiaHijoPadre;
    int tuberiaPadreHijo[2], nbytesTuberiaPadreHijo;

    pid_t pid;
    char readbufferTuberiaHijoPadre[80];
    char readbufferTuberiaPadreHijo[80];

    pipe(tuberiaHijoPadre);
    pipe(tuberiaPadreHijo);


    if((pid = fork())==-1)
        perror("Error al crear el proceso hijo \n");
    if(pid==0){
        close(tuberiaHijoPadre[0]);
        close(tuberiaPadreHijo[1]);
        nbytesTuberiaPadreHijo = read(tuberiaPadreHijo[0], readbufferTuberiaPadreHijo, sizeof(readbufferTuberiaPadreHijo));
        printf("Mensaje recibido en hijo: %s \n", readbufferTuberiaPadreHijo);
        for (int indice = 0; readbufferTuberiaPadreHijo[indice] != '\0'; ++indice){
            readbufferTuberiaPadreHijo[indice] = toupper(readbufferTuberiaPadreHijo[indice]);
        }

        write(tuberiaHijoPadre[1], readbufferTuberiaPadreHijo, (strlen(readbufferTuberiaPadreHijo)+1));
        
    }
    else{
        close(tuberiaHijoPadre[1]);
        close(tuberiaPadreHijo[0]);

        
        

        write(tuberiaPadreHijo[1], argv[1], (strlen(argv[1])+1));
        nbytesTuberiaHijoPadre= read(tuberiaHijoPadre[0], readbufferTuberiaHijoPadre, sizeof(readbufferTuberiaHijoPadre));
        printf("Mensaje recibido en padre: %s \n", readbufferTuberiaHijoPadre);

    }

}