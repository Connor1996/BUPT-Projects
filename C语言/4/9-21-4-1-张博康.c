#include<stdio.h>

int main()
{
	int i;
	int model,num;
	double price,ans=0;	
	
	printf("请输入周一至周五各天销售情况（产品号，销售量），产品号为-1代表该天输入结束\n");
	for(i=1;i<=5;i++)
	{
		printf("周%d销售情况：\n",i);
		while(1)
		{
			scanf("%d",&model);
			if(model==-1) //当得到-1跳出循环 
				break;
			scanf(",%d",&num);
			switch(model) //产品所对应的价格 
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
			ans+=num*price; //累加器得到总额 
		}
	}
	printf("本周销售总额为：%lf",ans);
	
	return 0;
}
 
