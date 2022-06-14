#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <time.h>
#include "F1.h"

#define MEM_SZ sizeof(struct shared_area)
#define MAX 10

struct shared_area
{	
	sem_t mutex;
	int num;
	int FIFO[MAX];
};


void FIFO()
{
  	int i;
	key_t key=5678;
	struct shared_area *shared_area_ptr;
	void *shared_memory = (void *)0;
	int shmid;

	shmid = shmget(key,MEM_SZ,0666|IPC_CREAT);
	if ( shmid == -1 )
	{
		printf("shmget falhou\n");
		exit(-1);
	}
	
	shared_memory = shmat(shmid,(void*)0,0);
	
	if (shared_memory == (void *) -1 )
	{
		printf("shmat falhou\n");
		exit(-1);
	}

	shared_area_ptr = (struct shared_area *) shared_memory;

	if ( sem_init((sem_t *)&shared_area_ptr->mutex,1,1) != 0 )
        {
                printf("sem_init falhou\n");
                exit(-1);
        }
	shared_area_ptr->num = 0;

	for(;;)
	{
     srand(time(NULL));
		     sem_wait((sem_t*)&shared_area_ptr->mutex);
			if ( shared_area_ptr->num == 0 )
			{
			     for(i=0;i<10;i++)
				   shared_area_ptr->FIFO[i] = 1 + rand() % 1000;
                 shared_area_ptr->num=i;
			}
            else if (shared_area_ptr->num == 10)
            {
                for(i=0;i<10;i++)
				   printf("%d ", shared_area_ptr->FIFO[i]);
                break;
            } 
             sem_post((sem_t*)&shared_area_ptr->mutex);
	}
        exit(0);
}