#include<stdio.h>
#include<math.h>

int main()
{
	double n,f,sum=1;
	double ans=1,up=1;
	int i=1;
	
	printf("Please input an float number:");
	scanf("%lf",&n);
	do //µü´ú·¨ 
	{
		up*=n;
		ans*=i++;
		f=up/ans;
		sum+=f;
	} while(fabs(f)>=1e-8);  
	printf("The result is:%.4lf",sum);
	
	return 0;
} 
