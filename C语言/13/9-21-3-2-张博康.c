#include<stdio.h>
#include<ctype.h>

int main()
{
	char ch;
	int int_1 = 0, int_2 = 0;  
	int state = 1; //�Ƿ���Ϲ淶 
	int type = 1, name = 0;
	int head = 1; 
	
	printf("Please input a string:");
	while((ch = getchar()) != '\n') 
	{
		
			if(type) //�ж�int�Ƿ����� 
			{
				if(int_1)
				{
					if(ch == 'n')
					{
						int_1 = 0;
						int_2 = 1;
					}
					else
					{
						state = 0;
						break;
					}
				}
				else if(int_2)
				{	
					if(ch == 't')
					{
						type = 0;
						name = 1;
					}
					else
					{
						state = 0;
						break;
					}
				}
				else
				{
					if(ch == 'i')
						int_1 = 1;
				}
			}
			else if(name)
			{
				if(head && !isblank(ch)) //�ж��Ƿ�Ϊ��������һ����ĸ 
				{
					if(!isalpha(ch) && ch != '_')
					{
						state = 0;
						break;
					}
					else
						head = 0;
				}
				else 
				{	
					if(ch == ';')
						break;
					else if(!isalnum(ch) && !isblank(ch) && ch != '_') 
					{
						state = 0;
						break;
					}
				
				}
			}
		
	}
	printf("The result is:");
	if(state)
		printf("YES");
	else
		printf("NO");
		
	return 0;
 }  
