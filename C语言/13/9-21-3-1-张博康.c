#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	FILE *in, *out;
	char ch;
	int note_slash = 0, slash = 0; //���ڷ�б�ܵ�״̬
	int note_asterisk = 0, note = 0; //����ע�͵�״̬
	
	out = fopen("out.c", "w");
	if((in = fopen("in.c", "r")) != NULL)
	{
		while((ch = fgetc(in)) != EOF)
		{
			if(slash) //�Ѿ���'//'ע��״̬ 
			{
				if(ch == '\n')
				{
					slash = 0;
					fputc(ch, out);
				}
			}
			else if(note) //�Ѿ���'/**/'״̬ 
			{
				if(note_asterisk) //��һ���ַ�����'*' 
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
			else if(note_slash) //��һ���ַ�����'/' 
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
				if(ch == '/') //����'/'�ı���Ӧ״̬ 
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
