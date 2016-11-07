#include "stdafx.h"
#include "set.h"
#include <algorithm>
#include <iostream>
using namespace std;
class MyClass
{
public:
	MyClass() : d(0) {};
	MyClass(int ad) : d(ad) {};
	bool operator == (MyClass const &m) const { return d == m.d; };
	bool operator > (MyClass const &m) const { return d > m.d; };
	bool operator < (MyClass const &m) const { return d < m.d; };
	friend ostream &operator << (ostream &os, MyClass const &m);
	friend istream &operator >> (istream &is, MyClass &m);
private:
	int d;
};
ostream &operator << (ostream &os, MyClass const &m)
{
	os << m.d;
	return os;
};
istream &operator >> (istream &is, MyClass &m)
{
	is >> m.d;
	return is;
};
int main()
{
	typedef ISet<MyClass>::iterator iterator;
	iterator iter;
	ISet<MyClass> set;
	cout << "Set:\n";
	cin >> set;
	ISet<MyClass> set2;
	cout << "Set2:\n";
	cin >> set2;
	cout << "Set + Set2:\n";
	cout << set + set2 << endl;
	cout << "Set * Set2:\n";
	cout << set * set2 << endl;
	cout << "Set - Set2:\n";
	cout << set - set2 << endl;
	cout << "Set / Set2:\n";
	cout << set / set2 << endl;
	cout << "Set[Set2] = 9:\n";
	set[set2] = MyClass(9);
	cout << set << endl;
	cout << "Set2:\n";
	for (iterator i : set2)
	{
		cout << i->get_value() << ' ';
	}
	cout << endl;
	system("pause");
	return 0;
}

