#include<stdio.h>

int isWaveNum(int n);

int main()
{
	int n;
	
	scanf("%d",&n);
	if(isWaveNum(n)==-1)
		printf("NO");
	else
		printf("YES");
	
	return 0;
}

int isWaveNum(int n)
{
	int odd,even;
	
	if(n/100==0)
	{
		return n%10;
	}
	else
	{
		odd=n%10;
		n/=10;
		even=n%10;
		n/=10;
		if(n!=0)
		{
			if(odd==isWaveNum(n) && (even==isWaveNum(n/10) || n/10==0) &&  odd!=even)
				return n%10;
			else 
				return -1;
		} 
	}
}
