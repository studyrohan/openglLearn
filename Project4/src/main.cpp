
#include <iostream>
#include <vector>
#include <forward_list>
#include <map>
#include "glad/include/glad/glad.h"
#include "GLFW/glfw3.h"


#include"../inc/header.h"
using namespace std;
class base {
public:
	void test()
	{
		cout << "base test" << std::endl;
	}
	base() {
		cout << "base constructor" << endl;
		int* b = new int[5];
	}
	~base() {
		cout << "base destructor" << endl;
		delete[] b;
	}

private:
	int* b;
};



class derived : public base {
public:
	derived() {
		cout << "derived constructor" << endl;
		int* d = new int[8];
	}
	~derived() {
		cout << "derived destructor" << endl;
		delete[] d;
	}
	void test()
	{
		cout << "derived test" << std::endl;
	}

private:
	int* d;
};
class A {
public:
	A();
	A(const A& a);
	A(const A& a,const A&b);
private:
	int a;
};
A::A()
	:a(0)
{

}
A::A(const A& a)
{
	this->a = a.a;
}

A::A(const A& a, const A& b)
{
	this->a = a.a + b.a;
}

using namespace std;
struct President
{
	std::string name;
	std::string country;
	int year;

	President(std::string p_name, std::string p_country, int p_year)
		: name(std::move(p_name)), country(std::move(p_country)), year(p_year)
	{
		cout << "    Construction\n";
	}
	President(const President& other)
		: name(std::move(other.name)), country(std::move(other.country)), year(other.year)
	{
		cout << "    Copy Construction\n";
	}
	President(President&& other)
		: name(std::move(other.name)), country(std::move(other.country)), year(other.year)
	{
		cout << "    Move Construction\n";
	}
};
int testVector()
{
	cout << "emplace_back to vector:\n";
	vector<President> v1;
	v1.emplace_back("Nelson Mandela", "South Africa", 1994);

	President tem("daf","asdfsdaf",9);
	v1.emplace_back(tem);



	cout << "\npush_back to vector (way-1 - right value reference as parameter):\n";
	vector<President> v2;
	v2.push_back(President("Nelson Mandela", "South Africa", 1994));

	cout << "\npush_back to vector (way-2 - left value as parameter):\n";
	vector<President> v3;
	President p1("Nelson Mandela", "South Africa", 1994);
	v3.push_back(p1);

	cout << "\ninsert into map: \n";
	map<int, President> m1;
	m1.insert(make_pair<int, President>(10, President("Nelson Mandela", "South Africa", 1994)));

	cout << "\nemplace into map: \n";
	map<int, President> m2;
	m2.emplace(10, President("Nelson Mandela", "South Africa", 1994));


	std::vector<int>a;
	int b = 0,c= 1,d =2;
	a.push_back(b);
	a.emplace_back(c);
	return 0;
}
void testForwardList()
{
	std::forward_list a{ 1,2,3 };
	
	a.emplace_front(0);
	a.push_front(-1);
	a.emplace_after(a.end(), 8);
	for (auto item:a)
	{
		std::cout << item << ",";
	}
	
}

//int main()
//{
//	base* pBase = new derived;
//	pBase->test();
//	cout << "---" << endl;
//	delete pBase;
//
//	return 0;
//}
int main()
{
	//start();
	//testVector();
	testForwardList();
	system("Pause");
	return 0;
}