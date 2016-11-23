#include<stdio.h>

int main()
{
	int a[999]={0};
	int p=2;
	int ans=2;
	int count=0;
		
	while(p*p<=999)
	{
		if(a[p]==0)
		{
			while(ans*p<=999)
			{
				a[ans*p]=1; //所有的整数倍标记为非素数 
				ans++;
			}
			ans=2;
		}
		p++;
	}
	printf("The prime numbers between 1 and 999 are:\n"); 
	for(int i=2;i<=998;i++)
	{
		if(a[i]==0)
		{
			count++;
			if(count%5)
				printf("%d\t",i);
			else 
				printf("%d\n",i);
		}	
	}
	
	return 0;
} 
