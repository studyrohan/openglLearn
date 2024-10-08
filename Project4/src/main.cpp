
#include <iostream>
#include <vector>
#include <forward_list>
#include <map>
#include <list>
#include "glad/include/glad/glad.h"
#include "GLFW/glfw3.h"


#include"../inc/header.h"
#include "../casttest.h"
#include "../castdrive.h"
#include <sstream>

using namespace std;

class derived;

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


	{
		base* b = new base();
		//derived* d = dynamic_cast<derived*>(b);
		static_cast<derived*>(b);
		auto d = (derived*)(b);

	}

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

void testSizeofString()
{
	std::string a;
	std::cout << sizeof(a) << std::endl;
	a.assign("da");
	a.front();
	a.back();
	a.push_back('k');
	a.pop_back();
	a.append("fads");
	a.max_size();
	a.capacity();


	a.data();
	a.c_str();
	a.length();
	a.at(0);
	a.size();
	a.reserve(9);
	a.resize(12);
	a.find('d');
	a.rfind('d');
	a.find_first_of('d');
	a.compare("da");
	a.substr(2);
	a.clear();
	a.insert(a.begin(),'d');

	std::cout << sizeof(a) << std::endl;
	a.append("fads");
	std::cout << sizeof(a) << std::endl;

	std::list<int>list;
	
	list.push_back(12);
	list.push_back(12);
	list.push_back(12);
	std::list<int>list2(list);
	std::list<int>list3 =list;

	list.clear();
	list2.clear();
	list3.clear();

}

int testStringStream()
{
	string a = "1+2i", b = "1+3i";
	std::istringstream sa(a), sb(b);
	std::ostringstream out;

	int ra, ia, rb, ib;
	char buff,buff1;
	// only read integer values to get the real and imaginary part of 
	// of the original complex number
	sa >> ra >> buff >> ia >> buff1;
	sb >> rb >> buff >> ib >> buff1;

	out << ra * rb - ia * ib << '+' << ra * ib + ia * rb << 'i';

	// final result in string format
	string result = out.str();
	return 0;
}
int main()
{
	//start();
	//testVector();
	testStringStream();
	testSizeofString();
	//testForwardList();
	system("Pause");
	return 0;
}