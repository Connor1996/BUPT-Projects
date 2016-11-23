#include "control.h" 
#include "queue.h"
#include "variable.h"

//策略1：先来先服务的控制线程
DWORD WINAPI Control_FCF()
{	
	DataInit();							//所有数据初始化 
	
	while(1)
	{
		while(IsEmpty(pq));				//等待队列不为空的时候再读取命令 
		
		Destination_Floor = DeQueue(pq);	//读取信息解释成相应的命令 
 
		State_Trans(); 					//电梯状态转移判断 
		while(State == RUN)				//在电梯运动过程中不断进行 
		{								//状态转移判断和电梯运行控制
			Running_Control();  
			State_Trans();
		}
		Running_Control();		//运行状态结束对电梯STOP状态下进行运行控制 
		State_Trans();			//判断状态是否切换为FREE 
	}
 } 
 
DWORD WINAPI Control_IPS()
{
	char ch;
	
	DataInit();
	while(1)
	{			
		State_Trans();			//电梯状态转移判断 
		while(State == RUN)		//在电梯运行过程中不断进行 
		{						//状态转移判断和电梯运行控制 
			Running_Control();
			State_Trans();
		}
		Running_Control();		//运行状态结束对电梯STOP状态下进行运行控制
	}
 } 
 
//数据初始化函数 
void DataInit()
{	
	State = FREE;
	Direction = NONE; 
	Current_Floor = 1; 
	Destination_Floor = 1;
	Change_Signal = 0;
	Up_Signal = 1;
	Down_Signal = 0; 
	for(int i=1; i<=MAXFLOOR; i++)
	{
		Up_Button[i] = 0;
		Down_Button[i] = 0;
		Inside_Button[i] = 0;
	}
}

