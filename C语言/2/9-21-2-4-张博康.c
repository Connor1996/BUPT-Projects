#include<stdio.h> 

int main()
{
	int n,m;
	int even=0,odd=0;
	
	printf("Please input an integer:"); 
	scanf("%d",&n);
	while(n!=0) //�����ó�n��ÿλ�� 
	{
		m=n%10;
		n/=10;
		if(m%2==0) //�ж���ż 
			even=1;
		else
			odd=1;
	}
	printf("The result is:");
	if(even&&!odd)
		printf("even number only!");
	else
		if(!even&&odd)
			printf("odd number only!");
		else 
			printf("both!");
	return 0;	
}
