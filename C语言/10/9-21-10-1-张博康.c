#include<stdio.h>

char *locatesubstr(char *str1,char *str2);

int main()
{
	char st1[500],st2[500];
	char *p;
	
	printf("Please input one string:");
	gets(st1);
	printf("Please input another string:");
	gets(st2);
	printf("The result is:%s",locatesubstr(st1,st2));
	    
 	return 0;
}

char *locatesubstr(char *str1,char *str2) 
{
	char *point=NULL;
	char *record=str2; //记录查找字符串的首地址 
	int mark=0;
	
	while(*str1!='\0')
	{
		if(*str1==*str2)
		{
			mark=1;
			point=str1; //记录被查找字符串的地址 
			while(*str2!='\0')
			{
				if(*str1!=*str2) //当不相同时，改变指针的指向重新继续查找 
				{
					mark=0;
					point=NULL;
					str2=record;
					break;
				}
				str1++; 
				str2++;
			} 
			if(mark)
				break;
		}
		else
			str1++;
	}
	if(mark)
		return point;
	else
		return "NULL!";
	
}