//状态转移判断函数 
void State_Trans()
{
	//策略1：先来先服务的状态转移判断 
	if(Strategy == 1) 
	{
		switch(State)
		{
			case STOP:
				Change_Signal = 1; 							//改变信号状态，用于输出模块确定是否有状态改变 
				if(Destination_Floor != Current_Floor)		//停止状态下，如果目前楼层和目标楼层不相同 
				{											//则转变为运行状态，并确定方向 
					State = RUN;
					if(Destination_Floor < Current_Floor)
						Direction = DOWN;
					else
						Direction = UP;
				}
				else										//停止状态下，如果目前楼层和目标楼层相同 
				{											//则转变为空闲状态，并设置方向为未知 
					Direction = NONE;
					State = FREE;
				}
				break;
			case RUN:										
				if(Destination_Floor == Current_Floor)		//运行状态下，如果目前楼层和目标楼层相同 
				{											//则转变为停止状态，并确定方向 
					Change_Signal = 1;
					State = STOP;
					if(Direction == UP)						//将相应楼层按钮状态清零  
						if(Up_Button[Current_Floor])
							Up_Button[Current_Floor] = 0;
						else
							Down_Button[Current_Floor] = 0;
					else if(Direction == DOWN)
						if(Down_Button[Current_Floor])
							Down_Button[Current_Floor] = 0;
						else
							Up_Button[Current_Floor] = 0;
					Inside_Button[Current_Floor] = 0; 
				}
				break;
			case FREE:
				Change_Signal = 1;
				if(Destination_Floor != Current_Floor)		//空闲状态下，如果目前楼层和目标楼层不相同 
				{											//则转变为运行状态，并确定方向 
					State = RUN;
					if(Destination_Floor < Current_Floor)
						Direction = DOWN;
					else
						Direction = UP;
				}
				else										//空闲状态下，如果目前楼层和目标楼层相同 
				{											//则转变为停止状态，并将相应楼层按钮清零 
					State = STOP;
					Up_Button[Current_Floor] = 0;
					Down_Button[Current_Floor] = 0;
					Inside_Button[Current_Floor] = 0; 
				}					
		}
	}
	//策略2：顺便服务的状态转移判断
	else if(Strategy == 2)
	{
		if(State == RUN && Destination_Floor == Current_Floor)	//运行状态下，如果目前楼层和目标楼层相同 
		{														//则转变为停止状态，并将相应楼层按钮清零 
			if(Direction == UP)
				Up_Button[Current_Floor] = 0;
			else if(Direction == DOWN)
				Down_Button[Current_Floor] = 0;
			Inside_Button[Current_Floor] = 0; 
			Change_Signal = 1;									//有状态变化，则改变信号状态 
			State = STOP;										
		}
		else if((State == FREE || State == STOP) && (Up_Button[Current_Floor] || Down_Button[Current_Floor] || Inside_Button[Current_Floor]))
		{														//如果电梯停在当前楼层，按了目标为本楼层的按钮 
			Up_Button[Current_Floor] = 0;						//则电梯不会进入运行状态而是再次进入停止状态准备开关门 
			Down_Button[Current_Floor] = 0;
			Inside_Button[Current_Floor] = 0; 
			Change_Signal = 1;
			State = STOP;
		}
		else
		{														
			if(Direction == UP || Direction == NONE)			//电梯向下运行或者无方向 
			{
				Up_Signal = 0;								//记录是否有上行请求的状态 
				
				for(int i=Current_Floor+1; i<=MAXFLOOR; i++)	//如果比当前层高的楼层有向上呼叫或者目标
				{												//那么以最低的高于当前楼层的向上呼叫所在楼层或者目标楼层为当前目标楼层
					if(Up_Button[i] == 1 || Inside_Button[i] == 1)
					{
						if(State == STOP || State == FREE)
						{
							Change_Signal = 1;
							State = RUN;
							Direction = UP; 
						}
						Destination_Floor = i;
						Up_Signal = 1;
						break;
					}
				}
				if(!Up_Signal)									//如果没有比当前层高的楼层有向上呼叫或者目标 
				{												
					Down_Signal = 0;						//记录是否有下行请求的状态 

					for(int i=MAXFLOOR; i>=1; i--)				//以最高的向下呼叫所在楼层或者目标楼层作为当前目标楼层
					{
						if(i == Current_Floor)					//忽略当前楼层请求 
							continue;							
						if(Down_Button[i] == 1 || Inside_Button[i] == 1)
						{										
							if(State == STOP || State == FREE)
							{
								Change_Signal = 1;
								State = RUN;
							}
							Destination_Floor = i;
							if(Destination_Floor > Current_Floor)
								Direction = UP;
							else if(Destination_Floor < Current_Floor)
								Direction = DOWN;
							Down_Signal = 1;
							break;
						}
					}
					if(!Down_Signal)							//如果没有以最高的向下呼叫所在楼层或者目标楼层作为当前目标楼层
					{											
						int NoCommand_Signal = 1; 				//记录是否有请求的状态
						
						for(int i=1; i<=MAXFLOOR; i++)			//以最低的向上呼叫所在楼层为目标楼层
						{
							if(Up_Button[i] == 1 || Inside_Button[i] == 1)
							{
								if(i == Current_Floor)
									continue;
								if(State == STOP || State == FREE)
								{
									Change_Signal = 1;
									State = RUN;
								}
								Destination_Floor = i;			 
								if(Destination_Floor > Current_Floor)
									Direction = UP;
								else if(Destination_Floor < Current_Floor)
									Direction = DOWN;
								NoCommand_Signal = 0;
								break;
							}
						}
						if(NoCommand_Signal)					//如果没有请求，则电梯进入空闲状态 
						{										
							if(State == STOP || State == RUN)
							{
								State = FREE;
								Direction = NONE;
								Change_Signal = 1;
							}
						}
					}
				}
			}	
			else if(Direction == DOWN)							//电梯向下运行 
			{
				Down_Signal = 0;							//记录是否有下行请求的状态 
									
				for(int i=Current_Floor-1; i>=1; i--)			//如果比当前层低的楼层有向下呼叫或者目标
				{												//以最高的低于当前楼层的向下呼叫所在楼层或者目标楼层作为当前目标楼层
					if(Down_Button[i] == 1 || Inside_Button[i] == 1)
					{										
						if(State == STOP || State == FREE)
						{
							Change_Signal = 1;
							State = RUN;
						}
						Destination_Floor = i;
						Direction = DOWN;
						Down_Signal = 1;
						break;
					}
				}
				if(!Down_Signal)								//如果没有比当前层低的楼层有向下呼叫或者目标
				{
					Up_Signal = 0;							//记录是否有上行请求状态 
					
					for(int i=1; i<=MAXFLOOR; i++)				//以最低的向上呼叫所在楼层或者目标楼层作为电梯当前目标楼层
					{		
						if(i == Current_Floor)
							continue;
						if(Down_Button[i] == 1 || Inside_Button[i] == 1)
						{
							if(State == STOP || State == FREE)
							{	
								Change_Signal = 1;
								State = RUN;
							}
							Destination_Floor = i;
							if(Destination_Floor > Current_Floor)
								Direction = UP;
							else if(Destination_Floor < Current_Floor)
								Direction = DOWN;
							Up_Signal = 1;
							break;
						}
					}
					if(!Up_Signal)								//如果没有以最低的向上呼叫所在楼层或者目标楼层作为电梯当前目标楼层
					{
						int NoCommand_Signal = 1;				//记录是否有请求 
						 
						for(int i=MAXFLOOR; i>=1; i--)			//以最高的向下呼叫所在楼层为目标楼层
						{
							if(i == Current_Floor)
								continue;
							if(Up_Button[i] == 1 || Inside_Button[i] == 1)
							{
								if(State == STOP || State == FREE)
								{
									Change_Signal = 1;
									State = RUN;
								}
								Destination_Floor = i;
								if(Destination_Floor > Current_Floor)
									Direction = UP;
								else if(Destination_Floor < Current_Floor)
									Direction = DOWN;
								NoCommand_Signal = 0;
							break;
							}
						}
						if(NoCommand_Signal)					//如果没有请求，则电梯进入空闲状态 
						{
							if(State == RUN || State == STOP)
							{
								State = FREE;
								Direction = NONE;
								Change_Signal = 1;
							}
						}
					}
				}
			}
		}
	}
	else if(Strategy == 3)
	{
		if(State == RUN && Destination_Floor == Current_Floor)	//运行状态下，如果目前楼层和目标楼层相同 
		{														//则转变为停止状态，并将相应楼层按钮清零 
			if(Direction == UP)
				Up_Button[Current_Floor] = 0;
			else if(Direction == DOWN)
				Down_Button[Current_Floor] = 0;
			Inside_Button[Current_Floor] = 0; 
			Change_Signal = 1;									//有状态变化，则改变信号状态 
			State = STOP;										
		}
		else if((State == FREE || State == STOP) && (Up_Button[Current_Floor] || Down_Button[Current_Floor] || Inside_Button[Current_Floor]))
		{														//如果电梯停在当前楼层，按了目标为本楼层的按钮 
			Up_Button[Current_Floor] = 0;						//则电梯不会进入运行状态而是再次进入停止状态准备开关门 
			Down_Button[Current_Floor] = 0;
			Inside_Button[Current_Floor] = 0; 
			Change_Signal = 1;
			State = STOP;
		}
		else
		{	
			int NoCommand_Signal = 1;							//记录是否有请求 
			for(int i=1; i<=MAXFLOOR; i++)						//遍历状态数组，检测是否有请求 
			{
				if(Up_Button[i] == 1 || Down_Button[i] == 1 || Inside_Button[i] == 1)
				{
					NoCommand_Signal = 0;
					break;
				}						
			}
			if(NoCommand_Signal)								//如果没有请求，则电梯进入空闲状态
			{
				if(State == RUN || State == STOP)
				{
					State = FREE;
					Direction = NONE;
					Change_Signal = 1;
				}
			}													
			else
			{
				if(Up_Signal)									//电梯在响应上行请求状态 
				{
					for(int i=1; i<=MAXFLOOR; i++)				
					{											
						if(i == Current_Floor)					//忽略当前楼层请求 
							continue;
						if(Up_Button[i] == 1 || Inside_Button[i] == 1)
						{										//如果有向上呼叫或者目标
							Destination_Floor = i;
							Change_Signal = 1;
							State = RUN;
							if(Destination_Floor > Current_Floor)
								Direction = UP;
							else if(Destination_Floor < Current_Floor)
								Direction = DOWN;	
							break;
						}
						if(i == MAXFLOOR)						//若完成响应上行请求，则进入响应下行请求的状态 
						{
							Up_Signal = 0;
							Down_Signal = 1;
						}
					}
				}
				if(Down_Signal)									//电梯在响应下行请求状态
				{
					for(int i=MAXFLOOR; i>=1; i--)				
					{
						if(i == Current_Floor)					//忽略当前楼层请求 
							continue;							
						if(Down_Button[i] == 1 || Inside_Button[i] == 1)
						{										//如果有向下呼叫或者目标		
							Change_Signal = 1;
							State = RUN;
							Destination_Floor = i;
							if(Destination_Floor > Current_Floor)
								Direction = UP;
							else if(Destination_Floor < Current_Floor)
								Direction = DOWN;
							break;
						}
						if(i == 1)								//若完成响应下行请求，则进入响应上行请求的状态 
						{
							Down_Signal = 0;
							Up_Signal = 1;
						} 
					}
				}
			}
		}
	} 
}

