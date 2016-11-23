#include<stdio.h>
#include<math.h>

int judgeTriangle(int,int,int);

int main()
{
	int a,b,c;
	
	printf("Please input three integers:");
	scanf("%d %d %d",&a,&b,&c);
	switch(judgeTriangle(a,b,c))
	{
		case -1:
			printf("It is not a triangle.");
			break;
		case 0:
			printf("It is a scalenous triangle.");
			break;
		case 1:
			printf("It is a right-angled triangle.");
			break;
		case 2:
			printf("It is an isosceles triangle.");
			break;
		case 3:
			printf("It is a equilateral triangle.");
			break;
	}	
	
	return 0;
} 

int judgeTriangle(int a,int b,int c) //ÅÐ¶ÏÈý½ÇÀàÐÍ 
{
	if(c>=a+b || c<=fabs(a-b))
		return -1;
	else if(a==b && b==c)
		return 3;
	else if((a==b && c!=a)||(a==c && b!=a)||(b==c && a!=b))
		return 2;
	else if(a*a+b*b==c*c || a*a+c*c==b*b || b*b+c*c==a*a)
		return 1;
	else
		return 0;
}
