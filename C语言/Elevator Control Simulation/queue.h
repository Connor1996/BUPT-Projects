#ifndef Queue_H
#define Queue_H

typedef int Item;
typedef struct node* PNode;
typedef struct node{
	Item data;
	PNode next;
}Node;

typedef struct{
	PNode front;
	PNode rear;
	int size;
}Queue;

Queue *InitQueue();									//����һ���¶��� 
void DestroyQueue(Queue *pqueue);					//���ٶ��� 
void ClearQueue(Queue *pqueue);						//���һ������ 
int IsEmpty(Queue *pqueue);							//�ж϶����Ƿ�Ϊ�� 
int GetSize(Queue *pqueue);							//���ض��д�С 
Item GetFront(Queue *pqueue);						//���ض���Ԫ�� 
void EnQueue(Queue *pqueue, Item item);				//��Ԫ����� 
Item DeQueue(Queue *pqueue);						//����Ԫ�س��� 

Queue *pq;


#endif
