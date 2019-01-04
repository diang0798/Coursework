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
void visualisation(struct element **head, struct element **tail);

sem_t sync, empty, full;
int num_produced = 0;
int num_consumed = 0;
char star = '*';
int i,j;

int main()
{
	int producer_id[NUMBER_OF_PRODUCERS], consumer_id[NUMBER_OF_CONSUMERS];
	struct element *head = NULL;
	struct element *tail = NULL;
	sem_init(&sync, 0, 1);
	sem_init(&empty, 0, MAX_BUFFER_SIZE);
	sem_init(&full, 0, 0);
	pthread_t producer_t[NUMBER_OF_PRODUCERS], consumer_t[NUMBER_OF_CONSUMERS];
	for(i = 0; i < NUMBER_OF_PRODUCERS; i++)
	{
		producer_id[i] = i;
		pthread_create(&producer_t[i], NULL, producer, (void*) &producer_id[i]);
	}
	for(j = 0; j< NUMBER_OF_CONSUMERS; j++)
	{
		consumer_id[j] = j;
		pthread_create(&consumer_t[j], NULL, consumer, (void *) &consumer_id[j]);
	}
	for(i = 0; i < NUMBER_OF_PRODUCERS; i++)
	{
		pthread_join(producer_t[i],NULL);
	}
	for(j= 0; j < NUMBER_OF_CONSUMERS; j++)
	{
		pthread_join(consumer_t[j],NULL);
	}
}


void *producer(void* arg)
{
	while(num_produced < MAX_NUMBER_OF_JOBS)
	{
		sem_wait(&empty);
		sem_wait(&sync);
		if(num_produced < MAX_NUMBER_OF_JOBS)
		{
			addLast((void*)&star, &head, &tail);
			num_produced++;
			printf("Producer Id = %d, Produced = %d, Consumed = %d: ", *((int *) arg), num_produced, num_consumed);
			visualisation(&head, &tail);
		}
		sem_post(&sync);
		sem_post(&full);
		if(num_produced == MAX_NUMBER_OF_JOBS)
		{
			for(i = 0; i < NUMBER_OF_CONSUMERS; i++)
			{
				sem_post(&full);
			}
		}
		
	}
}


void *consumer(void* arg)
{
	while(num_consumed < MAX_NUMBER_OF_JOBS)
	{
		sem_wait(&full);
		sem_wait(&sync);
		if(num_consumed < MAX_NUMBER_OF_JOBS)
		{
			removeFirst(&head, &tail);
			num_consumed++;
			printf("Consumer Id = %d, Produced = %d, Consumed = %d: ",*((int*) arg) , num_produced, num_consumed);
			visualisation(&head, &tail);
		}
		sem_post(&sync);
		sem_post(&empty);
	}
}


void visualisation(struct element **head, struct element **tail)
{
	struct element* temp = *head;
	while(temp != NULL)
	{
		char* star = temp->pData;
		temp = temp->pNext;
		printf("%c", *star);
	}
	printf("\n");
}
