#include<stdio.h>

int convert(int);
 
int main()
{
	int n;
	
	printf("Please input an integer:");
	scanf("%d",&n);
	printf("The result is:%d",convert(n));
	
	return 0;
}

int convert(int n) //×ª»» 
{
	if(n==0 || n==1)
		return n;
	else
		return (n%10+convert(n/10)*2); 
} 
