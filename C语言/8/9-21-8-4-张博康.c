#include<stdio.h>
#include<string.h>

void delcharfun(char str[],char ch);

int main()
{
	char st[100];
	char ch;
	
	printf("Please input the string:");
	gets(st);
	printf("Please input the letter you want to delete:");
	scanf("%c",&ch);
	delcharfun(st,ch);
	printf("The result is:");
	puts(st);
	
	return 0;	
} 

void delcharfun(char str[],char ch)
{
	int len;
	
	len=strlen(str); //���ַ������� 
	for(int i=0;i<=len-1;i++)
	{
		if(str[i]==ch)
		{
			for(int j=i;j<=len-1;j++)
			{ 
				str[j]=str[j+1]; //��ǰ��λ 
			}
			len--;
			i--;
		}
	}
}
