#include<iostream>
#include<cstdlib>
#include<ctime> 

using namespace std;

int main()
{
	int value;
	
	srand(time(NULL));  //随机函数初始化 
	int price = rand() % 1000 + 1;	//随机产生1-1000的价格 
	
	cout << "How much do you think the value is? (1-1000)" << endl;
	while(cin >> value, value < 1 || value > 1000)	//判断输入的数据是否合法 
	{
		cout << "Sorry, the selected value is unavailable! Please try again." << endl;
		cin.clear();	//复原输入流的状态比特位 
		cin.sync();		//清空输入流缓冲区 
	}
	while(value != price)	// 
	{
		if(value > price)
			cout << "The value is higher than the value. Please try again." << endl;
		else if(value < price)
			cout << "The value is lower than the value. Please try again." << endl;
		else
			break;
		while(cin >> value, value < 1 || value > 1000)	//判断输入的数据是否合法 
		{
			cout << "Sorry, the selected value is unavailable! Please try again." << endl;
			cin.clear();
			cin.sync();
		}
	}	
	cout << "How clever you are!";
	
	return 0;
 } 
