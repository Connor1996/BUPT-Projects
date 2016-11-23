#include "variable.h"
#include "control.h"
#include "output.h" 

DWORD WINAPI Output()
{
	fp = fopen("elevator_running_record.txt", "w");
	Running_Time = clock(); 
	
	printf("State = FREE Door = CLOSE Direction = NONE CurrentFloor = %d DestinationFloor = %d", Current_Floor, Destination_Floor);
	while(1)
	{
		//检测到变化状态再输出 
		if(Change_Signal)
		{
			WaitForSingleObject(hTimeMutex, INFINITE);	
			Print_File(); 				//输出到文件 
			Print_Screen();				//输出到命令行(屏幕) 
			Change_Signal = 0;			//输出完后修改信号状态 
			ReleaseMutex(hTimeMutex);	//输出完后释放互斥对象权限，用以控制模块继续运行 
		}	
	}
}

//输出到命令行(屏幕) 
void Print_Screen()
{
	printf("RunningTime = %.2lfs\n", (clock()-Running_Time)*1.0/CLOCKS_PER_SEC);
	printf("State = ");
	switch(State)
	{
		case RUN:
			printf("RUN "); break;
		case STOP:
			printf("STOP"); break;
		case FREE:		
			printf("FREE");
	}
	printf(" Door = ");
	switch(Door)
	{
		case OPEN:
			printf("OPEN "); break;
		case CLOSED:
			printf("CLOSE");
	}
	printf(" Direction = "); 
	switch(Direction)
	{
		case UP:
			printf(" UP "); break;
		case DOWN:
			printf("DOWN"); break;
		case NONE:
			printf("NONE"); 	
	}
	printf(" CurrentFloor = %d DestinationFloor = %d", Current_Floor, Destination_Floor);
	if(State == STOP && Door == CLOSED)
	printf("STOP TIME = %.2lfs\n", (End - Start + CLOSE_TIME + OPEN_TIME)*1.0/CLOCKS_PER_SEC);
	int i;
	printf("Up Request: ");
	for(i=1; i<=MAXFLOOR-1; i++)
		if(Up_Button[i] == 1)
			printf("%d ", i);
	printf("\nDown Request: ");
	for(i=2; i<=MAXFLOOR; i++)
		if(Down_Button[i] == 1)
			printf("%d ", i);
	printf("\nFloor Request: ");
	for(i=1; i<=MAXFLOOR; i++)
		if(Inside_Button[i] == 1)
			printf("%d ", i);
	printf("\n\n");	
}

//输出到文件 
void Print_File()
{
//	fp = fopen("elevator_running_record.txt", "a+");
	
	fprintf(fp, "RunningTime = %.2lfs\n", (clock()-Running_Time)*1.0/CLOCKS_PER_SEC);
	fprintf(fp, "State = ");
	switch(State)
	{
		case RUN:
			fprintf(fp, "RUN "); break;
		case STOP:
			fprintf(fp, "STOP"); break;
		case FREE:	
			fprintf(fp, "FREE");
		}
	fprintf(fp, " Door = ");
	switch(Door)
	{
		case OPEN:
			fprintf(fp, "OPEN "); break;
		case CLOSED:
			fprintf(fp, "CLOSE");
	}
	fprintf(fp, " Direction = "); 
	switch(Direction)
	{
		case UP:
			fprintf(fp, " UP "); break;
		case DOWN:
			fprintf(fp, "DOWN"); break;
		case NONE:
			fprintf(fp, "NONE"); 	
	}
	fprintf(fp, " CurrentFloor = %d  DestinationFloor = %d\n", Current_Floor, Destination_Floor);
	if(State == STOP && Door == CLOSED)
		fprintf(fp, "STOP TIME = %.2lfs\n", (End - Start + CLOSE_TIME + OPEN_TIME)*1.0/CLOCKS_PER_SEC);
	fprintf(fp, "Up Request: ");
	int i;
	for(i=1; i<=MAXFLOOR-1; i++)
		if(Up_Button[i] == 1)
			fprintf(fp, "%d ", i);
	fprintf(fp, "\nDown Request: ");
	for(i=2; i<=MAXFLOOR; i++)
		if(Down_Button[i] == 1)
			fprintf(fp, "%d ", i);
	fprintf(fp, "\nFloor Request: ");
	for(i=1; i<=MAXFLOOR; i++)
		if(Inside_Button[i] == 1)
			fprintf(fp, "%d ", i);
	fprintf(fp, "\n\n");
	fflush(fp);		
//fclose(fp);
} 
