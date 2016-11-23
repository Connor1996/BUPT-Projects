#include<stdio.h>

int isLeap(int);
int GetMonthDays(int,int);
int GetWeekDay(int,int,int);
void PrintMonthCalender(int,int);
 
int main()
{
	int year,month;
	int startDay,days;
	
	printf("Please input year and month:");
	scanf("%d %d",&year,&month);
	startDay=GetWeekDay(year,month,1);
	days=GetMonthDays(year,month);
	
	printf("The result is:\n");
	printf("\t\t\t    %d-%d\n",year,month);
	PrintMonthCalender(startDay,days);
	
	return 0;	
} 

int isLeap(int year) //判断是否闰年 
{
	if(year%4==0 && year%100!=0)
		return 1;
	else 
		return 0;
}

int GetMonthDays(int year,int month) //得到给定月的天数 
{
	switch(month)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			return 31;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			return 30;
			break;
		case 2:
			if(isLeap)
				return 29;
			else 	
				return 28;
			break;
	}
} 

int GetWeekDay(int year,int month,int day) //计算出给定日期是星期几 
{
	int days;
	int weekDay;
	
	days=year*365+year/400+year/4-year/100;
	for(int i=month;i<=12;i++)
	{
		days-=GetMonthDays(year,i);
	}
	days+=day;
	weekDay=days%7;
	
	return weekDay; 
}

void PrintMonthCalender(int startDay,int days) //打印日历 
{
	printf("Sun.\tMon.\tTue.\tWed.\tThu.\tFri.\tSat.\n");
	for(int i=0;i<startDay;i++)
	{
		printf("\t");
	}
	for(int i=1;i<=days;i++)
	{
		printf("%d",i);
		if((i+startDay)%7==0)
			printf("\n");
		else
			printf("\t");
	}
} 
