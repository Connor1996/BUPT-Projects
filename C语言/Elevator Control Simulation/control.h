#ifndef Control_H
#define Control_H

#define STOP 0					//电梯停靠
#define RUN 1					//电梯运行 
#define FREE 2					//空闲 

#define	UP 0					//向上运行
#define DOWN 1					//向下运行
#define NONE 2					//未知方向

#define CLOSED 0				//门关闭 
#define OPEN 1 					//门打开 

void DataInit();				//电梯数据初始化 
void State_Trans();				//确定电梯状态
void Running_Control();			//电梯运行控制 

int Up_Button[10];				//外部上行按钮 
int Down_Button[10];			//外部下行按钮 
int Inside_Button[10];			//内部楼层按钮 

int State;						//电梯运行状态 (STOP、RUN、FREE） 
int GO; 						//电梯开门按键 
int Door;						//门的状态 
int Direction;					//电梯运行方向
int Current_Floor; 				//目前楼层
int Destination_Floor;			//目标楼层 

int Up_Signal;					//电梯是否有上行请求 
int Down_Signal;				//电梯是否有下行请求 
		 
#endif
