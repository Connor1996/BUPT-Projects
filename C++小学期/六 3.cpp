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
	while((ch = infile.get()) != EOF) //�ж��Ƿ��ļ���β 
	{
		if(ch != '\n')
			outfile << ch;
		else
			outfile << endl << i++ << ' '; //����к� 
	}
	
	infile.close(); //�ر������ļ� 
	outfile.close(); //�ر�����ļ� 
	
	return 0;
}
