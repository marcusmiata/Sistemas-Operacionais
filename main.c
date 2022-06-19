#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <signal.h>
#include "F1.h"
#include <pthread.h>

#define max 10

void *thr(){
    signal(SIGUSR1, retiradeF1);
    sleep(10);
}

int main()
{   
    pid_t p[7] = {-1,-1,-1,-1,-1,-1,-1};
    int espera;

    p[3] = fork();
    if(p[3]){ 
        if(p[3] > 0)
        { 
            p[0] = fork();
        }
        if(p[0] > 0)
        {
            p[1] = fork();
        }
        if(p[1] > 0)
        {
            p[2] = fork();
        }
        if(p[2] > 0)
        { 
            p[4] = fork();
        }
        if(p[4] > 0)
        {
            p[5] = fork();
        }
    }

    //PROCESSO PAI
    if(p[0] > 0 && p[1] > 0 && p[2] > 0 && p[3] > 0 && p[4] > 0 && p[5] > 0){
        waitpid(p[0], NULL, -1);
        waitpid(p[1], NULL, -1);
        waitpid(p[2], NULL, -1);
    }       

    //PROCESSO 1
    if(p[0] == 0)
    { 
        FIFO(p[3]);
        exit(0);
    }

    //PROCESSO 2
    if(p[1] == 0)
    { 
        FIFO(p[3]);
        exit(0);
    }
    
    //PROCESSO 3
    if(p[2] == 0)
    {   
        FIFO(p[3]);
        exit(0);
    }

    if(p[3] == 0)
    {
        pthread_t thread;
        //pthread_create(&thread, NULL, thr,NULL);
        while(1)
        {
         signal(SIGUSR1, retiradeF1);
         sleep(10);
        }
    }

    if(p[4] == 0)
    {
        exit(0);
    }

    if(p[5] == 0)
    {
        exit(0);
    }
}
