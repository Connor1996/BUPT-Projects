#include<stdio.h>

int main()
{
	int i,n;
	int sum=0;
	
	printf("Please input an integer:");
	scanf("%d",&n);
	for(i=1;i<=n;i++)  
	{
		if(i%3==0 && i%7==0) //判断能否同时被3和7整除 
			sum+=i; 
	}
	sum=sum*sum;
	printf("The result is:%d",sum);
	return 0;
}
