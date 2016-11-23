#include<stdio.h>

int countBinary(int);

int main()
{
	int n;
	
	printf("Input an integer:");
	scanf("%d",&n);
	printf("The binary form of number %d has %d digits.",n,countBinary(n));
}

int countBinary(int n) //计算二进制位数 
{
	int ans=1;
	
	if(n==0 || n==1)
		return 1;
	else
	{
		ans+=countBinary(n/2);
		return ans;
	}
}
