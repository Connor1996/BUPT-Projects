#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	char filename[100];
	
	cout << "Please input the name of the file that you want to open." << endl;
	cin >> filename;
	ifstream infile(filename);
	cout << "Please input the name of the file that you want to output." << endl;
	cin >> filename;
	ofstream outfile(filename);
	
	char ch;
	int i = 2;
	outfile << "1 ";
	while((ch = infile.get()) != EOF) //判断是否到文件结尾 
	{
		if(ch != '\n')
			outfile << ch;
		else
			outfile << endl << i++ << ' '; //输出行号 
	}
	
	infile.close(); //关闭输入文件 
	outfile.close(); //关闭输出文件 
	
	return 0;
}
