#include<stdio.h>
 
typedef struct
{
	char name[50];
	char num[50];
	int score;
}information;

int main()
{
	information inf[100];
	FILE *fp = fopen("file1.dat", "ab"); //以追加写方式打开二进制文件2 
	int i, n;
	
	printf("Please input the number of the students that you want to add:");
	scanf("%d\n", &n);
	printf("Please input the information of the students that you want to add:\n");
	for(i=0; i<=n-1; i++) //读入新添加学生的信息 
	{
		scanf("%s", &inf[i].name);
		scanf("%s", &inf[i].num);
		scanf("%d\n", &inf[i].score);
	}
	/*fwrite(&n, sizeof(n), 1, fp); //向二进制文件写入n 
	fwrite(inf, sizeof(inf), n, fp); //向二进制文件写入新添入的学生信息 
	fclose(fp);
	**/*
	return 0;
}
