#include<stdio.h>

typedef struct
{
	int num;
	struct node* next;
}node;

void delete_list(node *head)
{
	node *current = head; //记录现在所在节点
	
	while(current)
	{
		node *temp;
		temp = current; 
		current = current->next; //节点后移 
		free(temp); 
	}
}

int main()
{
	int n;
	node *head_A, *head_B; //分别为链表A的头指针，链表B的头指针 
	node *previous, *current;
	
	printf("Please input List A(end by -1):");
	scanf("%d" ,&n);
	head_A = previous = (node *)malloc(sizeof(node));
	head_A->num = n;
	while(scanf("%d", &n), n!=-1)
	{
		current = (node *)malloc(sizeof(node)); //动态内存分配 
		current->num = n;
		previous = previous->next = current; //记录这一节点以用于链接后面的节点 
	}
	current->next = NULL; //链表设置为NULL
	
	printf("Please input List B(end by -1):");
	scanf("%d" ,&n);
	head_B = previous = (node *)malloc(sizeof(node));
	head_B->num = n;
	while(scanf("%d", &n), n!=-1)
	{
		current = (node *)malloc(sizeof(node)); //动态内存分配 
		current->num = n;
		previous = previous->next = current; //记录这一节点以用于链接后面的节点 
	}
	current->next = NULL; //链表设置为NULL
	//从头到位遍历链表A，查找符合链表B的位置 
	current = head_B;
	int state = 0, ok = 0; //记录状态 
	while(head_A)
	{
		node *temp;
		if(state == 1 && head_A->num!=current->num)
		{ 
			state = 0;
			current = head_B;
		}
		if(head_A->num == current->num)
		{
			state = 1;
			current = current->next;
			if(current == NULL)
			{
			 	ok = 1; 
				break;
			}
		}
		//边遍历链表A边释放节点 
		temp = head_A;  
		head_A = head_A->next;
		free(temp);
	}
	//释放链表所有节点 
	delete_list(head_A);
	delete_list(head_B);
	//分情况输出 
	if(ok == 1)
		printf("ListB is the sub sequence of ListA.");
	else
		printf("ListB is not the sub sequence of ListA.");
	
	return 0;
}
		  
