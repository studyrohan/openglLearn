
#include <windows.h>
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
#include <thread>
#include <assert.h>
#include <mutex>


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

// Declare an object of this type in a scope in order to suppress
// all floating-point exceptions temporarily. The old exception
// state will be reset at the end.
class FPExceptionDisabler
{
public:
	FPExceptionDisabler()
	{
		// Retrieve the current state of the exception flags. This
		// must be done before changing them. _MCW_EM is a bit
		// mask representing all available exception masks.
		_controlfp_s(&mOldValues, _MCW_EM, _MCW_EM);
		// Set all of the exception flags, which suppresses FP
		// exceptions on the x87 and SSE units.
		_controlfp_s(0, _MCW_EM, _MCW_EM);
	}
	~FPExceptionDisabler()
	{
		// Clear any pending FP exceptions. This must be done
		// prior to enabling FP exceptions since otherwise there
		// may be a 'deferred crash' as soon the exceptions are
		// enabled.
		_clearfp();

		// Reset (possibly enabling) the exception status.
		_controlfp_s(0, mOldValues, _MCW_EM);
	}

private:
	unsigned int mOldValues;

	// Make the copy constructor and assignment operator private
	// and unimplemented to prohibit copying.
	FPExceptionDisabler(const FPExceptionDisabler&);
	FPExceptionDisabler& operator=(const FPExceptionDisabler&);
};

// Declare an object of this type in a scope in order to enable a
// specified set of floating-point exceptions temporarily. The old
// exception state will be reset at the end.
// This class can be nested.
class FPExceptionEnabler
{
public:
	// Overflow, divide-by-zero, and invalid-operation are the FP
	// exceptions most frequently associated with bugs.
	FPExceptionEnabler(unsigned int enableBits = _EM_OVERFLOW |
		_EM_ZERODIVIDE | _EM_INVALID)
	{
		// Retrieve the current state of the exception flags. This
		// must be done before changing them. _MCW_EM is a bit
		// mask representing all available exception masks.
		_controlfp_s(&mOldValues, _MCW_EM, _MCW_EM);

		// Make sure no non-exception flags have been specified,
		// to avoid accidental changing of rounding modes, etc.
		enableBits &= _MCW_EM;

		// Clear any pending FP exceptions. This must be done
		// prior to enabling FP exceptions since otherwise there
		// may be a 'deferred crash' as soon the exceptions are
		// enabled.
		_clearfp();

		// Zero out the specified bits, leaving other bits alone.
		_controlfp_s(0, ~enableBits, enableBits);
	}
	~FPExceptionEnabler()
	{
		// Reset the exception state.
		_controlfp_s(0, mOldValues, _MCW_EM);
	}

private:
	unsigned int mOldValues;

	// Make the copy constructor and assignment operator private
	// and unimplemented to prohibit copying.
	FPExceptionEnabler(const FPExceptionEnabler&);
	FPExceptionEnabler& operator=(const FPExceptionEnabler&);
};

int __cdecl DescribeException(PEXCEPTION_POINTERS pData, const char* pFunction)
{
	// Clear the exception or else every FP instruction will
	// trigger it again.
	_clearfp();

	DWORD exceptionCode = pData->ExceptionRecord->ExceptionCode;
	const char* pDescription = NULL;
	switch (exceptionCode)
	{
	case STATUS_FLOAT_INVALID_OPERATION:
		pDescription = "float invalid operation";
		break;
	case STATUS_FLOAT_DIVIDE_BY_ZERO:
		pDescription = "float divide by zero";
		break;
	case STATUS_FLOAT_OVERFLOW:
		pDescription = "float overflow";
		break;
	case STATUS_FLOAT_UNDERFLOW:
		pDescription = "float underflow";
		break;
	case STATUS_FLOAT_INEXACT_RESULT:
		pDescription = "float inexact result";
		break;
	case STATUS_FLOAT_MULTIPLE_TRAPS:
		// This seems to occur with SSE code.
		pDescription = "float multiple traps";
		break;
	default:
		pDescription = "unknown exception";
		break;
	}

	void* pErrorOffset = 0;
#if defined(_M_IX86)
	void* pIP = (void*)pData->ContextRecord->Eip;
	pErrorOffset = (void*)pData->ContextRecord->FloatSave.ErrorOffset;
#elif defined(_M_X64)
	void* pIP = (void*)pData->ContextRecord->Rip;
#else
#error Unknown processor
#endif

	printf("Crash with exception %x (%s) in %s at %p!n",
		exceptionCode, pDescription, pFunction, pIP);

	if (pErrorOffset)
	{
		// Float exceptions may be reported in a delayed manner -- report the
		// actual instruction as well.
		printf("Faulting instruction may actually be at %p.n", pErrorOffset);
	}

	// Return this value to execute the __except block and continue as if
	// all was fine, which is a terrible idea in shipping code.
	return EXCEPTION_EXECUTE_HANDLER;
	// Return this value to let the normal exception handling process
	// continue after printing diagnostics/saving crash dumps/etc.
	//return EXCEPTION_CONTINUE_SEARCH;
}

