#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <signal.h>
#include "F1.h"

#define max 10

void trata(int signum)
{
    printf("Chegou o sinal %d em p4", signum);
    exit(1);
}

int main()
{   
    pid_t p1, p2, p3, p4;
    int espera;

    p4 = fork();
    if(p4){ 
        if(p4 > 0)
        { 
            p1 = fork();
        }
        if(p1>0)
        {
            p2 = fork();
        }
        if(p2 > 0)
        {
            p3 = fork();
        }
    }

    //PROCESSO PAI
    if(p1 > 0 && p2 > 0 && p3 > 0 && p4 > 0){
        waitpid(p1, NULL, -1);
        waitpid(p2, NULL, -1);
        waitpid(p3, NULL, -1);
    }       

    //PROCESSO 1
    if(p1 == 0)
    { 
        FIFO(p4);
        exit(0);
    }

    //PROCESSO 2
    if(p2 == 0)
    { 
        FIFO(p4);
        exit(0);
    }
    
    //PROCESSO 3
    if(p3 == 0)
    {   
        FIFO(p4);
        exit(0);
    }

    if(p4 == 0)
    {
        signal(SIGUSR1, retiradeF1);
        sleep(10);
    }

}
