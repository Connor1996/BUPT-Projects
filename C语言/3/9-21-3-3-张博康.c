#include<stdio.h>
#include<math.h>

int main()
{
	int i,j,a,b,c;
	int sum=1;
	int ans=0; //�������������ĸ��� 
	
	printf("Input three integers:");
	scanf("%d %d %d",&a,&b,&c);
	printf("The result is:\n");
	for(i=a;i<=b;i++)
	{
		if(i==1)
			continue;
		j=2;
		while(j*j<=i) //��������֮�� 
		{
			if(i%j==0)
		    	if(j!=i/j)
					sum+=j+i/j; 
				else 
					sum+=j;
			j++;
		}
		if(fabs(i-sum)<=c) //�ж��Ƿ����������������㰴��ʽ��� 
		{
			ans++; 
			if(ans%5==0)
				printf("%d\n",i);
			else 
				printf("%d\t",i);
		}
		sum=1;
	} 
	if(ans==0)
		printf("There is no proper nnumber in the interval."); 
		
	return 0;
} 
