#pragma once
#include "casttest.h"
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