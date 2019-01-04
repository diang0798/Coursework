#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include "coursework.h"
#include "linkedlist.h"


struct element *head;
struct element *tail;
void * producer(void* arg);
void * consumer(void* arg);
sem_t sync, empty, full;
int num_produced = 0;
int num_consumed = 0;
int i,j;
double sum_rTime = 0;
double sum_trTime = 0;


int main()
{
	int producer_id[NUMBER_OF_PRODUCERS], consumer_id[NUMBER_OF_CONSUMERS];
	struct element *head = NULL;
	struct element *tail = NULL;
	sem_init(&sync, 0, 1);
	sem_init(&empty, 0, MAX_BUFFER_SIZE);
	sem_init(&full, 0, 0);
	pthread_t producer_t[NUMBER_OF_PRODUCERS], consumer_t[NUMBER_OF_CONSUMERS];
	for(j = 0; j < NUMBER_OF_PRODUCERS; j++)
	{
		producer_id[j] = j;
		pthread_create(&producer_t[j], NULL, producer, (void*) &producer_id[j]);
	}
	for(j = 0; j< NUMBER_OF_CONSUMERS; j++)
	{
		consumer_id[j] = j;
		pthread_create(&consumer_t[j], NULL, consumer, (void *) &consumer_id[j]);
	}
	for(j = 0; j < NUMBER_OF_PRODUCERS; j++)
	{
		pthread_join(producer_t[j], NULL);
	}
	for(j= 0; j < NUMBER_OF_CONSUMERS; j++)
	{
		pthread_join(consumer_t[j], NULL);
	}
	sem_destroy(&sync);
	sem_destroy(&empty);
	sem_destroy(&full);
	printf("Average Response Time = %lf\n", sum_rTime/MAX_NUMBER_OF_JOBS);
	printf("Average Turn Around Time = %lf\n", sum_trTime/MAX_NUMBER_OF_JOBS); 
}


void *producer(void* arg)
{
	while(num_produced < MAX_NUMBER_OF_JOBS)
	{
		sem_wait(&empty);
		sem_wait(&sync);
		if(num_produced < MAX_NUMBER_OF_JOBS)
		{
			struct process* x = generateProcess();
			addLast(x, &head, &tail);
			num_produced++;
			printf("Producer Id = %d, Items Produced = %d, New Process Id = %d, Burst Time = %d\n",
 *((int *) arg), num_produced, x->iProcessId, x->iInitialBurstTime);
		}
		sem_post(&sync);
		sem_post(&full);
	}
}


void *consumer(void* arg)
{
	int cur_rTime = 0;
	int cur_trTime = 0;	
	while(num_consumed < MAX_NUMBER_OF_JOBS)
	{
		sem_wait(&full);
		sem_wait(&sync);
		struct process* otemp = removeFirst(&head, &tail);
		num_consumed++;
		sem_post(&sync);
		struct timeval startTime, currentTime;
		runNonPreemptiveJob(otemp, &startTime, &currentTime);
		cur_rTime = getDifferenceInMilliSeconds((otemp->oTimeCreated), startTime);
		cur_trTime = getDifferenceInMilliSeconds((otemp->oTimeCreated), currentTime);
		sum_rTime += cur_rTime;
		sum_trTime += cur_trTime;
		printf("Consumer Id = %d, Process Id = %d, Previous Burst Time = %d, New Burst Time = %d,\
 Response Time = %d, Turn Around Time = %d\n", *((int *) arg), otemp->iProcessId, otemp->iPreviousBurstTime, otemp->iRemainingBurstTime, cur_rTime, cur_trTime);
		free(otemp);
		sem_post(&empty);
	}
}



