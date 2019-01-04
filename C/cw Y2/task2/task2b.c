#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "coursework.h"
#include "linkedlist.h"


void process_list(struct element*  listOfHead[],struct element*  listOfTail[]);
void pq(struct element* listOfHead[],struct element*  listOfTail[]);


int main()
{
	int i, j;
	int flag;
	struct element* listOfHead [MAX_PRIORITY];
	struct element* listOfTail [MAX_PRIORITY];
	int list[NUMBER_OF_PROCESSES];
	for(i = 0; i < MAX_PRIORITY; i++)	//initialize arrays
	{
		listOfHead[i] = NULL;
		listOfTail[i] = NULL;
	}
	for(i = 0; i < NUMBER_OF_PROCESSES; i++)
	{
		struct process* x = generateProcess();
		int cur_priority = x->iPriority;
		flag = 0;
		for(j = 0; j < i; j++)		//check if there is a linkedlist for current priority
		{
			if(cur_priority == list[j])
			{
				addLast(x, &listOfHead[cur_priority], &listOfTail[cur_priority]);
				flag = 1;
				list[i] = -1;
				break;
			}
		}
		if(flag == 0)		//if current priority do not have a linkedlist
		{
			struct element* head = NULL;
			struct element* tail = NULL;
			addLast(x, &head, &tail);		//bulid a new linkedlist
			listOfHead[cur_priority] = head;
			listOfTail[cur_priority] = tail;
			list[i] = cur_priority;			//record this priority has built a linkedlist
		}
						
	}
	process_list(listOfHead,listOfTail);		//print process list
	pq(listOfHead,listOfTail);			
}


void process_list(struct element* listOfHead[],struct element*  listOfTail[])
{
	int i;
	int pre_priority = -1;
	printf("PROCESS LIST:\n");
	for(i = 0; i < MAX_PRIORITY; i++)
	{
		struct element* temp = listOfHead[i];
		while(temp != NULL)
		{
			struct process* otemp = temp->pData;
			if((otemp->iPriority) != pre_priority)
			{
				printf("priority %d:\n",otemp->iPriority);
			}
			printf("\tProcess Id = %d, Priority = %d, Initial Burst Time = %d, \
Remaining Burst Time = %d\n", otemp->iProcessId, otemp->iPriority, otemp->iInitialBurstTime, \
otemp->iRemainingBurstTime);
			temp = temp->pNext;
			pre_priority = otemp->iPriority;
		}
	}
	printf("END\n");
}


void pq(struct element* listOfHead[],struct element*  listOfTail[])
{
	struct timeval startTime, currentTime;
	int cur_rTime = 0;
	int cur_trTime = 0;
	double sum_rTime, sum_trTime;
	int i, j, k;
	int n = 0;
	struct process* list[NUMBER_OF_PROCESSES];
	printf("\n");
	
	for(i = 0; i < MAX_PRIORITY; i++)
	{
		if(listOfHead[i] != NULL)		
		{
			struct element* temp = listOfHead[i];
			if((temp->pNext) == NULL)		//if current priority just has one process
			{
				struct process* otemp = removeFirst(&listOfHead[i], &listOfTail[i]);
				runPreemptiveJob(otemp, &startTime, &currentTime);
				printf("Process Id = %d, Priority = %d, Previous Burst Time = %d, \
Remaining Burst Time = %d, Response Time = %d\n", otemp->iProcessId, otemp->iPriority, otemp->iPreviousBurstTime, \
otemp->iRemainingBurstTime, cur_rTime);
				if(temp != NULL)
				{
					sum_rTime += cur_rTime;
					cur_rTime += otemp->iPreviousBurstTime;
				}
				cur_trTime += otemp->iPreviousBurstTime;
				sum_trTime += cur_trTime;
				while((otemp->iRemainingBurstTime) != 0)
				{
					runPreemptiveJob(otemp, &startTime, &currentTime);
					if((otemp->iRemainingBurstTime) == 0)
					{
						break;
					}
					printf("Process Id = %d, Priority = %d, Previous Burst Time = %d, \
Remaining Burst Time = %d\n", otemp->iProcessId, otemp->iPriority, otemp->iPreviousBurstTime, \
otemp->iRemainingBurstTime);
				}
				printf("Process Id = %d, Priority = %d, Previous Burst Time = %d, \
Remaining Burst Time = %d, Turnaround Time = %d\n", otemp->iProcessId, otemp->iPriority, otemp->iPreviousBurstTime, \
otemp->iRemainingBurstTime, cur_trTime);
				free(otemp);
			}
			else		//if current priority has multiple processes
			{
				while(temp != NULL)		//get the number of process
				{
					list[n] = removeFirst(&listOfHead[i], &listOfTail[i]);
					n++;
					temp = temp->pNext;
				}
				for(j = 0; j < n; j++)
				{
					struct process* otemp = list[j];
					runPreemptiveJob(otemp, &startTime, &currentTime);
					printf("Process Id = %d, Priority = %d, Previous Burst Time = %d, \
Remaining Burst Time = %d, Response Time = %d\n", otemp->iProcessId, otemp->iPriority, otemp->iPreviousBurstTime, \
otemp->iRemainingBurstTime, cur_rTime);
					sum_rTime += cur_rTime;	
					cur_rTime += 5;
					cur_trTime += 5;
				}
				while(n != 0)		//round robin
				{
					for(j = 0; j < n; j++)
					{
						struct process* otemp = list[j];
						runPreemptiveJob(otemp, &startTime, &currentTime);
						if((otemp->iRemainingBurstTime) == 0)
						{
							cur_rTime += otemp->iPreviousBurstTime;
							cur_trTime += otemp->iPreviousBurstTime;
							sum_trTime += cur_trTime;
							printf("Process Id = %d, Priority = %d, Previous Burst Time = %d, \
Remaining Burst Time = %d, Turnaround Time = %d\n", otemp->iProcessId, otemp->iPriority, otemp->iPreviousBurstTime, \
otemp->iRemainingBurstTime, cur_trTime);
							free(otemp);
							for(k=j; k < n - 1; k++)
							{
								list[k] = list[k+1];
							}
							n -= 1;
							j -= 1;
							if(n == 0)
							{
								break;
							}
							continue;
						}
						printf("Process Id = %d, Priority = %d, Previous Burst Time = %d, \
Remaining Burst Time = %d\n", otemp->iProcessId, otemp->iPriority, otemp->iPreviousBurstTime, \
otemp->iRemainingBurstTime);
						cur_rTime += 5;
						cur_trTime += 5;
					}
				}
			}	
		}
	}
	printf("Average response time = %lf\n", sum_rTime/NUMBER_OF_PROCESSES);
	printf("Average turn around time = %lf\n", sum_trTime/NUMBER_OF_PROCESSES);
}
