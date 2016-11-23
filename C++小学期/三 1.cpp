#include <iostream>

using namespace std;

void init(int (&matrix)[4][5])	//矩阵初始化，输入数据 
{
	cout << "Please input the matrix." << endl;
	for(int i=0; i<4; i++)
		for(int j=0; j<5; j++)
			cin >> matrix[i][j];
}

void output(const int (&matrix)[4][5])	//矩阵的格式化输出 
{
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<5; j++)
			cout << matrix[i][j] << "\t";
		cout << endl;
	}
}

void _plus(const int (&matrix1)[4][5], const int (&matrix2)[4][5], int (&matrix3)[4][5])	//两矩阵相加，结果储存在另外一个矩阵 
{
	for(int i=0; i<4; i++)
		for(int j=0; j<5; j++)
			matrix3[i][j] =	matrix1[i][j] + matrix2[i][j]; 
}

void _minus(const int (&matrix1)[4][5], const int (&matrix2)[4][5], int (&matrix3)[4][5])	//两矩阵相减，结果储存在另外一个矩阵 
{
	for(int i=0; i<4; i++)
		for(int j=0; j<5; j++)
			matrix3[i][j] = matrix1[i][j] - matrix2[i][j];
}

int main()
{
	int A1[4][5], A2[4][5], A3[4][5];	//定义三个矩阵 
	
	init(A1);
	init(A2);
	cout << "A3 = A1 + A2" << endl;
	_plus(A1, A2, A3);
	output(A3);
	cout << "A3 = A1 - A2" << endl;
	_minus(A1, A2, A3);
	output(A3);
	
	return 0;
} 
