
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void handler (int);

int main(int argc, char *argv[]){
    pid_t pid1, pid2;
    int status1, status2;

    pid1=fork();
    if(pid1==0) {
        execl("/usr/bin/cal", "cal", argv[1], argv[2], NULL);
        _exit(status1);
    }else{
        fprintf(stderr,"\nProceso padre esperando por el hijo %d\n\n", pid1);
        wait(&status1);
        fprintf(stderr,"Hijo %d terminado.\n\n", pid1);
    }

    pid2 = fork();
    if(pid2==0) {
        signal(SIGUSR1, handler);
        sleep(50);
        _exit(status2);
        
    }else{
        fprintf(stderr,"Proceso padre esperando por el hijo %d\n", pid2);
        wait(&status2);
    }
       
    fprintf(stderr,"Proceso padre %d terminado\n", getppid());

    return 0;
}

void handler (int sig) {
    fprintf(stderr,"\nRecibida la señal SIGUSR1!\n");
    fprintf(stderr,"Hijo %d terminado.\n", getpid());
    exit(0);
}