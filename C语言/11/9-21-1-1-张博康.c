#include<stdio.h>

typedef struct
{
	int num;
	struct node* next;
}node;

int main()
{
	int n;
	node *head, *previous, *current; //�ֱ�Ϊ��¼ͷָ�롢ǰһ���ָ�롢�������ָ�� 
	
	//�������� 
	printf("Please input a series of integers:");
	scanf("%d" ,&n);
	head = previous = (node *)malloc(sizeof(node));
	head->num = n;
	while(scanf("%d", &n), n!=-1)
	{
		current = (node *)malloc(sizeof(node)); //��̬�ڴ���� 
		current->num = n;
		previous = previous->next = current; //��¼��һ�ڵ����������Ӻ���Ľڵ� 
	}
	current->next = NULL; //��������ΪNULL 
	
	//������� 
	current = head; //��ͷ��ʼ 
	printf("The list is:");
	while(current)
	{
		if(current->next != NULL)
			printf("%d ", current->num);
    	else
			printf("%d\n", current->num);
		current = current->next; //���� 
	}	
	
	//������Ҫɾ�������� 
	printf("Please input an integer you want to delete:");
	scanf("%d", &n);
	
	//��������ɾ�������������� 
	current = head;
	while(current)
	{
		if(current->num == n)
		{	
			node *temp; //������ʱ�ڵ㣬���ڼ�¼��Ҫɾ���Ľڵ� 
			temp = current;
			if(current == head)
				head = current->next;
			else
				previous->next = current->next;
			current = current->next;
			free(temp); //�ͷŽڵ� 
		}
		else
		{
			previous = current;
			current = current->next;
		}
	}
	
	//������������±� 
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
