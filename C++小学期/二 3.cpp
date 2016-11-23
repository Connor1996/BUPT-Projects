#include <iostream>
#include <cmath>

using namespace std;

class Car;
class Boat
{
	friend double getTotalWeight(const Boat &, const Car &); //��Ԫ���� 
	public:
		Boat(double x)
		{
			weight = x;
		} 
	private:
		double weight;
};

class Car 
{
	friend double getTotalWeight(const Boat &, const Car &); //��Ԫ���� 
	public:
		Car(double x)
		{
			weight = x;
		}
	private:
		double weight;
};

double getTotalWeight(const Boat &b, const Car &c) //����ܹ������� 
{
	return b.weight + c.weight ;
}



int main()
{
	double w;
	
	cout << "Please input the weight of boat." << endl;
	cin >> w;
	Boat boat(w);
	cout << "Please input the weight of car." << endl;
	cin >> w;
	Car car(w);
	
	cout << "The total weight of boat and car is " << getTotalWeight(boat, car) << endl;
}
