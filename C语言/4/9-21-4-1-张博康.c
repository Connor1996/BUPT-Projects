#include<stdio.h>

int main()
{
	int i;
	int model,num;
	double price,ans=0;	
	
	printf("��������һ��������������������Ʒ�ţ�������������Ʒ��Ϊ-1��������������\n");
	for(i=1;i<=5;i++)
	{
		printf("��%d���������\n",i);
		while(1)
		{
			scanf("%d",&model);
			if(model==-1) //���õ�-1����ѭ�� 
				break;
			scanf(",%d",&num);
			switch(model) //��Ʒ����Ӧ�ļ۸� 
			{
				case 1:
					price=2.98;
					break;
				case 2:
					price=4.50;
					break;
				case 3:
					price=9.98;
					break;
				case 4:
					price=4.49;
					break;
				case 5:
					price=6.87;
			}	
			ans+=num*price; //�ۼ����õ��ܶ� 
		}
	}
	printf("���������ܶ�Ϊ��%lf",ans);
	
	return 0;
}
 
