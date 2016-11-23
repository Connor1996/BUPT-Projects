#include<stdio.h>

typedef struct
{
	int num;
	struct node* next;
}node;

void delete_list(node *head)
{
	node *current = head; //��¼�������ڽڵ�
	
	while(current)
	{
		node *temp;
		temp = current; 
		current = current->next; //�ڵ���� 
		free(temp); 
	}
}

int main()
{
	int n;
	node *head_A, *head_B; //�ֱ�Ϊ����A��ͷָ�룬����B��ͷָ�� 
	node *previous, *current;
	
	printf("Please input List A(end by -1):");
	scanf("%d" ,&n);
	head_A = previous = (node *)malloc(sizeof(node));
	head_A->num = n;
	while(scanf("%d", &n), n!=-1)
	{
		current = (node *)malloc(sizeof(node)); //��̬�ڴ���� 
		current->num = n;
		previous = previous->next = current; //��¼��һ�ڵ����������Ӻ���Ľڵ� 
	}
	current->next = NULL; //��������ΪNULL
	
	printf("Please input List B(end by -1):");
	scanf("%d" ,&n);
	head_B = previous = (node *)malloc(sizeof(node));
	head_B->num = n;
	while(scanf("%d", &n), n!=-1)
	{
		current = (node *)malloc(sizeof(node)); //��̬�ڴ���� 
		current->num = n;
		previous = previous->next = current; //��¼��һ�ڵ����������Ӻ���Ľڵ� 
	}
	current->next = NULL; //��������ΪNULL
	//��ͷ��λ��������A�����ҷ�������B��λ�� 
	current = head_B;
	int state = 0, ok = 0; //��¼״̬ 
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
		//�߱�������A���ͷŽڵ� 
		temp = head_A;  
		head_A = head_A->next;
		free(temp);
	}
	//�ͷ��������нڵ� 
	delete_list(head_A);
	delete_list(head_B);
	//�������� 
	if(ok == 1)
		printf("ListB is the sub sequence of ListA.");
	else
		printf("ListB is not the sub sequence of ListA.");
	
	return 0;
}
		  
