#include <iostream> 
#include <cmath>

using namespace std;

class Point
{
	friend class Rectangle;
	public:
		Point() : x(0), y(0) { }; //Point无参构造函数，默认为0 
		Point(int _x, int _y) : x(_x), y(_y) { }; //Point带参构造函数，使用初始化列表 
		double getDistance(Point &, Point &) const;
	private:
		int x, y;
};

double Point::getDistance(Point &p1, Point &p2) const
{
	return sqrt((p2.y-p1.y) * (p2.y-p1.y) - (p2.x-p1.x) * (p2.x-p1.x));
}

class Rectangle
{
	public:
		Rectangle(Point &p1, Point &p2) : leftUp(p1), rightBottom(p2) { }; //Rectangle构造函数，使用初始化列表 
		long long getArea() const;
	private:
		Point leftUp;
		Point rightBottom;
};

long long Rectangle::getArea() const
{
	return abs((leftUp.x-rightBottom.x) * (leftUp.y-rightBottom.y));
}

int main()
{
	int x1, x2, y1, y2;
	cout << "Please input the ordniate of top left corner of the rectangle." << endl;
	cin >> x1 >> y1;
	Point p1(x1, y1); 
	cout << "Please input the ordniate of bottom right corner of the rectangle." << endl;
	cin >> x2 >> y2;
	Point p2(x2, y2);
	Rectangle rectangle(p1, p2);
	cout << "The area of the rectangle is " << rectangle.getArea() << endl;
	 

	return 0;
}
