#include "variable.h"
#include "control.h" 
#include "queue.h" 

//策略1：先来先服务的输入线程 
DWORD WINAPI Input_FCF()
{
	char ch;

	while(scanf("%c", &ch) != EOF)
	{
		if(ch != '\n')		//忽略回车的影响 
			//将键入的信息解释成相应的指令 
			switch(ch)
			{
				case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
					if(Inside_Button[ch-'0'] == 0)
					{
						Inside_Button[ch-'0'] = 1; EnQueue(pq, ch-'0');	
					}
					break;
				case 'q': case 'Q':
					if(Up_Button[1] == 0)
					{
						Up_Button[1] = 1; EnQueue(pq, 1);	
					}
					break;
				case 'w': case 'W':
					if(Up_Button[2] == 0)
					{
						Up_Button[2] = 1; EnQueue(pq, 2);	
					}
					break;
				case 'e': case 'E':
					if(Up_Button[3] == 0)
					{
						Up_Button[3] = 1; EnQueue(pq, 3);	
					}
					break;
				case 'r': case 'R':
					if(Up_Button[4] == 0)
					{
						Up_Button[4] = 1; EnQueue(pq, 4);	
					}
					break;
				case 't': case 'T':
					if(Up_Button[5] == 0)
					{
						Up_Button[5] = 1; EnQueue(pq, 5);	
					}
					break;
				case 'y': case 'Y':
					if(Up_Button[6] == 0)
					{
						Up_Button[6] = 1; EnQueue(pq, 6);	
					}
					break;
				case 'u': case 'U':
					if(Up_Button[7] == 0)
					{
						Up_Button[7] = 1; EnQueue(pq, 7);	
					}
					break;
				case 'i': case 'I':
					if(Up_Button[8] == 0)
					{
						Up_Button[8] = 1; EnQueue(pq, 8);	
					}
					break;
				
				case 'a': case 'A':
					if(Down_Button[2] == 0)
					{
						Down_Button[2] = 1; EnQueue(pq, 2);	
					}
					break;
				case 's': case 'S':
					if(Down_Button[3] == 0)
					{
						Down_Button[3] = 1; EnQueue(pq, 3);	
					}
					break;
				case 'd': case 'D':
					if(Down_Button[4] == 0)
					{
						Down_Button[4] = 1; EnQueue(pq, 4);	
					}
					break;
				case 'f': case 'F':
					if(Down_Button[5] == 0)
					{
						Down_Button[5] = 1; EnQueue(pq, 5);	
					}
					break;
				case 'g': case 'G':
					if(Down_Button[6] == 0)
					{
						Down_Button[6] = 1; EnQueue(pq, 6);	
					}
					break;
				case 'h': case 'H':
					if(Down_Button[7] == 0)
					{
						Down_Button[7] = 1; EnQueue(pq, 7);	
					}
					break;
				case 'j': case 'J':
					if(Down_Button[8] == 0)
					{
						Down_Button[8] = 1; EnQueue(pq, 8);	
					}
					break;
				case 'k': case 'K':
					if(Down_Button[9] == 0)
					{
						Down_Button[9] = 1; EnQueue(pq, 9);	
					}
					break;
					
				case '0':
					GO = 1; break; 
			}
	}
	exit(0);
	
} 

//策略2：顺便服务的输入线程 
DWORD WINAPI Input_IPS()
{
	char ch;
	
	while(scanf("%c", &ch) != EOF)
	{
		if(ch != '\n')
		{
			//将键入的信息解释成相应的指令 
			switch(ch)
			{
				case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
					Inside_Button[ch-'0'] = 1; break;
				case 'q': case 'Q':
					Up_Button[1] = 1; break;
				case 'w': case 'W':
					Up_Button[2] = 1; break;
				case 'e': case 'E':
					Up_Button[3] = 1; break;
				case 'r': case 'R':
					Up_Button[4] = 1; break;
				case 't': case 'T':
					Up_Button[5] = 1; break;
				case 'y': case 'Y':
					Up_Button[6] = 1; break;
				case 'u': case 'U':
					Up_Button[7] = 1; break;
				case 'i': case 'I':
					Up_Button[8] = 1; break;
				
				case 'a': case 'A':
					Down_Button[2] = 1; break;
				case 's': case 'S':
					Down_Button[3] = 1; break;
				case 'd': case 'D':
					Down_Button[4] = 1; break;
				case 'f': case 'F':
					Down_Button[5] = 1; break;
				case 'g': case 'G':
					Down_Button[6] = 1; break;
				case 'h': case 'H':
					Down_Button[7] = 1; break;
				case 'j': case 'J':
					Down_Button[8] = 1; break;
				case 'k': case 'K':
					Down_Button[9] = 1; break;
					
				case '0':
					GO = 1; break; 
			}
		}
	}
	exit(0);
}
