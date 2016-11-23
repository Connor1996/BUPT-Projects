#include <iostream>

using namespace std;

const double PI = 3.1415926;

class Shape
{
	public:
		Shape() //Shape构建函数 
		{
			cout << "//Shape's constructor is called." << endl;
		}
		~Shape() //Shape析构函数 
		{
			cout << "//Shape's destructor is called." << endl;
		}
		double getArea() //得到面积 
		{
			return area;
		}
	protected:
		double area;
}; 

class Rectangle: public Shape
{
	public:
		Rectangle(double len, double wid) : length(len), width(wid), area(len * wid) //Rectangle构建函数，使用初始化列表 
		{
			cout << "//Rectangle's constructor is called." << endl;
		} 
		~Rectangle() //Rectangle析构函数 
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
		Circle(double rad) : radius(rad), area(radius * radius * PI) //Circle构建函数，使用初始化列表
		{
			cout << "//Circle's constructor is called." << endl;
		}
		~Circle() //Circle析构函数 
		{
			cout << "//Circle's destructor is called." << endl;
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
};
 
int main()
{
	double x, y;
	
	cout << "Please input the length and width of the rectangle." << endl;
	cin >> x >> y;
	Rectangle rectangle(x, y); //定义一个Rectangle对象 
	cout << "The area of the rectangle is " << rectangle.getArea() << endl;
	cout << "Please input the radius of the circle." << endl;
	cin >> x;
	Circle circle(x); //定义一个Circle对象 
	cout << "The area of the circle is " << circle.getArea() << endl;
	cout << "Please input the length of the side of square." << endl;
	cin >> x;
	Square square(x); //定义一个Square对象 
	cout << "The area of the square is " << square.getArea() << endl;
} 
