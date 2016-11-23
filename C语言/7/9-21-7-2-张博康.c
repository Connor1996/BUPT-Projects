#include<stdio.h>

int main()
{
	int n;
	int a[100];
	int sum=0;
	
	printf("Please input the number of the courses:");
	scanf("%d",&n);
	printf("Please input %d scores:",n);
	for(int i=0;i<=n-1;i++) //读入数组并求和 
	{
		scanf("%d",&a[i]);
		sum+=a[i];
	} 
	printf("The average score is:%.2f",(float)sum/n);
	
	return 0;
}
