#ifndef Control_H
#define Control_H

#define STOP 0					//����ͣ��
#define RUN 1					//�������� 
#define FREE 2					//���� 

#define	UP 0					//��������
#define DOWN 1					//��������
#define NONE 2					//δ֪����

#define CLOSED 0				//�Źر� 
#define OPEN 1 					//�Ŵ� 

void DataInit();				//�������ݳ�ʼ�� 
void State_Trans();				//ȷ������״̬
void Running_Control();			//�������п��� 

int Up_Button[10];				//�ⲿ���а�ť 
int Down_Button[10];			//�ⲿ���а�ť 
int Inside_Button[10];			//�ڲ�¥�㰴ť 

int State;						//��������״̬ (STOP��RUN��FREE�� 
int GO; 						//���ݿ��Ű��� 
int Door;						//�ŵ�״̬ 
int Direction;					//�������з���
int Current_Floor; 				//Ŀǰ¥��
int Destination_Floor;			//Ŀ��¥�� 

int Up_Signal;					//�����Ƿ����������� 
int Down_Signal;				//�����Ƿ����������� 
		 
#endif
