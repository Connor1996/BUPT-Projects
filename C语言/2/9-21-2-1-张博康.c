#include<stdio.h>
#include<ctype.h>

int main()
{
	char ch;
	int alpha=0,space=0,digit=0,other=0;
	
	printf("Please input a string:");
	while ((ch=getchar())!='\n')
	{
		if(isalpha(ch)) //�ж��Ƿ�Ϊ��ĸ 
			alpha++;
		else
			if(isspace(ch)) //�ж��Ƿ�Ϊ�ո� 
				space++;
			else
				if(isdigit(ch)) //�ж��Ƿ�Ϊ���� 
					digit++;
				else 
					other++;		
	}
	printf("The number of English chararcters,spaces,numbers,other characters are:%d %d %d %d",alpha,space,digit,other);
	return 0;
}
