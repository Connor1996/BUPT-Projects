#include<stdio.h>

int main()
{
	int ans;
	int i,j,k,l;
			
	for(i='W';i<='Z';i++) //����A�Ķ��� 
	{
		if(i=='X')
			continue;
		for(j='W';j<='Z';j++) //����B�Ķ��� 
		{
			if(i==j)
				continue;
			for(k='W';k<='Y';k++) //����C�Ķ��� 
			{
				if(k==i||k==j)
					continue;
				if(k=='X')
					continue;
				for(l='X';l<='Z';l++) //����D�Ķ��� 
				{
					if(l==i||l==j||l==k)
						continue;
					ans++;
					printf("Group %d:\n",ans);
					printf("A VS %c\n",i);
					printf("B VS %c\n",j);
					printf("C VS %c\n",k); 
					printf("D VS %c\n\n",l);
					break;
				}
			}
		}
	}
	printf("There are %d ways to assign the players.",ans);
	
	return 0;
}
