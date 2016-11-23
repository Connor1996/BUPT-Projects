#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	FILE *in, *out;
	char ch;
	int note_slash = 0, slash = 0; //关于反斜杠的状态
	int note_asterisk = 0, note = 0; //关于注释的状态
	
	out = fopen("out.c", "w");
	if((in = fopen("in.c", "r")) != NULL)
	{
		while((ch = fgetc(in)) != EOF)
		{
			if(slash) //已经是'//'注释状态 
			{
				if(ch == '\n')
				{
					slash = 0;
					fputc(ch, out);
				}
			}
			else if(note) //已经是'/**/'状态 
			{
				if(note_asterisk) //上一个字符读到'*' 
				{ 
					if(ch == '/')
					{ 
						note = 0;
						note_asterisk = 0;
					}
				}
				else if(ch == '*')
					note_asterisk = 1;
			}
			else if(note_slash) //上一个字符读到'/' 
			{
				if(ch == '*')
				{
					note = 1;
					note_slash = 0;
				}
				else if(ch == '/')
				{
					slash = 1;
					note_slash = 0;
				}
				else
					fputc(ch, out);
			}
			else 
			{
				if(ch == '/') //读到'/'改变相应状态 
					note_slash = 1;
				else
					fputc(ch, out);
			}
		}
	}
	fclose(in);
	fclose(out);
		
	return 0;
 }  
