#include<stdio.h>
#include<ctype.h>

int main()
{
	char ch;
	int alpha=0,space=0,digit=0,other=0;
	
	printf("Please input a string:");
	while ((ch=getchar())!='\n')
	{
		if(isalpha(ch)) //判断是否为字母 
			alpha++;
		else
			if(isspace(ch)) //判断是否为空格 
				space++;
			else
				if(isdigit(ch)) //判断是否为数字 
					digit++;
				else 
					other++;		
	}
	printf("The number of English chararcters,spaces,numbers,other characters are:%d %d %d %d",alpha,space,digit,other);
	return 0;
}
