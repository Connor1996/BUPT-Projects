#include<stdio.h>
#include<string.h>

typedef struct
{
	char name[50];
	char num[50];
	int score;
}information;

information inf[100];

void quicksort(information *inf, int left, int right) //�������� 
{
	int i, j;
	information key;
	
	if(left < right)
	{
		i = left;
		j = right;
		key = inf[left];
		while(i < j)
		{
			while(i < j)
			{
				if(inf[j].score<key.score)
					j--;
				else if(inf[j].score == key.score && strcmp(inf[j].num, key.num)>0)
					j--;
				else 
					break;
			}
			if(i < j)
				inf[i++] = inf[j];
			while(i < j)
			{
				if(inf[i].score>key.score)
					i++;
				else if(inf[i].score == key.score && strcmp(inf[i].num, key.num)<0)
					i++;
				else
					break;
			}
			if(i < j)
				inf[j--] = inf[i];
		}
		inf[i] = key;
		quicksort(inf, left, i-1);
		quicksort(inf, i+1, right); 
	}
	else
		return;
}

int main()
{
	FILE *fp2 = fopen("file2.dat", "wb");
	FILE *fp1 = fopen("file1.dat", "rb");
	int i, n;
	
	fread(&n, sizeof(n), 1, fp1); //�Ӷ������ļ�����n 
	fread(inf, sizeof(inf), n, fp1); //�Ӷ������ļ�����ѧ������ 
	quicksort(inf, 0, n-1); //���ɼ���ѧ������ 
	fwrite(inf, sizeof(inf), n, fp2); //��������ļ�д��n��ѧ������ 
	fclose(fp1); 
	fclose(fp2);
	
	return 0;
}
