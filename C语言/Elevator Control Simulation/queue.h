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

Queue *InitQueue();									//创建一个新队列 
void DestroyQueue(Queue *pqueue);					//销毁队列 
void ClearQueue(Queue *pqueue);						//清空一个队列 
int IsEmpty(Queue *pqueue);							//判断队列是否为空 
int GetSize(Queue *pqueue);							//返回队列大小 
Item GetFront(Queue *pqueue);						//返回队首元素 
void EnQueue(Queue *pqueue, Item item);				//新元素入队 
Item DeQueue(Queue *pqueue);						//队首元素出队 

Queue *pq;


#endif
