#pragma once

#include <iostream>

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
	virtual ~base()  {
		cout << "base destructor" << endl;
		delete[] b;
	}

private:
	int* b;
};



