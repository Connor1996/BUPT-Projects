#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
	ofstream outfile("流式IO.txt"); //设置文件输出流 
	int _integer = -10;
	unsigned int _uinteger = 123;
	long long _long = 1230821083131;
	double _double = 3414.414142;
	string _string = "这是一个字符串";
	
	outfile << setw(6) << _integer << endl;
	outfile << setw(6) << _uinteger << endl;
	outfile << setw(6) << _long << endl;
	outfile << setw(6) << _double << endl;
	outfile << setw(6) << _string << endl;
	
	int x = 154;
	outfile << dec << x << endl; //输出十进制数字 
	outfile << oct << x << endl; //输出八进制数字 
	outfile << hex << x << endl; //输出十六进制数字 
	
	return 0; 
}