//电梯运行控制函数
//对于不同策略电梯运行是相同的，故使用同一函数 
void Running_Control()
{
	switch(State)
	{
		case RUN:
			//电梯运行状态，上下行分别增减楼层，并改变信号状态 
			if(Direction == UP)
			{
				Change_Signal = 1;
				Current_Floor++;
			}
			else if(Direction == DOWN)
			{
				Change_Signal = 1;
				Current_Floor--;
			}
			Sleep(INTERVAL_TIME);						//电梯运行一层楼需要INTERVAL_TIME 
			break;
		case STOP:
			//电梯停止状态下，先开门后关门，并改变信号状态 
			Door = OPEN;			
			Change_Signal = 1;
			GO = 0;	
			Sleep(OPEN_TIME);							//电梯开门所需时间
			Start = clock();							//记录电梯停靠之前的时间			
			while((clock() - Start) < STOP_TIME)
			{
				if(GO == 1)								//若按关门键，终止停靠，立即关门 
				{	
					GO = 0; 
					break;
				}
			}
			End = clock(); 								//记录电梯停靠之后的时间 
		 	Door = CLOSED;
			Change_Signal = 1;
			Sleep(CLOSE_TIME);							//电梯关门所需时间 
			WaitForSingleObject(hTimeMutex, INFINITE);	//等待输出模块完成输出 
			ReleaseMutex(hTimeMutex);					 
	}
}
