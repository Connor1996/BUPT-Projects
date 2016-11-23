#include<stdio.h>

int main()
{
	int n,m;
	int Nsquare=0,Nrectangle=0;
	
	printf("Please input two integers:");
	scanf("%d %d",&n,&m); 
	for(int p=0;p<=n-1;p++) //控制起点横坐标 
		for(int q=0;q<=m-1;q++)	//控制起点纵坐标 
			for(int i=p+1;i<=n;i++)	//控制末点横坐标 
				for(int j=q+1;j<=m;j++) //控制末点纵坐标 
				{
					if(i-p==j-q)
						Nsquare++;
					else 
						Nrectangle++; 
				}
	printf("The number of square is %d,The number of rectangle is %d",Nsquare,Nrectangle);
	
	return 0;	 
} 

