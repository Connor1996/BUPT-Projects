#include<stdio.h>

void sort(int a[][100],int n);

int main()
{
	int n;
	int a[100][100];
	int	record[1000];
	int num=1;
	int ans=0;
	int i,j;
	
	printf("Please input row of the matrix:");
	scanf("%d",&n);
	printf("Please input elements of the matrix:\n");
	for(i=0;i<=n-1;i++)
	{
		for(j=0;j<=n-1;j++) //读入矩阵元素 
		{
			scanf("%d",&a[i][j]);
		}
	}
	printf("The result is:\n");
	sort(a,n);
	
    system("pause");
	return 0;
} 

void sort(int a[][100],int n)
{
    int sum[100],temp[100];
	int i,j,k,min=0,pos=0;
	
	for(i=0;i<=n-1;i++)
    {
		sum[i]=0;
		for(j=0;j<=n-1;j++)
			sum[i]+=a[i][j];								//求各行和 
	}
	for(i=0;i<=n-1;i++)
    {
		min=sum[i];
		for(j=i+1;j<=n-1;j++)
        {
			if(min>sum[j])
            {
				min=sum[j];
				pos=j;
			}
		}
		for(k=0;k<=n-1;k++)
			temp[k]=a[pos][k];
		for(j=pos-1;j>=i;j--)
        {
			for(k=0;k<=n-1;k++)
            {
				a[j+1][k]=a[j][k];
			}
		}
		for(k=0;k<=n-1;k++)
			a[i][k]=temp[k];							  //各行和排序并记录顺序和位次 
	}
	for(i=0;i<=n-1;i++)
    {
		for(j=0;j<=n-1;j++)
        {
			printf("%d",a[i][j]);						  //按位置打印 
			if(j==n-1)
				putchar('\n');
			else
				putchar(' ');
        }
    }	
}
