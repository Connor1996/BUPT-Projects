#include "control.h" 
#include "queue.h"
#include "variable.h"

//����1�������ȷ���Ŀ����߳�
DWORD WINAPI Control_FCF()
{	
	DataInit();							//�������ݳ�ʼ�� 
	
	while(1)
	{
		while(IsEmpty(pq));				//�ȴ����в�Ϊ�յ�ʱ���ٶ�ȡ���� 
		
		Destination_Floor = DeQueue(pq);	//��ȡ��Ϣ���ͳ���Ӧ������ 
 
		State_Trans(); 					//����״̬ת���ж� 
		while(State == RUN)				//�ڵ����˶������в��Ͻ��� 
		{								//״̬ת���жϺ͵������п���
			Running_Control();  
			State_Trans();
		}
		Running_Control();		//����״̬�����Ե���STOP״̬�½������п��� 
		State_Trans();			//�ж�״̬�Ƿ��л�ΪFREE 
	}
 } 
 
DWORD WINAPI Control_IPS()
{
	char ch;
	
	DataInit();
	while(1)
	{			
		State_Trans();			//����״̬ת���ж� 
		while(State == RUN)		//�ڵ������й����в��Ͻ��� 
		{						//״̬ת���жϺ͵������п��� 
			Running_Control();
			State_Trans();
		}
		Running_Control();		//����״̬�����Ե���STOP״̬�½������п���
	}
 } 
 
//���ݳ�ʼ������ 
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

