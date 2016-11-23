#include <iostream>

using namespace std;

void init(int (*matrix)[5])	//�����ʼ������������ 
{
	cout << "Please input the matrix." << endl;
	for(int i=0; i<4; i++)
		for(int j=0; j<5; j++)
			cin >> matrix[i][j];
}

void output(const int (*matrix)[5])	//����ĸ�ʽ����� 
{
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<5; j++)
			cout << matrix[i][j] << "\t";
		cout << endl;
	}
}

void _plus(const int (*matrix1)[5], const int (*matrix2)[5], int (*matrix3)[5])	//��������ӣ��������������һ������ 
{
	for(int i=0; i<4; i++)
		for(int j=0; j<5; j++)
			matrix3[i][j] =	matrix1[i][j] + matrix2[i][j]; 
}

void _minus(const int (*matrix1)[5], const int (*matrix2)[5], int (*matrix3)[5]) //������������������������һ������ 
{
	for(int i=0; i<4; i++)
		for(int j=0; j<5; j++)
			matrix3[i][j] = matrix1[i][j] - matrix2[i][j];
}

int main()
{
	int (*pA1)[5], (*pA2)[5], (*pA3)[5]; //����ָ�룬��̬������������ 
	pA1 = new int[4][5];
	pA2 = new int[4][5];
	pA3 = new int[4][5];
	
	init(pA1);
	init(pA2);
	cout << endl << "A3 = A1 + A2" << endl;
	_plus(pA1, pA2, pA3);
	output(pA3);
	cout << endl << "A3 = A1 - A2" << endl;
	_minus(pA1, pA2, pA3);
	output(pA3);
	delete [] pA1;	//�ͷž���ռ� 
	delete [] pA2;
	delete [] pA3;
	
	return 0;
} 
