/*********************************************************************************************
                                       版本更新日志 
																		by: 张博康，王天晓 
Version 0.1 (due. 2015.5.8):
	实现先来先服务策略

Version 0.2 (due. 2015.5.9):
	增加命令行初始化界面
	增加策略选择：先来先服务，顺便服务（尚未实现）
	
Version 0.2.1 (due. 2015.5.10):
	增加策略选择中的判误功能

Version 0.3 (due. 2015.5.11): 
	实现电梯运行状态自动隔秒输出
 
Version 0.3.1 (due. 2015.5.12): 
	修复了电梯下行到0层的bug 

Version 0.4 (due. 2015.5.13): 
	将运行状态隔秒输出改为状态改变时输出 
	 
Version 0.5 (due. 2015.5.13):
	实现了顺便服务策略
	更新了variable.h中的全局变量 

Version 0.6 (due. 2015.5.14):
	增加电梯门开关状态的输出 
	修复了电梯按钮状态未更新会导致电梯结束服务后回到呼叫楼层的bug 
	修复了当前楼层发出呼叫时电梯不进行开关门操作的bug 
	
Version 0.7 (due. 2015.5.15):	
	对代码进行了详细的注释
	
Version 0.8 (due. 2015.5.20): 
	添加开门按钮GO状态，可以进行及时的关门
	添加时间互斥对象以解决开门状态持续时间短而忽略输出的bug
	
Version 0.8.3 (due. 2015.5.20):
	增加自定义配置对开关门时间的调整
	增加自定义配置对最高楼层数的调整（但不能超过9层） 
	增加了最快响应策略的选择（尚未实现） 

Version 0.9 (due. 2015.5.21):
	实现了最快响应策略
	
Version 1.0beta (due. 2015.5.22):
	增加输出的信息种类 
	添加状态输出到文件的功能
	增加了输入EOF自动结束程序的功能
	增加了开头界面对命令输入的说明 
	代码首次突破1000行 
	
Version 1.1 (due. 2015.5.29)
	增加策略实时切换的功能（代码未更新，在图形界面版本中实现） 
 
*********************************************************************************************/
#include "variable.h"
#include "queue.h"
#include "string.h"
 
int main() 
{
	//线程定义
	HANDLE hThread_Input, hThread_Control, hThread_Output; 										 
	hTimeMutex = CreateMutex(NULL, FALSE, "TIME");
	//输入信息界面 
	printf("********************************************************************************");
	printf("*                         Elevator Control System                              *");
	printf("*              Please choose one strategy to control the elevator:             *");
	printf("*                    1.先来先服务   2.顺便服务   3.最快响应                    *");
	printf("*                                                                              *"); 
	printf("*              命令输入说明：                                                  *");
	printf("*              *******************************************************         *");
	printf("*              *       键盘输入       |           对应指令           *         *");
	printf("*              *-----------------------------------------------------*         *");
	printf("*              *Q、W、E、R、T、Y、U、I|外部1、2、3、4、5、6、7、8上行*         *");
	printf("*              *-----------------------------------------------------*         *");
	printf("*              *A、S、D、F、G、H、J、K|外部2、3、4、5、6、7、8、9下行*         *"); 
	printf("*              *-----------------------------------------------------*         *");
	printf("*              *1、2、3、4、5、6、7、8|内部1、2、3、4、5、6、7、8、9 *         *");
	printf("*              *         、9          |            层请求            *         *"); 
	printf("*              *******************************************************         *");
	printf("*                                                                              *");
	printf("********************************************************************************");
	printf("Please input the number of the strategy:\n");
	//策略选择中的判误，只能输入1、2或3 
	char TF[1000];
	while(scanf("%s", &TF), strcmp(TF, "1") && strcmp(TF, "2") && strcmp(TF, "3"))
		printf("Sorry, please input valid data.\n"); 
	if(!strcmp(TF, "1"))
		Strategy = 1;
	else if(!strcmp(TF, "2"))
		Strategy = 2;
	else if(!strcmp(TF, "3"))
		Strategy = 3;
	printf("Do you want change the config? If not, program will use default config.\n"
			"Please input Yes(1) or No(0).\n");
	while(scanf("%s", &TF), strcmp(TF, "Yes") && strcmp(TF, "1") && strcmp(TF, "No") && strcmp(TF, "0"))
		printf("Sorry, please input valid command.\n");
	if(!strcmp(TF, "Yes") || !strcmp(TF, "1"))
	{
		printf("MAX FLOOR (2~9) = ");
		scanf("%d", &MAXFLOOR);
		printf("INTERVAL TIME (ms) = ");
		scanf("%d", &INTERVAL_TIME);
		printf("STOP TIME (ms) = ");
		scanf("%d", &STOP_TIME);
		printf("OPEN TIME (ms) = " );
		scanf("%d", &OPEN_TIME);
		printf("CLOSE TIME (ms) = ");
		scanf("%d", &CLOSE_TIME);
		
		printf("Config is saved. Enjoy yourself!%c\n\n", 3);
	}
	else
	{
		MAXFLOOR = 9;
		INTERVAL_TIME = 2000;
		STOP_TIME = 1000;
		OPEN_TIME = 500;
		CLOSE_TIME = 500;
	}
	printf("--------------------------------------------------------------------------------");
	printf("Please input the orders.\n");
	
	//策略1：先来先服务的线程创建 
	if(Strategy == 1)
	{
		pq = InitQueue();
		hThread_Input = CreateThread(NULL, 0, Input_FCF, NULL, 0, NULL);
		hThread_Control = CreateThread(NULL, 0, Control_FCF, NULL, 0, NULL);
		hThread_Output = CreateThread(NULL, 0, Output, NULL, 0, NULL); 
	}
	//策略2、3：顺便服务/最快响应服务的线程创建 
	else if(Strategy == 2 || Strategy == 3)
	{
		hThread_Input = CreateThread(NULL, 0, Input_IPS, NULL, 0, NULL);
		hThread_Control = CreateThread(NULL, 0, Control_IPS, NULL, 0, NULL);
		hThread_Output = CreateThread(NULL, 0, Output, NULL, 0, NULL); 
	}
	
	CloseHandle(hThread_Input);
	CloseHandle(hThread_Control);
	CloseHandle(hThread_Output);
	
	//主函数暂停 
	Sleep(400000);
		
	return 0;
}
