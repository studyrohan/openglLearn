#include <winsock2.h>
#include <stdio.h>
int main()
{
	// init socket
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