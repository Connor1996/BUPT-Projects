#include<stdio.h>

int main()
{
	char a[100]; //�����ַ����飬��������ÿλ���ֿ�Ϊ�ַ� 
	char ch;
	int i=0,j;
	int n;
	
	printf("Please input an integer:");
	while((ch=getchar())!='\n') //�������� 
	{
		a[i]=ch;
		i++;
	}
	n=i%3; //�����һ������ǰ��λ�� 
	printf("The result is:"); 
	for(j=0;j<=n-1;j++)  
	{
		putchar(a[j]); //�����һ������ǰ������ 
	}
	if(n!=0)
		printf(",");
	for(;j<=i-1;j++) //���֮����������� 
	{
		putchar(a[j]);
		if((j+1-n)%3==0 && j!=i-1)
			printf(",");
	}
	
	return 0;
}
