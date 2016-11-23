#include<stdio.h>

typedef struct
{
	int num;
	struct node* next;
}node;

int main()
{
	int n;
	node *head, *previous, *current; //分别为记录头指针、前一项的指针、现在项的指针 
	
	//读入数据 
	printf("Please input a series of integers:");
	scanf("%d" ,&n);
	head = previous = (node *)malloc(sizeof(node));
	head->num = n;
	while(scanf("%d", &n), n!=-1)
	{
		current = (node *)malloc(sizeof(node)); //动态内存分配 
		current->num = n;
		previous = previous->next = current; //记录这一节点以用于链接后面的节点 
	}
	current->next = NULL; //链表设置为NULL 
	
	//输出链表 
	current = head; //从头开始 
	printf("The list is:");
	while(current)
	{
		if(current->next != NULL)
			printf("%d ", current->num);
    	else
			printf("%d\n", current->num);
		current = current->next; //后移 
	}	
	
	//读入需要删除的数字 
	printf("Please input an integer you want to delete:");
	scanf("%d", &n);
	
	//遍历链表，删除满足条件的项 
	current = head;
	while(current)
	{
		if(current->num == n)
		{	
			node *temp; //建立临时节点，用于记录需要删除的节点 
			temp = current;
			if(current == head)
				head = current->next;
			else
				previous->next = current->next;
			current = current->next;
			free(temp); //释放节点 
		}
		else
		{
			previous = current;
			current = current->next;
		}
	}
	
	//遍历链表，输出新表 
	current = head;
	if(head == NULL)
		printf("There is no item in the list.");
	else 	
	{
		printf("The new list is:");
		while(current)
		{
			node *temp;
			if(current->next != NULL)
				printf("%d ", current->num);
			else
				printf("%d", current->num);
			temp = current; 
			current = current->next;
			free(temp);
		}	
	}
	
	return 0;	
} 
