#include<stdio.h>

int main()
{
	int a[1000];
	int n,m;
	int mark=-1;
	int temp;
	
	printf("Please input the number of integers:");
	scanf("%d",&n);
	printf("Please input the integers:");
	for(int i=0;i<=n-1;i++) //读入数组 
	{
		scanf("%d",&a[i]);
	}
	printf("Please input the times of query:");
	scanf("%d",&m);
	printf("Please input the integers you want to query:");
	for(int i=1;i<=m;i++) //依次读入查询的元素 
	{
		scanf("%d",&temp);
		for(int j=0;j<=n-1;j++) //遍历数组查询 
			if(temp==a[j])
			{
				mark=j;
				break;
			}
		if(mark==-1)
			printf("NULL\n");
		else if(mark!=0 && mark==n-1)	
			printf("%d\n",a[mark-1]);
		else if(mark==0 && mark!=n-1)
			printf("%d\n",a[mark+1]);
		else	
			printf("%d %d\n",a[mark-1],a[mark+1]);
		mark=-1; 
	} 
	
	return 0;
}
