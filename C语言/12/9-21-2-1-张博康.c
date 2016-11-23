#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	FILE *in, *out;
	char ch_next, ch;
	int state1 = 0; //关于反斜杠的状态
	int state2 = 0; //关于注释的状态
	
	out = fopen("out.c", "w");
	if((in=fopen("in.c", "r")) != NULL)
	{
		ch = fgetc(in);
		while((ch_next = fgetc(in)) != EOF)
		{
			if(ch=='/')
			{ 
				if(ch_next=='/' && !state1)
					state1 = 1;
				else if(ch_next=='*' && !state2)
					state2 = 1;
			}
			else if(ch=='\n' && state1) //反斜杠注释结束标志 
			{
				fputc(ch, out);
				state1 = 0;
			}
			else if(ch=='*' && state2) 
			{
				if(ch_next == '/')  ///* */注释结束标志 
					state2 = 0;
			}
			else if(!state1 && !state2)
				fputc(ch, out);
			ch = ch_next;
		}
		fputc(ch, out);
	}
	fclose(in);
	fclose(out);
		
	return 0;
 }  
