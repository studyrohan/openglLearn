
#include <iostream>
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
	testWenli();
}