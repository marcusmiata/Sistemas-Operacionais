#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <signal.h>
#define max 10

int main()
{   
    pid_t p1, p2, p3;
    int espera;

    p1 = fork();
    if(p1){
        if(p1>0){
            p2 = fork();
        }
        if(p2 > 0){
            p3 = fork();
        }
    }


}