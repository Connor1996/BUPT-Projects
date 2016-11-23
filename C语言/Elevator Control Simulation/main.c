/*********************************************************************************************
                                       �汾������־ 
																		by: �Ų����������� 
Version 0.1 (due. 2015.5.8):
	ʵ�������ȷ������

Version 0.2 (due. 2015.5.9):
	���������г�ʼ������
	���Ӳ���ѡ�������ȷ���˳�������δʵ�֣�
	
Version 0.2.1 (due. 2015.5.10):
	���Ӳ���ѡ���е�������

Version 0.3 (due. 2015.5.11): 
	ʵ�ֵ�������״̬�Զ��������
 
Version 0.3.1 (due. 2015.5.12): 
	�޸��˵������е�0���bug 

Version 0.4 (due. 2015.5.13): 
	������״̬���������Ϊ״̬�ı�ʱ��� 
	 
Version 0.5 (due. 2015.5.13):
	ʵ����˳��������
	������variable.h�е�ȫ�ֱ��� 

Version 0.6 (due. 2015.5.14):
	���ӵ����ſ���״̬����� 
	�޸��˵��ݰ�ť״̬δ���»ᵼ�µ��ݽ��������ص�����¥���bug 
	�޸��˵�ǰ¥�㷢������ʱ���ݲ����п����Ų�����bug 
	
Version 0.7 (due. 2015.5.15):	
	�Դ����������ϸ��ע��
	
Version 0.8 (due. 2015.5.20): 
	��ӿ��Ű�ťGO״̬�����Խ��м�ʱ�Ĺ���
	���ʱ�以������Խ������״̬����ʱ��̶����������bug
	
Version 0.8.3 (due. 2015.5.20):
	�����Զ������öԿ�����ʱ��ĵ���
	�����Զ������ö����¥�����ĵ����������ܳ���9�㣩 
	�����������Ӧ���Ե�ѡ����δʵ�֣� 

Version 0.9 (due. 2015.5.21):
	ʵ���������Ӧ����
	
Version 1.0beta (due. 2015.5.22):
	�����������Ϣ���� 
	���״̬������ļ��Ĺ���
	����������EOF�Զ���������Ĺ���
	�����˿�ͷ��������������˵�� 
	�����״�ͻ��1000�� 
	
Version 1.1 (due. 2015.5.29)
	���Ӳ���ʵʱ�л��Ĺ��ܣ�����δ���£���ͼ�ν���汾��ʵ�֣� 
 
*********************************************************************************************/
#include "variable.h"
#include "queue.h"
#include "string.h"
 
int main() 
{
	//�̶߳���
	HANDLE hThread_Input, hThread_Control, hThread_Output; 										 
	hTimeMutex = CreateMutex(NULL, FALSE, "TIME");
	//������Ϣ���� 
	printf("********************************************************************************");
	printf("*                         Elevator Control System                              *");
	printf("*              Please choose one strategy to control the elevator:             *");
	printf("*                    1.�����ȷ���   2.˳�����   3.�����Ӧ                    *");
	printf("*                                                                              *"); 
	printf("*              ��������˵����                                                  *");
	printf("*              *******************************************************         *");
	printf("*              *       ��������       |           ��Ӧָ��           *         *");
	printf("*              *-----------------------------------------------------*         *");
	printf("*              *Q��W��E��R��T��Y��U��I|�ⲿ1��2��3��4��5��6��7��8����*         *");
	printf("*              *-----------------------------------------------------*         *");
	printf("*              *A��S��D��F��G��H��J��K|�ⲿ2��3��4��5��6��7��8��9����*         *"); 
	printf("*              *-----------------------------------------------------*         *");
	printf("*              *1��2��3��4��5��6��7��8|�ڲ�1��2��3��4��5��6��7��8��9 *         *");
	printf("*              *         ��9          |            ������            *         *"); 
	printf("*              *******************************************************         *");
	printf("*                                                                              *");
	printf("********************************************************************************");
	printf("Please input the number of the strategy:\n");
	//����ѡ���е�����ֻ������1��2��3 
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
	
	//����1�������ȷ�����̴߳��� 
	if(Strategy == 1)
	{
		pq = InitQueue();
		hThread_Input = CreateThread(NULL, 0, Input_FCF, NULL, 0, NULL);
		hThread_Control = CreateThread(NULL, 0, Control_FCF, NULL, 0, NULL);
		hThread_Output = CreateThread(NULL, 0, Output, NULL, 0, NULL); 
	}
	//����2��3��˳�����/�����Ӧ������̴߳��� 
	else if(Strategy == 2 || Strategy == 3)
	{
		hThread_Input = CreateThread(NULL, 0, Input_IPS, NULL, 0, NULL);
		hThread_Control = CreateThread(NULL, 0, Control_IPS, NULL, 0, NULL);
		hThread_Output = CreateThread(NULL, 0, Output, NULL, 0, NULL); 
	}
	
	CloseHandle(hThread_Input);
	CloseHandle(hThread_Control);
	CloseHandle(hThread_Output);
	
	//��������ͣ 
	Sleep(400000);
		
	return 0;
}