static float g_zero = 0;

void TryDivByZero()
{
	__try
	{
		float inf = 1.0f / g_zero;
		printf("No crash encountered, we successfully calculated %f.n", inf);
	}
	__except (DescribeException(GetExceptionInformation(), __FUNCTION__))
	{
		// Do nothing here - DescribeException() has already done
		// everything that is needed.
	}
}

int testAutomic()
{
	{
		std::atomic<int> x{ 0 }, y{ 0 }, z{ 0 };
		//l. The only ordering imposed is that once a value for a variable from 
		//thread 1 is observed in thread 2, thread 2 can not see an ¡°earlier¡± value 
		//for that variable from thread 1.
		auto fun1 = [&]()
		{
			x.store(1, memory_order_relaxed);
			std::cout << "x.store(1, memory_order_relaxed);\n";
			x.store(2, memory_order_relaxed);
			std::cout << "x.store(2, memory_order_relaxed)\n";
		};
		auto fun2 = [&]()
		{
			y = x.load(memory_order_relaxed);
			std::cout << "y = x.load(memory_order_relaxed);\n";
			z = x.load(memory_order_relaxed);
			std::cout << "z = x.load(memory_order_relaxed);";

			assert(y <= z);
		};
		std::thread thread1{ fun1 }, thread2(fun2);
		thread1.join();
		thread2.join();

	}


	//The first model is ¡°sequentially consistent¡±. This is the default mode used 
	//when none is specified, and it is the most restrictive. It can also be explicitly
	//specified via std::memory_order_seq_cst. It provides the same restrictions and 
	//limitation to moving loads around that sequential programmers are inherently 
	//familiar with, except it applies across threads.

	{
		std::atomic<int>x = 0;
		std::atomic<int>y = 0;
		std::atomic<int>b = 1;
		//Although x and y are unrelated variables, the memory model 
		//specifies that the assert cannot fail. The store to 'y' happens-before 
		//the store to x in thread 1. If the load of 'x' in thread 2 gets the results
		//of the store that happened in thread 1, it must all see all operations that 
		//happened before the store in thread 1, even unrelated ones. That means the 
		//optimizer is not free to reorder the two stores in thread 1 since thread 2 
		//must see the store to Y as well.
		auto fun1 = [&]()
		{
			y = 1;
			x.store(2);
		};
		auto fun2 = [&]()
		{
			if (x.load() == 2)
				assert(y == 1);
		};
		std::thread thread1{ fun1 }, thread2(fun2);
		thread1.join();
		thread2.join();
	}

	//The third mode is a hybrid between the other two. The acquire/release mode 
	//is similar to the sequentially consistent mode, except it only applies a
	//happens-before relationship to dependent variables. This allows for a relaxing
	//of the synchronization required between independent reads of independent writes.
	{
		std::atomic<int>x = 0;
		std::atomic<int>y = 0;

		auto fun1 = [&]()
		{
			y = 1;
			x.store(2);
		};
		auto fun2 = [&]()
		{
			if (x.load() == 2)
				assert(y == 1);
		};
		std::thread thread1{ fun1 }, thread2(fun2);
		thread1.join();
		thread2.join();
	}

	//The third mode is a hybrid between the other two. The acquire/release mode 
	//is similar to the sequentially consistent mode, except it only applies a 
	//happens-before relationship to dependent variables. This allows for a relaxing 
	//of the synchronization required between independent reads of independent writes.
	return 0;
}


struct Foo
{
	int   i;
	float f;
	char  c;
};

// Note: `alignas(alignof(long double))` below can be simplified to simply 
// `alignas(long double)` if desired.
struct alignas(alignof(long double)) Foo2
{
	// put your definition here
};

struct Empty {};
class EmptyClass
{};

struct alignas(64) Empty64 {};

int testAligned1()
{
	std::cout << "Alignment of"  "\n"
		"- char            : " << alignof(char) << "\n"
		"- pointer         : " << alignof(int*) << "\n"
		"- class Foo       : " << alignof(Foo) << "\n"
		"- class Foo2      : " << alignof(Foo2) << "\n"
		"- empty class     : " << alignof(Empty) << "\n"
		"- empty EmptyClass     : " << alignof(EmptyClass) << "\n"
		"- empty class\n"
		"  with alignas(64): " << alignof(Empty64) << "\n";


	int d = alignof(int);//4
	int c2 = alignof(double);//8
	int c3 = alignof(double*);//8
	int cc4 = alignof(void*);//8

	return 0;
}



int main()
{
	//start();
	//testVector();
	//FPExceptionEnabler enable;
	//TryDivByZero();

	testAligned1();
	testStringStream();
	testSizeofString();
	//testForwardList();
	testAutomic();
	system("Pause");
	return 0;
}