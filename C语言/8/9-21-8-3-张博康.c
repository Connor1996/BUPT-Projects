#include<stdio.h>

int maxLen(int a[],int);

int main()
{
	int a[1000];
	int n;
	
	printf("Please input the number of integers:");
	scanf("%d",&n);
	printf("Please input the integers:");
	for(int i=0;i<=n-1;i++)
	{
		scanf("%d",&a[i]);
	}
	printf("The longest level is:%d",maxLen(a,n));
	
	return 0;
} 

int maxLen(int a[],int n)
{
	int len=0,max=0; //��¼ƽ̨��󳤶� 
	int num=-1;
	
	for(int i=0;i<=n-1;i++)
	{
		if(a[i]==num)  
			len++;
		else
		{
			if(len>max)
				max=len; 
			num=a[i]; //�ı�ȶ���ֵ 
			len=1; //���¼�¼��ƽ̨���� 
		}
	}
	
	return max;
}
