#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"


void addFirst(void * oTemp, struct element ** pHead, struct element ** pTail)
{
	if(*pHead == NULL)	//check the linked list whether contains element or not 
	{
		struct element* newPtr = malloc(sizeof(struct element)); //create a memory space for a new element
		
		if(newPtr != NULL)			//check whether create a new element successfully or not
		{
			newPtr->pData = oTemp;	        //assign the input into newPtr
			newPtr->pNext = NULL;	
			*pHead = newPtr;		//pHead and pTail point to the element
			*pTail = newPtr;
		}
		else	
		{
			perror("no memory available");  //print error message
			exit(0);
		}
	}
	else
	{
		struct element* newPtr = malloc(sizeof(struct element));
		
		if(newPtr != NULL)
		{
			newPtr->pData = oTemp;		//assign the input into newPtr
			newPtr->pNext = *pHead;		//put the new element before the head element
			*pHead = newPtr;		//let the new element as the new head
		}
		else
		{
			perror("no memory available");	//print if there is no more memory available
			exit(0);
		}
	}

}


void addLast(void * oTemp, struct element ** pHead, struct element ** pTail)
{
	if(*pHead == NULL)
	{
		struct element* newPtr = malloc(sizeof(struct element));
		
		if(newPtr != NULL)
		{
			newPtr->pData = oTemp;	
			newPtr->pNext = NULL;
			*pHead = newPtr;		
			*pTail = newPtr;		
		}
		else
		{
			perror("no memory available");	//print error message
			exit(0);
		}
	}
	else
	{
		struct element* newPtr = malloc(sizeof(struct element));
		
		if(newPtr != NULL)
		{
			newPtr->pData = oTemp;	
			newPtr->pNext = NULL;
			(*pTail)->pNext = newPtr;		// put the new element behind the last element 
			*pTail = newPtr;			// let the new element as the last element
		}
		else
		{
			perror("no memory available");
			exit(0);
		}	
	}
 	
}


void * removeFirst(struct element ** pHead, struct element ** pTail)
{
	if(*pHead == NULL)
	{	
		printf("It's an empty list.");		//print if it's an empty list
		return NULL;
	}
	else{
			struct element* temp = *pHead;  	//assign the origin head element to temporary element
			int* data = temp->pData;        	//assign the temporary element into a data pointer
			*pHead = (*pHead)->pNext;	        //let the next element as the new head element
			return data;				//return the data which is removed from the list
			free(temp);				//release the memory block 
	}	
}
