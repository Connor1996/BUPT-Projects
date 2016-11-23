#ifndef Variable_H 
#define Variable_H

#include <windows.h>
#include <stdio.h>
#include <time.h>

DWORD WINAPI Control_FCF();		//�����ȷ�����Կ����߳� 
DWORD WINAPI Control_IPS(); 	//˳�������Կ����߳� 
DWORD WINAPI Input_FCF();		//�����ȷ�����������߳� 
DWORD WINAPI Input_IPS(); 		//˳�������������߳� 
DWORD WINAPI Output();			//����߳� 

int MAXFLOOR;					//���¥����
int OPEN_TIME; 					//���ݿ���ʱ�� 
int CLOSE_TIME;					//���ݹ���ʱ�� 
int INTERVAL_TIME;				//��������һ��¥��ʱ��
int STOP_TIME;					//������һ��¥��ͣ��ʱ�� 

int Strategy;					//���� 
int Change_Signal;				//״̬�ı��ź�

clock_t Start, End;				//��¼��ʼ������ʱ�� 
HANDLE hTimeMutex; 				//ʱ�以����� 
  

#endif
