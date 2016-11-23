#include <stdio.h>

void InsertSort(int a[],int n);

int main()
{
	int n,i;
	int a[1000];
	
	printf("Please input the number of integers:");
	scanf("%d",&n);
	printf("Please input the integers:");
	for(i=0;i<=n-1;i++)
		scanf("%d",&a[i]);	
	InsertSort(a,n);
	
	return 0;
}

void InsertSort(int a[],int n) //二分查找 
{
	int temp;
	int i,j,k;
	
	for(i=1;i<=n-1;i++)
	{
		for(j=0;j<=i-1;j++)
		{
			if(j==i)
				continue;
			else{
				if(a[i]>=a[j])
					continue;
				else if(a[i]<a[j]){
					temp=a[i];
					for(k=i-1;k>=j;k--)
						a[k+1]=a[k];
					a[j]=temp;
				}
			}	
		}
	}
	
	printf("The result is:");
	for(i=0;i<=n-1;i++) //输出 
	{
		printf("%d",a[i]);
		if(i!=n-1)
			printf(" ");
	}
}
