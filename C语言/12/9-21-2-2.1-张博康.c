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
	FILE *fp = fopen("file1.dat", "wb");
	int i, n;
	
	printf("Please input the number of the students:");
	scanf("%d\n", &n);
	printf("Please input the information of the students:\n");
	for(i=0; i<=n-1; i++) //读入数据 
	{
		scanf("%s", &inf[i].name);
		scanf("%s", &inf[i].num);
		scanf("%d\n", &inf[i].score);
	}
	fwrite(&n, sizeof(n), 1, fp); //向二进制文件写入n 
	fwrite(inf, sizeof(inf), n, fp); //向二进制文件写入学生信息 
	fclose(fp);
	
	return 0;
}
