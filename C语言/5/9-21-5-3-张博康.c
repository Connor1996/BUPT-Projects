#include<stdio.h>

int isPrime(int);
void printFactor(int);

int main()
{
	int i,j;
	int a,b;
	int ans;
		
	printf("Please input two integers:");
	scanf("%d %d",&a,&b);
	printf("The result is:\n");
	for(i=a;i<=b;i++)
	{
		if(isPrime(i))
			printf("%d=%d\n",i,i);
		else
		{
			printFactor(i); 
		}
	}
	
	return 0;	
      }

int isPrime(int n) //判断素数 
{
	int mark=0;
	int j=2;
	
	while(j*j<=n)
	{
		if(n%j==0)
		{
			mark=1;
			break;
		}
		j++;
	}
	if(mark)
		return 0;
	else 
		return 1;
} 

void printFactor(int n) //打印因数 
{
	int l=2;
	
	printf("%d=",n);
	while(n>1)
	{
		if(n%l==0)
		{
			n/=l;
			if(n==1)
				printf("%d\n",l);
			else
				printf("%d*",l);
			l=2; 
		}
		else
			l++;	
	}
}
