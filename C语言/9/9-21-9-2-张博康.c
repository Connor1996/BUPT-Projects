#include<stdio.h>

int RecurBinarySearch(int a[],int,int,int);

int main()
{
	int num[100000];
	int result[100000]; 
	int n,m;
	int temp;
	int i,j;
	
	printf("Please input the number is integers:");
	scanf("%d",&n);
	printf("Please intput the number you want to search:");
	scanf("%d",&m);
	printf("Please input the integers:");
	for(i=0;i<=n-1;i++) //读入所有数字 
	{
		scanf("%d",&num[i]);
	}
	printf("Please input the integers you want to search:");
	for(i=0;i<=m-1;i++) //读入需要查找的数字，并将结果储存在result 
	{
		scanf("%d",&temp);
		result[i]=RecurBinarySearch(num,0,n-1,temp); 
	}
	printf("The elements'subscript in the array are:");
	for(i=0;i<=m-1;i++)
	{
		printf("%d",result[i]);
		if(i!=m-1)
			printf(" "); 
	}
	
	return 0;
	
}

int RecurBinarySearch(int a[],int left,int right,int temp) //二分查找 
{
	int mid;
	
	if(left<=right)
	{
		mid=(left+right)/2;
		if(a[mid]==temp)
			return mid;
		if(a[mid]<temp)
			return RecurBinarySearch(a,mid+1,right,temp);
		if(a[mid]>temp)
			return RecurBinarySearch(a,left,mid-1,temp);
	}
	else 
		return -1;
}
