#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>


#define MEM_SZ sizeof(struct shared_area)
#define MAX 10

struct shared_area{	
	int num;
	int fila[MAX];
};

void removeF2(int* vet)
{
  	int i;
	key_t key=1234;
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

	shared_area_ptr->num=0;
	for(i=0;i<MAX;i++)
		shared_area_ptr->fila[i]=0;
	
	//for(;;)
	//{
		if ( shared_area_ptr->num > 0 )
		{
			for(i=0;i<shared_area_ptr->num;i++)
				vet[i] = shared_area_ptr->fila[i]; 
			shared_area_ptr->num=0;
		}
        else{
            printf("fila vazia");
        }
	//}

    return;
    //exit(0);
}