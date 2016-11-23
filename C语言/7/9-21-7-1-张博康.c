#include<stdio.h>

int isWaveNum(int);

int odd,even; //记录奇数偶数位 
int ans=0; //记录位数 

int main()
{
	int n;
	
	scanf("%d",&n);
	odd=n%10;
	even=(n%100)/10;
	if(n<100 && odd!=even)
		printf("YES");
	if(odd!=even && isWaveNum(n))
		printf("YES");
	else
		printf("NO");
	
	return 0;
}

int isWaveNum(int n) //判断波浪数 
{
	ans++;
	if(n>=1)
	{
		if(ans%2!=0)
		{
			if(n%10==odd)
				return isWaveNum(n/10);
			else 
				return 0;		
		}
		else
		{
			if(n%10==even)
				return isWaveNum(n/10);
			else 
				return 0;
		}
	}
	else 
		return 1;	
}
