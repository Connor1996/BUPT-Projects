#include<iostream>
#include<cstdlib>
#include<ctime> 

using namespace std;

int main()
{
	int value;
	
	srand(time(NULL));  //���������ʼ�� 
	int price = rand() % 1000 + 1;	//�������1-1000�ļ۸� 
	
	cout << "How much do you think the value is? (1-1000)" << endl;
	while(cin >> value, value < 1 || value > 1000)	//�ж�����������Ƿ�Ϸ� 
	{
		cout << "Sorry, the selected value is unavailable! Please try again." << endl;
		cin.clear();	//��ԭ��������״̬����λ 
		cin.sync();		//��������������� 
	}
	while(value != price)	// 
	{
		if(value > price)
			cout << "The value is higher than the value. Please try again." << endl;
		else if(value < price)
			cout << "The value is lower than the value. Please try again." << endl;
		else
			break;
		while(cin >> value, value < 1 || value > 1000)	//�ж�����������Ƿ�Ϸ� 
		{
			cout << "Sorry, the selected value is unavailable! Please try again." << endl;
			cin.clear();
			cin.sync();
		}
	}	
	cout << "How clever you are!";
	
	return 0;
 } 
