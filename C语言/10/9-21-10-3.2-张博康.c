#include<stdio.h>

int **Create2(int n,int m);

int main()
{
	int n,m,i,j;
	int **pt;
	
	printf("Please input n and m:");
	scanf("%d %d",&n,&m);
	printf("Please input %d integers:\n",n*m);
	pt=Create2(n,m);
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
		{
			scanf("%d",pt[i]+j);
		}
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			printf("%d",-*(pt[i]+j)*10); //�����Ӧ��ֵ 
			if(j!=m-1)
				printf(" "); 
		}
		printf("\n");
	}
	for(i=0;i<=n-1;i++)
		free(pt[i]);
	free(pt);
	
	return 0;
} 

int **Create2(int n,int m)
{	
	int **point;
	int i;
	
	point=(int **)malloc(n*sizeof(int *)); //���������ڴ� 
	for(i=0;i<n;i++)
		point[i]=(int *)malloc(m*sizeof(int)); //����ÿ��Ԫ�����ٷ����ڴ� 
		 
	return point;
}
