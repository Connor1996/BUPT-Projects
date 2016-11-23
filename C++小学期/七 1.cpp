#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <iomanip>

using namespace std;

class Person
{
	public:
		Person(string _name, string _callNumber = "") : name(_name), callNumber(_callNumber) { }; //Person�Ĺ��캯�����绰����Ĭ��Ϊ�գ���ʹ�ó�ʼ���б� 
		bool operator<(const Person &b) const //����С�������������set������ 
		{
			return this->name < b.name;
		} 
		bool operator==(const Person &b) const //���ص��������������set��find���� 
		{
			return this->name == b.name;
		}
		string getNumber() const //��õ绰���� 
		{
			return callNumber;
		}
		string getName() const //�����ϵ������ 
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
	
	cout << "��������ӵ���ϵ�˸�����";
	cin >> x;
	for(int i=0; i<x; i++)
	{
		string _name, _number;
		
		cout << "��������ϵ�˵������͵绰" << endl;
		cin >> _name >> _number;
		Person temp(_name, _number);
		set<Person>::iterator set_it = person.find(temp);
		if(set_it != person.end())
			cout << "��ǰ��ϵ���Ѵ��ڣ����ʧ�ܣ�" << endl; 
		else
			person.insert(temp); //����������ϵ�˲���set���� 
	}
}

void seek(set<Person> &person)
{
	string s;
	
	while(1)
	{
	 	cout << "��������ҵ���ϵ������(����:q����)" << endl;
	 	cin >> s;
	 	if(s == ":q")
	 		break;
	 	else
	 	{
	 		Person temp(s);
	 		set<Person>::iterator set_it = person.find(temp); //�������������¼�����ҵ�����ϵ�� 
	 		if(set_it == person.end())
			 	cout << "�����ڵ�ǰ��ϵ��" << endl;	
			else
				cout <<  "���ڵ�ǰ��ϵ�ˣ��绰����Ϊ��" << set_it->getNumber() << endl;
		}
	}
}

void del(set<Person> &person)
{
	string s;
	
	while(1)
	{
	 	cout << "������Ҫɾ������ϵ������(����:q����)" << endl;
	 	cin >> s;
	 	if(s == ":q")
	 		break;
	 	else
	 	{
	 		Person temp(s);
	 		set<Person>::iterator set_it = person.find(temp); //�������������¼Ҫɾ������ϵ�� 
	 		if(set_it == person.end())
			 	cout << "�����ڵ�ǰ��ϵ��" << endl;	
			else
			{
			 	person.erase(set_it); //��set������ɾ��Ԫ�� 
				cout <<  "���ڵ�ǰ��ϵ�ˣ�ɾ���ɹ���" << endl;
			}
		}
	}
}

int main()
{
	ifstream infile("book.txt", ios_base::in); //�����ļ������� 
	set<Person> person; //����Ԫ������ΪPerson���set���� 
	string _name, _number;
	
	while(infile >> _name >> _number)
	{
		Person temp(_name, _number); //������ʱPerson�� 
		person.insert(temp); //����ʱ��Person���뵽������ 
	}
	infile.close(); //�ر������ļ� 
	
	add(person); //�����ϵ�� 
	seek(person); //������ϵ�� 
	del(person); //ɾ����ϵ�� 
	
	ofstream outfile("book.txt", ios_base::out); //�����ļ������ 
	for(set<Person>::iterator i=person.begin(); i!=person.end(); i++) //�õ����ڱ���set�������Ԫ�� 
	{
		outfile << left << setw(20) << i->getName() << setw(20) << i->getNumber() << endl;	 
	}
	outfile.close();
	
	return 0;
}
