#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <iomanip>

using namespace std;

class Person
{
	public:
		Person(string _name, string _callNumber = "") : name(_name), callNumber(_callNumber) { }; //Person的构造函数，电话号码默认为空，并使用初始化列表 
		bool operator<(const Person &b) const //重载小于运算符，用于set的排序 
		{
			return this->name < b.name;
		} 
		bool operator==(const Person &b) const //重载等于运算符，用于set的find函数 
		{
			return this->name == b.name;
		}
		string getNumber() const //获得电话号码 
		{
			return callNumber;
		}
		string getName() const //获得联系人姓名 
		{
			return name;
		} 
	private:
		string name;
		string callNumber;
};

void add(set<Person> &person)
{
	int x;
	
	cout << "请输入添加的联系人个数：";
	cin >> x;
	for(int i=0; i<x; i++)
	{
		string _name, _number;
		
		cout << "请输入联系人的姓名和电话" << endl;
		cin >> _name >> _number;
		Person temp(_name, _number);
		set<Person>::iterator set_it = person.find(temp);
		if(set_it != person.end())
			cout << "当前联系人已存在，添加失败！" << endl; 
		else
			person.insert(temp); //将新增的联系人插入set容器 
	}
}

void seek(set<Person> &person)
{
	string s;
	
	while(1)
	{
	 	cout << "请输入查找的联系人姓名(输入:q结束)" << endl;
	 	cin >> s;
	 	if(s == ":q")
	 		break;
	 	else
	 	{
	 		Person temp(s);
	 		set<Person>::iterator set_it = person.find(temp); //定义迭代器，记录被查找到的联系人 
	 		if(set_it == person.end())
			 	cout << "不存在当前联系人" << endl;	
			else
				cout <<  "存在当前联系人，电话号码为：" << set_it->getNumber() << endl;
		}
	}
}

void del(set<Person> &person)
{
	string s;
	
	while(1)
	{
	 	cout << "请输入要删除的联系人姓名(输入:q结束)" << endl;
	 	cin >> s;
	 	if(s == ":q")
	 		break;
	 	else
	 	{
	 		Person temp(s);
	 		set<Person>::iterator set_it = person.find(temp); //定义迭代器，记录要删除的联系人 
	 		if(set_it == person.end())
			 	cout << "不存在当前联系人" << endl;	
			else
			{
			 	person.erase(set_it); //从set容器中删除元素 
				cout <<  "存在当前联系人，删除成功！" << endl;
			}
		}
	}
}

int main()
{
	ifstream infile("book.txt", ios_base::in); //设置文件输入流 
	set<Person> person; //设置元素类型为Person类的set容器 
	string _name, _number;
	
	while(infile >> _name >> _number)
	{
		Person temp(_name, _number); //构建临时Person类 
		person.insert(temp); //将临时的Person插入到容器中 
	}
	infile.close(); //关闭输入文件 
	
	add(person); //添加联系人 
	seek(person); //查找联系人 
	del(person); //删除联系人 
	
	ofstream outfile("book.txt", ios_base::out); //设置文件输出流 
	for(set<Person>::iterator i=person.begin(); i!=person.end(); i++) //用迭代期遍历set，输出各元素 
	{
		outfile << left << setw(20) << i->getName() << setw(20) << i->getNumber() << endl;	 
	}
	outfile.close();
	
	return 0;
}
