#include<stdio.h>

int main()
{
	char a[10000];
	char *point[1000];
	char *pt;
	char ch;
	int ans=0,mark=0,i;
	
	printf("Please input a string:");
	gets(a);
	pt=a; //��¼ͷָ�� 
	point[ans++]=a; 
	while(*pt!='\0')
	{
		if(mark==1)
		{
			mark=0;
			point[ans++]=pt;
		} 
		if(*pt==' ') //�ո񴦱���ַ�����β 
		{
			mark=1;
			*pt='\0';
		}
		pt++;	
	} 
	printf("The result is:\n");
	for(i=0;i<=ans-1;i++) //�������ַ��� 
	{
		puts(point[i]); 
	}
	return 0;
} 
