#include<stdio.h>

int main()
{
	int n,m,i;
	int ans=0;
	
	printf("Please input two integers:");
	scanf("%d %d",&n,&m);
	printf("The result is:\n");
	for(i=1;i<=n;i++)
	{
		int p=i;
		int sum=0;
		while(p!=0) //取得n的每位数，并算出各位数平方的总和 
		{
			sum+=(p%10)*(p%10);
			p/=10;
		}
		if(sum==i/m)
		{
			ans++;
			if(ans%5==0)
				printf("%d\n",i);
			else
				printf("%d\t",i);
		}
	}
	return 0;
}