//״̬ת���жϺ��� 
void State_Trans()
{
	//����1�������ȷ����״̬ת���ж� 
	if(Strategy == 1) 
	{
		switch(State)
		{
			case STOP:
				Change_Signal = 1; 							//�ı��ź�״̬���������ģ��ȷ���Ƿ���״̬�ı� 
				if(Destination_Floor != Current_Floor)		//ֹͣ״̬�£����Ŀǰ¥���Ŀ��¥�㲻��ͬ 
				{											//��ת��Ϊ����״̬����ȷ������ 
					State = RUN;
					if(Destination_Floor < Current_Floor)
						Direction = DOWN;
					else
						Direction = UP;
				}
				else										//ֹͣ״̬�£����Ŀǰ¥���Ŀ��¥����ͬ 
				{											//��ת��Ϊ����״̬�������÷���Ϊδ֪ 
					Direction = NONE;
					State = FREE;
				}
				break;
			case RUN:										
				if(Destination_Floor == Current_Floor)		//����״̬�£����Ŀǰ¥���Ŀ��¥����ͬ 
				{											//��ת��Ϊֹͣ״̬����ȷ������ 
					Change_Signal = 1;
					State = STOP;
					if(Direction == UP)						//����Ӧ¥�㰴ť״̬����  
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
				if(Destination_Floor != Current_Floor)		//����״̬�£����Ŀǰ¥���Ŀ��¥�㲻��ͬ 
				{											//��ת��Ϊ����״̬����ȷ������ 
					State = RUN;
					if(Destination_Floor < Current_Floor)
						Direction = DOWN;
					else
						Direction = UP;
				}
				else										//����״̬�£����Ŀǰ¥���Ŀ��¥����ͬ 
				{											//��ת��Ϊֹͣ״̬��������Ӧ¥�㰴ť���� 
					State = STOP;
					Up_Button[Current_Floor] = 0;
					Down_Button[Current_Floor] = 0;
					Inside_Button[Current_Floor] = 0; 
				}					
		}
	}
	//����2��˳������״̬ת���ж�
	else if(Strategy == 2)
	{
		if(State == RUN && Destination_Floor == Current_Floor)	//����״̬�£����Ŀǰ¥���Ŀ��¥����ͬ 
		{														//��ת��Ϊֹͣ״̬��������Ӧ¥�㰴ť���� 
			if(Direction == UP)
				Up_Button[Current_Floor] = 0;
			else if(Direction == DOWN)
				Down_Button[Current_Floor] = 0;
			Inside_Button[Current_Floor] = 0; 
			Change_Signal = 1;									//��״̬�仯����ı��ź�״̬ 
			State = STOP;										
		}
		else if((State == FREE || State == STOP) && (Up_Button[Current_Floor] || Down_Button[Current_Floor] || Inside_Button[Current_Floor]))
		{														//�������ͣ�ڵ�ǰ¥�㣬����Ŀ��Ϊ��¥��İ�ť 
			Up_Button[Current_Floor] = 0;						//����ݲ����������״̬�����ٴν���ֹͣ״̬׼�������� 
			Down_Button[Current_Floor] = 0;
			Inside_Button[Current_Floor] = 0; 
			Change_Signal = 1;
			State = STOP;
		}
		else
		{														
			if(Direction == UP || Direction == NONE)			//�����������л����޷��� 
			{
				Up_Signal = 0;								//��¼�Ƿ������������״̬ 
				
				for(int i=Current_Floor+1; i<=MAXFLOOR; i++)	//����ȵ�ǰ��ߵ�¥�������Ϻ��л���Ŀ��
				{												//��ô����͵ĸ��ڵ�ǰ¥������Ϻ�������¥�����Ŀ��¥��Ϊ��ǰĿ��¥��
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
				if(!Up_Signal)									//���û�бȵ�ǰ��ߵ�¥�������Ϻ��л���Ŀ�� 
				{												
					Down_Signal = 0;						//��¼�Ƿ������������״̬ 

					for(int i=MAXFLOOR; i>=1; i--)				//����ߵ����º�������¥�����Ŀ��¥����Ϊ��ǰĿ��¥��
					{
						if(i == Current_Floor)					//���Ե�ǰ¥������ 
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
					if(!Down_Signal)							//���û������ߵ����º�������¥�����Ŀ��¥����Ϊ��ǰĿ��¥��
					{											
						int NoCommand_Signal = 1; 				//��¼�Ƿ��������״̬
						
						for(int i=1; i<=MAXFLOOR; i++)			//����͵����Ϻ�������¥��ΪĿ��¥��
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
						if(NoCommand_Signal)					//���û����������ݽ������״̬ 
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
			else if(Direction == DOWN)							//������������ 
			{
				Down_Signal = 0;							//��¼�Ƿ������������״̬ 
									
				for(int i=Current_Floor-1; i>=1; i--)			//����ȵ�ǰ��͵�¥�������º��л���Ŀ��
				{												//����ߵĵ��ڵ�ǰ¥������º�������¥�����Ŀ��¥����Ϊ��ǰĿ��¥��
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
				if(!Down_Signal)								//���û�бȵ�ǰ��͵�¥�������º��л���Ŀ��
				{
					Up_Signal = 0;							//��¼�Ƿ�����������״̬ 
					
					for(int i=1; i<=MAXFLOOR; i++)				//����͵����Ϻ�������¥�����Ŀ��¥����Ϊ���ݵ�ǰĿ��¥��
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
					if(!Up_Signal)								//���û������͵����Ϻ�������¥�����Ŀ��¥����Ϊ���ݵ�ǰĿ��¥��
					{
						int NoCommand_Signal = 1;				//��¼�Ƿ������� 
						 
						for(int i=MAXFLOOR; i>=1; i--)			//����ߵ����º�������¥��ΪĿ��¥��
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
						if(NoCommand_Signal)					//���û����������ݽ������״̬ 
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
		if(State == RUN && Destination_Floor == Current_Floor)	//����״̬�£����Ŀǰ¥���Ŀ��¥����ͬ 
		{														//��ת��Ϊֹͣ״̬��������Ӧ¥�㰴ť���� 
			if(Direction == UP)
				Up_Button[Current_Floor] = 0;
			else if(Direction == DOWN)
				Down_Button[Current_Floor] = 0;
			Inside_Button[Current_Floor] = 0; 
			Change_Signal = 1;									//��״̬�仯����ı��ź�״̬ 
			State = STOP;										
		}
		else if((State == FREE || State == STOP) && (Up_Button[Current_Floor] || Down_Button[Current_Floor] || Inside_Button[Current_Floor]))
		{														//�������ͣ�ڵ�ǰ¥�㣬����Ŀ��Ϊ��¥��İ�ť 
			Up_Button[Current_Floor] = 0;						//����ݲ����������״̬�����ٴν���ֹͣ״̬׼�������� 
			Down_Button[Current_Floor] = 0;
			Inside_Button[Current_Floor] = 0; 
			Change_Signal = 1;
			State = STOP;
		}
		else
		{	
			int NoCommand_Signal = 1;							//��¼�Ƿ������� 
			for(int i=1; i<=MAXFLOOR; i++)						//����״̬���飬����Ƿ������� 
			{
				if(Up_Button[i] == 1 || Down_Button[i] == 1 || Inside_Button[i] == 1)
				{
					NoCommand_Signal = 0;
					break;
				}						
			}
			if(NoCommand_Signal)								//���û����������ݽ������״̬
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
				if(Up_Signal)									//��������Ӧ��������״̬ 
				{
					for(int i=1; i<=MAXFLOOR; i++)				
					{											
						if(i == Current_Floor)					//���Ե�ǰ¥������ 
							continue;
						if(Up_Button[i] == 1 || Inside_Button[i] == 1)
						{										//��������Ϻ��л���Ŀ��
							Destination_Floor = i;
							Change_Signal = 1;
							State = RUN;
							if(Destination_Floor > Current_Floor)
								Direction = UP;
							else if(Destination_Floor < Current_Floor)
								Direction = DOWN;	
							break;
						}
						if(i == MAXFLOOR)						//�������Ӧ���������������Ӧ���������״̬ 
						{
							Up_Signal = 0;
							Down_Signal = 1;
						}
					}
				}
				if(Down_Signal)									//��������Ӧ��������״̬
				{
					for(int i=MAXFLOOR; i>=1; i--)				
					{
						if(i == Current_Floor)					//���Ե�ǰ¥������ 
							continue;							
						if(Down_Button[i] == 1 || Inside_Button[i] == 1)
						{										//��������º��л���Ŀ��		
							Change_Signal = 1;
							State = RUN;
							Destination_Floor = i;
							if(Destination_Floor > Current_Floor)
								Direction = UP;
							else if(Destination_Floor < Current_Floor)
								Direction = DOWN;
							break;
						}
						if(i == 1)								//�������Ӧ���������������Ӧ���������״̬ 
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

//�������п��ƺ���
//���ڲ�ͬ���Ե�����������ͬ�ģ���ʹ��ͬһ���� 
void Running_Control()
{
	switch(State)
	{
		case RUN:
			//��������״̬�������зֱ�����¥�㣬���ı��ź�״̬ 
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
			Sleep(INTERVAL_TIME);						//��������һ��¥��ҪINTERVAL_TIME 
			break;
		case STOP:
			//����ֹͣ״̬�£��ȿ��ź���ţ����ı��ź�״̬ 
			Door = OPEN;			
			Change_Signal = 1;
			GO = 0;	
			Sleep(OPEN_TIME);							//���ݿ�������ʱ��
			Start = clock();							//��¼����ͣ��֮ǰ��ʱ��			
			while((clock() - Start) < STOP_TIME)
			{
				if(GO == 1)								//�������ż�����ֹͣ������������ 
				{	
					GO = 0; 
					break;
				}
			}
			End = clock(); 								//��¼����ͣ��֮���ʱ�� 
		 	Door = CLOSED;
			Change_Signal = 1;
			Sleep(CLOSE_TIME);							//���ݹ�������ʱ�� 
			WaitForSingleObject(hTimeMutex, INFINITE);	//�ȴ����ģ�������� 
			ReleaseMutex(hTimeMutex);					 
	}
}
