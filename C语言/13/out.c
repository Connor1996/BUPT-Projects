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
	FILE *fp = fopen("file1.dat", "ab"); 
	int i, n;
	
	printf("Please input the number of the students that you want to add:");
	scanf("%d\n", &n);
	printf("Please input the information of the students that you want to add:\n");
	for(i=0; i<=n-1; i++) 
	{
		scanf("%s", &inf[i].name);
		scanf("%s", &inf[i].num);
		scanf("%d\n", &inf[i].score);
	}
	*
	return 0;
}
