#include <stdio.h>
#include <Winsock2.h>
#include <windows.h>
#pragma comment(lib,"ws2_32.lib")

SOCKET sockClient;

DWORD WINAPI Fun(LPVOID lpParamter)
{
	while(true)
	{
		char recvBuf[100];
		recv(sockClient, recvBuf, 100, 0);
		printf("%s Says: %s\n", "Server", recvBuf);
	}
}

int main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;	 
	wVersionRequested = MAKEWORD(2,2); 
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) 
	{
		return -1;
	}
	if ( LOBYTE( wsaData.wVersion ) != 2 ||	HIBYTE( wsaData.wVersion ) != 2 ) 
	{
		WSACleanup();
		return -1; 
	}
	sockClient = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	char recvBuf[100];
	recv(sockClient, recvBuf, 100, 0);
	printf("%s\n", recvBuf);
	send(sockClient, "Attention: A Client has enter...\n", strlen("Attention: A Client has enter...\n")+1, 0);
	HANDLE handle = CreateThread(NULL,0,Fun,NULL,0,NULL);
	CloseHandle(handle);
	while(true)
	{
		char talk[100];
		printf("\nPlease enter what you want to say next:");
		gets(talk);
		send(sockClient, talk, strlen(talk)+1, 0);
	}
	closesocket(sockClient);
	WSACleanup();
	printf("\n");
	system("pause");
	return 0;
}

