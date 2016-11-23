#include<stdio.h>

int main()
{
	char a[100]; //创建字符数组，把整数的每位数字看为字符 
	char ch;
	int i=0,j;
	int n;
	
	printf("Please input an integer:");
	while((ch=getchar())!='\n') //读入数据 
	{
		a[i]=ch;
		i++;
	}
	n=i%3; //计算第一个逗号前的位数 
	printf("The result is:"); 
	for(j=0;j<=n-1;j++)  
	{
		putchar(a[j]); //输出第一个逗号前的数字 
	}
	if(n!=0)
		printf(",");
	for(;j<=i-1;j++) //输出之后的所有数字 
	{
		putchar(a[j]);
		if((j+1-n)%3==0 && j!=i-1)
			printf(",");
	}
	
	return 0;
}
