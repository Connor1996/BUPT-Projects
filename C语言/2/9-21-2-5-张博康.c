#include<stdio.h>
#include<math.h>
int main()
{
	double a,b,c,d;
	double f1,f2;
	
	printf("Please input three float numbers:");
	scanf("%lf %lf %lf",&a,&b,&c);
	if(a==0)
		printf("The equation is not quadratic");
	else
	{
		
		d=b*b-a*c*4; //根据公式计算Δ 
		if(d==0)
			printf("The equation has two equal roots:%.4lf",-b/(2*a));
		else
			if(d>0)
			{
				f1=(-b+sqrt(d))/(2*a); //求根 
				f2=(-b-sqrt(d))/(2*a);
				if(fabs(f1-f2)<=1e-6)
					printf("The equation has two equal roots:%.4lf",f1);
				else
					printf("The equation has two distinct real roots:%.4lf and %.4lf",f1,f2);
			}
			else //求虚数 
			{
				d*=-1;
				double i=sqrt(d)/(2*a);
				double f=-b/(2*a);
				printf("The equation has two distinct complex roots:%.4lf+%.4lfi and %.4lf-%.4lfi",f,i,f,i);	
			}	
	}
	return 0;
}
