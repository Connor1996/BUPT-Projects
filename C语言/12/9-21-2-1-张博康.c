#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	FILE *in, *out;
	char ch_next, ch;
	int state1 = 0; //���ڷ�б�ܵ�״̬
	int state2 = 0; //����ע�͵�״̬
	
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
			else if(ch=='\n' && state1) //��б��ע�ͽ�����־ 
			{
				fputc(ch, out);
				state1 = 0;
			}
			else if(ch=='*' && state2) 
			{
				if(ch_next == '/')  ///* */ע�ͽ�����־ 
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
