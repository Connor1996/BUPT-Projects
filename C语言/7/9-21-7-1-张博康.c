#include<stdio.h>

int isWaveNum(int);

int odd,even; //��¼����ż��λ 
int ans=0; //��¼λ�� 

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

int isWaveNum(int n) //�жϲ����� 
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
