#include <iostream>

using namespace std;

const double PI = 3.1415926;

class Shape
{
	public:
		Shape() //Shape�������� 
		{
			cout << "//Shape's constructor is called." << endl;
		}
		~Shape() //Shape�������� 
		{
			cout << "//Shape's destructor is called." << endl;
		}
		double getArea() //�õ���� 
		{
			return area;
		}
	protected:
		double area;
}; 

class Rectangle: public Shape
{
	public:
		Rectangle(double len, double wid) : length(len), width(wid), area(len * wid) //Rectangle����������ʹ�ó�ʼ���б� 
		{
			cout << "//Rectangle's constructor is called." << endl;
		} 
		~Rectangle() //Rectangle�������� 
		{
			cout << "//Rectangle's destructor is called."	<< endl;
		}
	private:
		double length;
		double width;
};

class Circle: public Shape
{
	public:
		Circle(double rad) : radius(rad), area(radius * radius * PI) //Circle����������ʹ�ó�ʼ���б�
		{
			cout << "//Circle's constructor is called." << endl;
		}
		~Circle() //Circle�������� 
		{
			cout << "//Circle's destructor is called." << endl;
		}
	private:
		double radius;
};

class Square: public Rectangle
{
	public:
		Square(double side): Rectangle(side, side) //Square����������ʹ�ó�ʼ���б� 
		{
			cout << "//Square's constructor is called." << endl;
		} 
		~Square() //Square�������� 
		{
			cout << "//Square's destructor is called." << endl;
		}
};
 
int main()
{
	double x, y;
	
	cout << "Please input the length and width of the rectangle." << endl;
	cin >> x >> y;
	Rectangle rectangle(x, y); //����һ��Rectangle���� 
	cout << "The area of the rectangle is " << rectangle.getArea() << endl;
	cout << "Please input the radius of the circle." << endl;
	cin >> x;
	Circle circle(x); //����һ��Circle���� 
	cout << "The area of the circle is " << circle.getArea() << endl;
	cout << "Please input the length of the side of square." << endl;
	cin >> x;
	Square square(x); //����һ��Square���� 
	cout << "The area of the square is " << square.getArea() << endl;
} 
