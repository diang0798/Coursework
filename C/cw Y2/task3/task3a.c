#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include "coursework.h"
#include "linkedlist.h"


struct element *head;
struct element *tail;
void * producer();
void * consumer();
void visualisation(struct element **head, struct element **tail);

sem_t sync, delay_consumer;
int counter = 0;
int num_produced = 0;
int num_consumed = 0;
char star = '*';


int main()
{
	struct element *head = NULL;
	struct element *tail = NULL;
	sem_init(&sync, 0, 1);
	sem_init(&delay_consumer, 0, 0);
	pthread_t producer0,consumer0;
	pthread_create(&producer0, NULL, producer, NULL);
	pthread_create(&consumer0, NULL, consumer, NULL);
	pthread_join(producer0,NULL);
	pthread_join(consumer0,NULL);

}


void *producer()
{
	while(num_produced < MAX_NUMBER_OF_JOBS)
	{
		sem_wait(&sync);
		addLast((void*)&star, &head, &tail);
		counter++;
		num_produced++;
		printf("Producer, Produced = %d, Consumed = %d: ", num_produced, num_consumed);
		visualisation(&head, &tail);
		if(counter > 0)
		{
			sem_post(&delay_consumer);
		}
		sem_post(&sync);
		while(counter == MAX_BUFFER_SIZE && num_produced != MAX_NUMBER_OF_JOBS);
		
	}
}


void *consumer()
{
	sem_wait(&delay_consumer);
	while(num_consumed < MAX_NUMBER_OF_JOBS)
	{
		sem_wait(&sync);
		removeFirst(&head, &tail);
		counter--;
		num_consumed++;
		printf("Consumer, Produced = %d, Consumed = %d: ", num_produced, num_consumed);
		visualisation(&head, &tail);
		sem_post(&sync);
		if(counter == 0 && num_consumed != MAX_NUMBER_OF_JOBS)
		{
			sem_wait(&delay_consumer);
		}
		while(counter == 0 && num_consumed != MAX_NUMBER_OF_JOBS);
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
