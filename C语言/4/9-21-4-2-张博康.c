#include<stdio.h>

int main()
{
	int ar[51]={1,2}; //初始化数组 
	int i,n;
	double ans;
	
	printf("Please input an integer:");
	scanf("%d",&n);
	printf("The result is:");
	for(i=2;i<=n;i++)
	{
		ar[i]=ar[i-1]+ar[i-2]; //用数组计算并储存斐波那契数列 
	}
	for(i=1;i<=n;i++)
	{
		ans+=(double)ar[i]/(double)ar[i-1]; //计算各项的值，并累加起来 
	}
	printf("%.2lf",ans);
	
	return 0;
}
