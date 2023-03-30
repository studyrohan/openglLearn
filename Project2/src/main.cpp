#include <winsock2.h>
#include <stdio.h>
#include <memory>

class MyClass
{
public:
	MyClass(int _a);
	~MyClass();

private:
	int a;

};

MyClass::MyClass(int _a)
	:a(_a)
{
}

MyClass::~MyClass()
{
}

class B
{
public:
	B();
	~B();

private:
	int c=0;
};

B::B()
{
}

B::~B()
{
}
std::unique_ptr<B> pass_through(std::unique_ptr<B> p)
{
	return p;
}
int  testUniquePtr()
{

	static std::unique_ptr< MyClass> A;
	//std::unique_ptr< MyClass> A1 = std::make_unique<MyClass>(); //error
	std::unique_ptr< B> b;

	std::unique_ptr< B> b1 = std::make_unique<B>();

	b = std::make_unique < B>(*b1.get());
	std::unique_ptr<B>b2 = pass_through(std::move(b1));
	return 0;
}

int main()
{
	// init socket

	return testUniquePtr();
	//std::unique_ptr<B>b2 = pass_through(b1);// complie error;

	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
		return -1;
	if (LOBYTE(wsaData.wVersion)!=2 || HIBYTE(wsaData.wVersion)!=2)
	{
		WSACleanup();
		return 1;

	}
	// create socket for listening
	SOCKET sockSrv = socket(AF_INET,SOCK_STREAM,0);
	if (sockSrv==-1)
	{
		WSACleanup();
		return 1;
	}
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	// bind socket ,listen port 6000
	if (bind(sockSrv,(sockaddr*)&addrSrv,sizeof(SOCKADDR)) == -1)
	{
		closesocket(sockSrv);
		WSACleanup();
		return 1;
	}
	if (listen(sockSrv,15)==-1)
	{
		closesocket(sockSrv);
		WSACleanup();
		return 1;
	}
	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	char msg[] = "hello world";
	while (true)
	{
		//wait client to connect
		SOCKET sockClient = accept(sockSrv, (sockaddr*)&addrClient, &len);
		if (sockClient == -1)
		{
			break;

		}

		// sent msg to client
		send(sockClient, msg, strlen(msg), 0);
		closesocket(sockClient);
	}
	closesocket(sockSrv);
	WSACleanup();
	return 0;
}