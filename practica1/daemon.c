#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <syslog.h>
#include <fcntl.h>
#include <errno.h>

int daemoncode(void);
int main (){
    daemoncode();
    exit(0);
    return 0;
}

int daemoncode(void){
        umask(0);
        
        pid_t sid = setsid();
        if (sid < 0) {
            perror("new SID failed\n");
            exit(EXIT_FAILURE);
        }
        while (1) {
            mkdir("./backup", 0777);
            system("cp -r estudiantes backup");
            sleep(20); /* se activa cada 60 segundos*/
        }
        return 0;
    
        
}
