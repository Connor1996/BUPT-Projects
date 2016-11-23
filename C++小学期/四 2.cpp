#include <iostream>

using namespace std;

const double PI = 3.1415926;

class Shape
{
	public:
		Shape()
		{
			cout << "//Shape's constructor is called." << endl;
		}
		~Shape()
		{
			cout << "//Shape's destructor is called." << endl;
		}
		virtual double getArea() = 0;
}; 

class Rectangle: public Shape
{
	public:
		Rectangle(double len, double wid) : length(len), width(wid) //Rectangle构建函数，使用初始化列表 
		{
			cout << "//Rectangle's constructor is called." << endl;
		} 
		~Rectangle() //Rectangle析构函数 
		{
			cout << "//Rectangle's destructor is called."	<< endl;
		}
		double getArea() //获得Rectangle的面积 
		{
			return length * width;
		}
	private:
		double length;
		double width;
};

class Circle: public Shape
{
	public:
		Circle(double rad) : radius(rad) //Circle构建函数，使用初始化列表
		{
			cout << "//Circle's constructor is called." << endl;
		}
		~Circle() //Circle析构函数 
		{
			cout << "//Circle's destructor is called." << endl;
		}
		double getArea() //获得Circle的面积 
		{
			return radius * radius * PI;
		}
	private:
		double radius;
};

class Square: public Rectangle
{
	public:
		Square(double side): Rectangle(side, side) //Square构建函数，使用初始化列表 
		{
			cout << "//Square's constructor is called." << endl;
		} 
		~Square() //Square析构函数 
		{
			cout << "//Square's destructor is called." << endl;
		}
		double getArea() //获得Square的面积 
		{
			return Rectangle::getArea(); 
		}
};
 
int main()
{
	double x, y;
	
	cout << "Please input the length and width of the rectangle." << endl;
	cin >> x >> y;
	Rectangle rectangle(x, y);
	cout << "The area of the rectangle is " << rectangle.getArea() << endl;
	cout << "Please input the radius of the circle." << endl;
	cin >> x;
	Circle circle(x);
	cout << "The area of the circle is " << circle.getArea() << endl;
	cout << "Please input the length of the side of square." << endl;
	cin >> x;
	Square square(x);
	cout << "The area of the square is " << square.getArea() << endl;
} 
