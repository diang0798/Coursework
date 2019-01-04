#include <stdio.h>
#include <stdlib.h>
#include "coursework.h"
#include "linkedlist.h"

void fcfs(struct element* head, struct element* tail);


int main()
{
	struct element* head = NULL;		
	struct element* tail = NULL;
	int n;
	for(n = 0; n < NUMBER_OF_PROCESSES; n++)
	{		
		struct process* x = generateProcess();
		addLast(x, &head, &tail);
	}
	
	fcfs(head, tail);
}

void fcfs(struct element* head, struct element* tail)
{
	struct timeval startTime, currentTime;
	int cur_rTime = 0;
	int cur_trTime = 0;
	double sum_rTime, sum_trTime;
	
	while(head != NULL)
	{
		struct process* otemp = removeFirst(&head, &tail);

		runNonPreemptiveJob(otemp, &startTime, &currentTime);
		cur_trTime += otemp->iPreviousBurstTime;
		sum_trTime += cur_trTime;
		printf("Process Id = %d, Previous Burst Time = %d, New Burst Time = %d, Response Time = %d, \
Turn Around Time = %d\n", otemp->iProcessId,otemp->iPreviousBurstTime, otemp->iRemainingBurstTime,cur_rTime, cur_trTime);
		if(head != NULL)
		{
			cur_rTime += otemp->iPreviousBurstTime;
			sum_rTime += cur_rTime;
		}
		free(otemp);
	}
	printf("Average response time = %lf\n", sum_rTime/NUMBER_OF_PROCESSES);
	printf("Average turn around time = %lf\n", sum_trTime/NUMBER_OF_PROCESSES);
}
