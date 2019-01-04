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
void * boost();


sem_t sync, empty, full;
int num_produced = 0;
int num_consumed = 0;
int i,j;
struct element* listOfHead [MAX_PRIORITY];
struct element* listOfTail [MAX_PRIORITY];
int list[NUMBER_OF_PROCESSES];
double sum_rTime = 0;
double sum_trTime = 0;


int main()
{
	for(i = 0; i < MAX_PRIORITY; i++)
	{
		//struct element* head = NULL;
	//	struct element* tail = NULL;
		listOfHead[i] = NULL;
		listOfTail[i] = NULL;
	}

	sem_init(&sync, 0, 1);
	sem_init(&empty, 0, MAX_BUFFER_SIZE);
	sem_init(&full, 0, 0);

	int producer_id[NUMBER_OF_PRODUCERS], consumer_id[NUMBER_OF_CONSUMERS];
	pthread_t producer_t[NUMBER_OF_PRODUCERS], consumer_t[NUMBER_OF_CONSUMERS];
	pthread_t boost_t;

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

	pthread_create(&boost_t, NULL, boost, NULL);

	for(j = 0; j < NUMBER_OF_PRODUCERS; j++)
	{
		pthread_join(producer_t[j],NULL);
	}
	for(j= 0; j < NUMBER_OF_CONSUMERS; j++)
	{
		pthread_join(consumer_t[j],NULL);
	}

	pthread_join(boost_t, NULL);

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
			int cur_priority = x->iPriority;
			addLast(x, &listOfHead[cur_priority], &listOfTail[cur_priority]);
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
	struct timeval startTime, currentTime;
	struct process* otemp;
	struct process* otemp_list[MAX_BUFFER_SIZE];
	int cur_rTime = 0;
	int cur_trTime = 0;
	int j = 0;
	while(num_consumed < MAX_NUMBER_OF_JOBS)
	{
		sem_wait(&full);
		sem_wait(&sync);
		if(num_consumed < MAX_NUMBER_OF_JOBS)
		{
			for(i = 0; i < MAX_PRIORITY; i++)
			{
				if(listOfHead[i] != NULL)
				{
					otemp = removeFirst(&listOfHead[i], &listOfTail[i]);
					if(otemp->iRemainingBurstTime == otemp->iInitialBurstTime && otemp->iInitialBurstTime <= TIME_SLICE)
					{
						runPreemptiveJob(otemp, &startTime, &currentTime);
						cur_rTime = getDifferenceInMilliSeconds((otemp->oTimeCreated), startTime);
						sum_rTime += cur_rTime;
						cur_trTime = getDifferenceInMilliSeconds((otemp->oTimeCreated), currentTime);
						sum_trTime += cur_trTime;
						printf("Consumer = %d, Process Id = %d, Priority = %d, Previous Burst Time = %d, \
New Burst Time = %d, Response Time = %d, Turn Around Time = %d\n",*((int*) arg), otemp->iProcessId, otemp->iPriority, otemp->iPreviousBurstTime,
otemp->iRemainingBurstTime, cur_rTime, cur_trTime);
						num_consumed++;
						free(otemp);
						sem_post(&empty);
					}
					else if(otemp->iRemainingBurstTime == otemp->iInitialBurstTime)
					{
						runPreemptiveJob(otemp, &startTime, &currentTime);
						cur_rTime = getDifferenceInMilliSeconds((otemp->oTimeCreated), startTime);
						sum_rTime += cur_rTime;
						printf("Consumer = %d, Process Id = %d, Priority = %d, Previous Burst Time = %d, \
New Burst Time = %d, Response Time = %d\n",*((int*) arg), otemp->iProcessId, otemp->iPriority, otemp->iPreviousBurstTime,
otemp->iRemainingBurstTime, cur_rTime);
						addLast(otemp, &listOfHead[i], &listOfTail[i]);
						sem_post(&full);
					}
					else if(otemp->iRemainingBurstTime <= TIME_SLICE)
					{
						runPreemptiveJob(otemp, &startTime, &currentTime);
						cur_trTime = getDifferenceInMilliSeconds((otemp->oTimeCreated), currentTime);
						sum_trTime += cur_trTime;
						printf("Consumer = %d, Process Id = %d, Priority = %d, Previous Burst Time = %d, \
New Burst Time = %d, Turn Around Time = %d\n",*((int*) arg), otemp->iProcessId, otemp->iPriority, otemp->iPreviousBurstTime,
otemp->iRemainingBurstTime, cur_trTime);
						num_consumed++;
						free(otemp);
						sem_post(&empty);
					}
					else
					{
						runPreemptiveJob(otemp, &startTime, &currentTime);
						printf("Consumer = %d, Process Id = %d, Priority = %d, Previous Burst Time = %d, \
New Burst Time = %d\n",*((int*) arg), otemp->iProcessId, otemp->iPriority, otemp->iPreviousBurstTime,
otemp->iRemainingBurstTime);
						addLast(otemp, &listOfHead[i], &listOfTail[i]);
						sem_post(&full);
					}
				}
			}
		}
		sem_post(&sync);
	}
}

void *boost()
{
	while(num_consumed < MAX_NUMBER_OF_JOBS)
	{
		struct timeval lastTime, currentTime;
		int i;
		sem_wait(&sync);
		for(i = 0; i < 32; i++)
		{
			if(listOfHead[i] != NULL)
			{
				lastTime = ((struct process *)(listOfHead[i]-> pData))->oMostRecentTime;
				gettimeofday(&currentTime, NULL);
				if(getDifferenceInMilliSeconds(lastTime, currentTime) > BOOST_INTERVAL)
				{
				struct process* otemp = removeFirst(&listOfHead[i], &listOfTail[i]);
				printf("Boost Priority: Process Id = %d, Priority = %d, New priority = 0\n", otemp->iProcessId, otemp->iPriority);
				addFirst(otemp, &listOfHead[0], &listOfTail[0]);
				}
	
			}
		}
		sem_post(&sync);
	}	
}
