#include<stdio.h>
 
int GCD(int,int);
int LCM(int,int);
 
int main()
{
	int  a,b;
	
	printf("Please input two integers:");
	scanf("%d %d",&a,&b);
	printf("The greatest common divisor is %d and the lowest common multiple is %d",GCD(a,b),LCM(a,b));

	return 0;
}

int GCD(int a,int b) //�������Լ�� 
{
	int temp;
	
	while(a%b!=0)
	{
		temp=a%b;
		a=b;
		b=temp;
	}
	return b;
}

int LCM(int a,int b) //������С������ 
{
	return a*b/GCD(a,b); //��С������=�����˻�/���Լ�� 
}
