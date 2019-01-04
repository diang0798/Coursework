#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

void fifo();
void lifo();
void element_print(struct element* head);
//struct element* head = NULL;
//struct element* tail = NULL;

int main(int argc, char *argv[])
{
//	struct element* head = NULL;
//	struct element* tail = NULL;

	fifo();
	lifo();
	//free()
}

void fifo()
{
	struct element* head = NULL;
	struct element* tail = NULL;
	
	int process[100];
	int i;
	for(i = 0; i < 100; i++)
	{
		process[i] = i;
	} 
	printf("FIFO:\n");
	for(i = 0; i < 100; i++)
	{
		addLast(&process[i], &head, &tail);
	}
	for(i = 0; i < 100; i++)
	{
		int* remove_one = removeFirst(&head, &tail);
		printf("Element%d = %d\n", i+1, *remove_one);
	}
	element_print(head);
	
}

void lifo()
{
	struct element* head = NULL;
	struct element* tail = NULL;

	int process[100];
	int i;
	for(i = 0; i < 100; i++)
	{
		process[i] = i;
	} 
	printf("LIFO:\n");
	for(i = 0; i < 100; i++)
	{
		addFirst(&process[i], &head, &tail);
	}
		for(i = 0; i < 100; i++)
	{
		int* remove_one = removeFirst(&head, &tail);
		printf("Element%d = %d\n", i+1, *remove_one);
	}

	element_print(head);
}


void element_print(struct element* head)
{
	struct element* temp = head;
	int i = 1;
   	while(temp != NULL)
   	{
		int* data = temp->pData;
		printf("Element %d = %d\n", i, *data);
		temp = temp->pNext;
		i++;
		printf("hello??\n");
      	}
}
