#include<stdio.h>

int main()
{
	int n;
	int a[200];
	int temp;
	int ans=0;
	
	printf("Please input the number of integers:");
	scanf("%d",&n);
	printf("Please input the integers:");
	for(int i=0;i<=n-1;i++)
	{
		scanf("%d",&temp);
		if(temp%2!=0) //记录偶数 
			a[i]=temp;
		else
		{
			for(int j=i;j>=ans;j--)
			{
				a[j+1]=a[j]; //向后移位 
			}
			a[ans]=temp; //放入奇数 
			ans++;
		}
	}
	printf("The elements of the new array are:");
	for(int i=0;i<=n-1;i++)
		if(i!=n-1)
			printf("%d ",a[i]);
		else 
			printf("%d",a[i]);
			
	return 0;
} 
