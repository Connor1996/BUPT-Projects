#include<stdio.h>

int main()
{
	int ar[51]={1,2}; //��ʼ������ 
	int i,n;
	double ans;
	
	printf("Please input an integer:");
	scanf("%d",&n);
	printf("The result is:");
	for(i=2;i<=n;i++)
	{
		ar[i]=ar[i-1]+ar[i-2]; //��������㲢����쳲��������� 
	}
	for(i=1;i<=n;i++)
	{
		ans+=(double)ar[i]/(double)ar[i-1]; //��������ֵ�����ۼ����� 
	}
	printf("%.2lf",ans);
	
	return 0;
}
