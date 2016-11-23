#include<stdio.h>

int main()
{
	int n;
	
	printf("Please input an integer：");
	scanf("%d",&n);
	printf("The result is:\n");
	for(int i=1;i<=n;i++) //打印上半部分星号 
	{
		for(int j=1;j<=n-i;j++)
			printf(" ");
		for(int j=1;j<=2*i-1;j++)
			printf("*");
		printf("\n");
	}
	for(int i=n-1;i>=1;i--) //打印下半部分星号 
	{
		for(int j=1;j<=n-i;j++)
			printf(" ");
		for(int j=1;j<=2*i-1;j++)
			printf("*");
		printf("\n");
	} 
	
	return 0;
} 
