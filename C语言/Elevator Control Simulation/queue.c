#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

Queue *InitQueue()
{
	Queue *pqueue = (Queue *)malloc(sizeof(Queue));
	if(pqueue!=NULL)
	{
		pqueue->front = NULL;
		pqueue->rear = NULL;
		pqueue->size = 0;
	}
	return pqueue;
}

void DestroyQueue(Queue *pqueue)
{
	if(IsEmpty(pqueue) != 1)
		ClearQueue(pqueue);
	free(pqueue);
}

void ClearQueue(Queue *pqueue)
{	
	while(IsEmpty(pqueue) != 1)
		DeQueue(pqueue);
}

int IsEmpty(Queue *pqueue)
{
	if(pqueue->front==NULL && pqueue->rear==NULL && pqueue->size==0)
		return 1;
	else
		return 0;
}

int GetSize(Queue *pqueue)
{
	return pqueue->size;
}

Item GetFront(Queue *pqueue)
{
	if(IsEmpty(pqueue)!=1)
		return pqueue->rear->data;
}

void EnQueue(Queue *pqueue, Item item)
{
	PNode pnode = (PNode)malloc(sizeof(Node));
	
	if(pnode != NULL)
	{
		pnode->data = item;
		pnode->next = NULL;
		if(IsEmpty(pqueue))
			pqueue->front = pnode;
		else
			pqueue->rear->next = pnode;
		pqueue->rear = pnode;
		pqueue->size++;
	}
}

Item DeQueue(Queue *pqueue)
{	
	PNode pnode = pqueue->front;
	Item ch = pnode->data;
	
	if(IsEmpty(pqueue)!=1 && pnode!=NULL)
	{
		pqueue->size--;
		pqueue->front = pnode->next;
		free(pnode);
		if(pqueue->size == 0)
			pqueue->rear = NULL;
		
		return ch;
	}
}
