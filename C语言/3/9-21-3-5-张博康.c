#include<stdio.h>
#include<math.h>

int a,b,c,d;

int main()
{
	double x1=1,x2=0;
	double function,differential;
	
	printf("Please input four integers:");
	scanf("%d %d %d %d",&a,&b,&c,&d);
	function=a*x1*x1*x1+b*x1*x1+c*x1+d;
	differential=3*a*x1*x1+2*b*x1+c;
	x2=x1-function/differential; //����X2 
	while(fabs(x2-x1)>1e-5)
	{
		x1=x2; //��¼Xn���Է���֮���Xn+1��֮�Ƚ� 
		function=a*x1*x1*x1+b*x1*x1+c*x1+d;
		differential=3*a*x1*x1+2*b*x1+c;
		x2=x1-function/differential; //����Xn+1 
	}
	printf("The solution is:");
	printf("%lf",x2);
	
	return 0;
} 
