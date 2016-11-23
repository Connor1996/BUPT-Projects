#include<stdio.h>

int *Create1(int);

int main()
{
	int n,i;
	int *head;
	
	printf("Please input n:");
	scanf("%d",&n);
	printf("Please input %d integers:\n",n);
	head=Create1(n);
	for(i=0;i<=n-1;i++) //读入
	{  
		scanf("%d",head+i);
	}
	for(i=0;i<=n-1;i++)
	{
		printf("%d",-*(head+i)*10); //输出 
		if(i!=n-1)
			putchar(' '); 
	} 	
	free(head);
	
	return 0;
} 

int *Create1(int n)
{	
	return (int *)malloc(n*sizeof(int)); //分配内存 
}
