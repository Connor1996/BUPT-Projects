#include<stdio.h>
#include<math.h>

int main()
{
	int i,j,a,b,c;
	int sum=1;
	int ans=0; //满足条件的数的个数 
	
	printf("Input three integers:");
	scanf("%d %d %d",&a,&b,&c);
	printf("The result is:\n");
	for(i=a;i<=b;i++)
	{
		if(i==1)
			continue;
		j=2;
		while(j*j<=i) //计算因数之和 
		{
			if(i%j==0)
		    	if(j!=i/j)
					sum+=j+i/j; 
				else 
					sum+=j;
			j++;
		}
		if(fabs(i-sum)<=c) //判断是否满足条件，若满足按格式输出 
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
