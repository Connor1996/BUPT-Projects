#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
	ofstream outfile("��ʽIO.txt"); //�����ļ������ 
	int _integer = -10;
	unsigned int _uinteger = 123;
	long long _long = 1230821083131;
	double _double = 3414.414142;
	string _string = "����һ���ַ���";
	
	outfile << setw(6) << _integer << endl;
	outfile << setw(6) << _uinteger << endl;
	outfile << setw(6) << _long << endl;
	outfile << setw(6) << _double << endl;
	outfile << setw(6) << _string << endl;
	
	int x = 154;
	outfile << dec << x << endl; //���ʮ�������� 
	outfile << oct << x << endl; //����˽������� 
	outfile << hex << x << endl; //���ʮ���������� 
	
	return 0; 
}
