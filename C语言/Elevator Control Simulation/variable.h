#ifndef Variable_H 
#define Variable_H

#include <windows.h>
#include <stdio.h>
#include <time.h>

DWORD WINAPI Control_FCF();		//先来先服务策略控制线程 
DWORD WINAPI Control_IPS(); 	//顺便服务策略控制线程 
DWORD WINAPI Input_FCF();		//先来先服务策略输入线程 
DWORD WINAPI Input_IPS(); 		//顺便服务策略输入线程 
DWORD WINAPI Output();			//输出线程 

int MAXFLOOR;					//最大楼层数
int OPEN_TIME; 					//电梯开门时间 
int CLOSE_TIME;					//电梯关门时间 
int INTERVAL_TIME;				//电梯运行一层楼的时间
int STOP_TIME;					//电梯在一层楼的停靠时间 

int Strategy;					//策略 
int Change_Signal;				//状态改变信号

clock_t Start, End;				//记录开始和运行时间 
HANDLE hTimeMutex; 				//时间互斥对象 
  

#endif
