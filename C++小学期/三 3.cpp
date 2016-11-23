#include <iostream>

using namespace std;

class Matrix
{
	public:
		Matrix(int, int);	
		Matrix(Matrix &);	
		~Matrix();			 
		static void input(Matrix &); 
		static void output(const Matrix &); 
		static Matrix plus(const Matrix &, const Matrix &);	
		static Matrix minus(const Matrix &, const Matrix &); 
		Matrix & operator=(const Matrix &);
	private:
		int lines, rows;
		int **pNode;	
}; 

Matrix::Matrix(int x, int y) : lines(x), rows(y) //矩阵构造函数 
{
	pNode = new int *[x]; //动态申请内存 
	for(int i=0; i<x; i++)
		pNode[i] = new int[y];
}

Matrix::Matrix(Matrix &M) : lines(M.lines), rows(M.rows)//矩阵复制构造函数 
{
	pNode = new int *[lines]; //动态申请内存 
	for(int i=0; i<lines; i++)
		pNode[i] = new int[rows];
} 

Matrix::~Matrix() //矩阵析构函数
{
	for(int i=0; i<lines; i++) //释放内存 
		delete [] pNode[i];
	delete [] pNode;
}
void Matrix::input(Matrix &M) //矩阵的读入 
{
	cout << "Please input the matrix." << endl;
	for(int i=0; i<M.lines; i++)
		for(int j=0; j<M.rows; j++)
			cin >> M.pNode[i][j];
}

void Matrix::output(const Matrix &M) //矩阵的输出
{
	for(int i=0; i<M.lines; i++)
	{
		for(int j=0; j<M.rows; j++)
			cout << M.pNode[i][j] << "\t";
		cout << endl;
	}
}

Matrix & Matrix::operator=(const Matrix &M)	//重载等号运算符 
{
	if(this != &M) //检查自赋值 
	{
		for(int i=0; i<this->lines; i++) //释放旧元素 
			delete [] this->pNode[i];
		delete [] this->pNode;
		this->pNode = new int *[M.lines]; //申请新空间 
		for(int i=0; i<M.lines; i++)
			this->pNode[i] = new int[M.rows];
		for(int i=0; i<M.lines; i++)
			for(int j=0; j<M.rows; j++)
				this->pNode[i][j] = M.pNode[i][j];
	}
}

Matrix Matrix::plus(const Matrix &matrix1, const Matrix &matrix2) //两矩阵相加，结果储存在另外一个矩阵  
{
	Matrix temp(matrix1.lines, matrix1.rows);
	for(int i=0; i<matrix1.lines; i++)
		for(int j=0; j<matrix1.rows; j++)
			temp.pNode[i][j] = matrix1.pNode[i][j] + matrix2.pNode[i][j]; 
	return temp;
}

Matrix Matrix::minus(const Matrix &matrix1, const Matrix &matrix2) //两矩阵相加，结果储存在另外一个矩阵
{
	Matrix temp(matrix1.lines, matrix2.rows);
	for(int i=0; i<matrix1.lines; i++)
		for(int j=0; j<matrix1.rows; j++)
			temp.pNode[i][j] = matrix1.pNode[i][j] - matrix2.pNode[i][j];
	return temp;
}

int main()
{
	int x, y;

	cout << "Please input lines and rows of the matrix." << endl;
	cin >> x >> y; 	
	Matrix A1(x, y);
	Matrix A2(x, y);
	Matrix A3(x, y); 
	
	Matrix::input(A1);
	Matrix::input(A2);
	cout << endl << "A3 = A1 + A2" << endl;
	A3 = Matrix::plus(A1, A2); 
	Matrix::output(A3);
	cout << endl << "A3 = A1 - A2" << endl;
	A3 = Matrix::minus(A1, A2);
	Matrix::output(A3);
	
	Matrix *pA1 = new Matrix(x, y);
	Matrix *pA2 = new Matrix(x, y); 
	Matrix *pA3 = new Matrix(x, y);

	
	Matrix::input(*pA1);
	Matrix::input(*pA2);
	cout << endl << "A3 = A1 + A2" << endl;
	*pA3 = Matrix::plus(*pA1, *pA2); 
	Matrix::output(*pA3);
	cout << endl << "A3 = A1 - A2" << endl;
	*pA3 = Matrix::minus(*pA1, *pA2);
	Matrix::output(*pA3);
	
	delete pA1; //释放指针 
	delete pA2;
	delete pA3;
	
	return 0;
} 
