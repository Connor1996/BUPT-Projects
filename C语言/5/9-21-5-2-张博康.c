#include<stdio.h>

int mypow(int,int);

int main()
{
	int x,n;
	
	printf("Please input two integers:");
	scanf("%d %d",&x,&n);
	printf("The result is %d.",mypow(x,n));
	
	return 0;
} 

int mypow(int x,int n) //Ãİ´ÎÔËËã 
{
	int ans=x;
	
	for(int i=2;i<=n;i++)
	{
		ans*=x; 
	}
	
	return ans;
}
