#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <semaphore.h>
#include "F1.h"
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

#define MEM_SZ sizeof(struct shared_area)
#define MAX 10

struct shared_area
{	
	sem_t mutex;
	int num;
	int FIFO[MAX];
};

void retiradeF1(int sinal)
{	
  	int i;
	key_t key=5678;
	struct shared_area *shared_area_ptr;
	void *shared_memory = (void *)0;
	int shmid;

	//Criar processos filhos para pipe
	int pid1;
	int canal[2];
	int vetor[10];

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
	
	if ( sem_init((sem_t*)&shared_area_ptr->mutex,1,1) != 0 )
	{
		printf("sem_init falhou\n");
		exit(-1);
	}


	if(pipe(canal) == -1){printf("Erro ao criar pipe.");}
	
	pid1 = fork();
	
	if(pid1 > 0)
	{
	sem_wait((sem_t*)&shared_area_ptr->mutex);
	if ( shared_area_ptr->num == 10)
	{	
		for(i=0;i<10;i++)
			vetor[i] = shared_area_ptr->FIFO[i];
		shared_area_ptr->num = 0;
	}
	sem_post((sem_t*)&shared_area_ptr->mutex);
	write(canal[1], vetor, sizeof(int)*10);
	close(canal[1]);
	wait(NULL);
	return;
	}

	//PROCESSO 5
	if(pid1 == 0)
	{
		read(canal[0], vetor, sizeof(int)*10);
		for(i = 0; i < 10; i++)
			printf("%d ", vetor[i]);
		printf("\n");
		fflush(stdout);
		close(canal[0]);
		exit(0);
	}
}

void retiradeF1_2(int sinal)
{	
  	int i;
	key_t key=5678;
	struct shared_area *shared_area_ptr;
	void *shared_memory = (void *)0;
	int shmid;

	//Criar processos filhos para pipe
	int pid;
	int canal[2];
	int vetor[10];

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
	
	if ( sem_init((sem_t*)&shared_area_ptr->mutex,1,1) != 0 )
	{
		printf("sem_init falhou\n");
		exit(-1);
	}


	if(pipe(canal) == -1){printf("Erro ao criar pipe.");}
	
	pid = fork();
	
	if(pid > 0)
	{
	sem_wait((sem_t*)&shared_area_ptr->mutex);
	if ( shared_area_ptr->num == 10)
	{	
		for(i=0;i<10;i++)
			vetor[i] = shared_area_ptr->FIFO[i];
		shared_area_ptr->num = 0;
	}
	sem_post((sem_t*)&shared_area_ptr->mutex);
	write(canal[1], vetor, sizeof(int)*10);
	close(canal[1]);
	wait(NULL);
	return;
	}

	//PROCESSO 6
	if(pid == 0)
	{
		read(canal[0], vetor, sizeof(int)*10);
		for(i = 0; i < 10; i++)
			printf("%d ", vetor[i]);
		printf("\n");
		fflush(stdout);
		close(canal[0]);
		exit(0);
	}
}