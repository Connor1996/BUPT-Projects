#include<stdio.h>

void GetMatrix(int a[][100],int n);
 
int main()
{
	int a[100][100];
	int n;
	int i,j;
	
	printf("Please input order of the snake matrix:");
	scanf("%d",&n);
	GetMatrix(a,n);
	printf("The snake matrix is:\n");	
	for(i=0;i<=n-1;i++) //输出蛇形矩阵 
		for(j=0;j<=n-1;j++)
		{
			printf("%d",a[i][j]);
			if(j!=n-1)
				printf(" ");
			else 
				printf("\n");
		} 

	return 0;
}

void GetMatrix(int a[][100],int n)
{	
	int row,col;
	int ans=4;
	
	a[0][0]=1;
	a[1][0]=2;
	a[0][1]=3; 
	row=0;
	col=1;
	while(row!=n-1 && col!=n-1) //获得上半部分蛇形矩阵 
	{
		if(row==0)
		{
			a[0][++col]=ans++;
			while(col!=0)
			{
				row++;
				col--;
				a[row][col]=ans++;
			}
		}
		else if(col==0)
		{
			a[++row][0]=ans++;
			while(row!=0)
			{
				row--;
				col++;
				a[row][col]=ans++;
			} 
		}
	}
	while(row!=n-1 || col!=n-1) //获得下半部分蛇形矩阵 
	{
		if(col==n-1)
		{
			a[++row][n-1]=ans++;
			while(row!=n-1)
			{
				row++;
				col--;
				a[row][col]=ans++;
			}
		} 
		else if(row==n-1)
		{
			a[n-1][++col]=ans++;
			while(col!=n-1)
			{
				row--;
				col++;
				a[row][col]=ans++;
			}
		}
	}	
} 
