#include <iostream>

using namespace std;

class Point 
{
	public:
		Point(int xx, int yy) //Point类的构造函数 
		{
			x = xx;
			y = yy;
		}
		Point & operator++() //++p 
		{
			x++;
			y++;
			return *this;
		}
		Point operator++(int) //p++ 
		{
			Point temp = *this;
			++*this;
			return temp;
		}
		Point & operator--() //--p 
		{
			x--;
			y--;
			return *this;
		}
		Point operator--(int) //p--
		{
			Point temp = *this;
			--*this;
			return temp;
		}
		void print()
		{
			cout << x << ' ' << y << endl;
		}
	private:
		int x, y;
};

int main() {
	int x, y;
	cout << "Please input the ordinate of the point." << endl;
	cin >> x >> y;
	Point point(x, y);

	++point;
	cout<<"++p:";
	point.print();
	--point;
	cout<<"--p:";
	point.print();
	point++;
	cout<<"p++:";
	point.print();
	point--;
	cout<<"p--:";
	point.print();
	return 0;
}
