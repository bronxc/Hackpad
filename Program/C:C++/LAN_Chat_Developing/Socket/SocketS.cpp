#include <stdio.h>
#include <Winsock2.h>
#include <windows.h>
#pragma comment(lib,"ws2_32.lib")

SOCKET sockConn;

DWORD WINAPI Fun(LPVOID lpParamter)
{
	while(true)
	{
		char recvBuf[100];
		recv(sockConn, recvBuf, 100, 0);
		printf("Client Says: %s\n",recvBuf);
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
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);	
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);

	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)); 
	listen(sockSrv, 10);
	SOCKADDR_IN  addrClient;
	int len = sizeof(SOCKADDR);

	while(true)
	{
		sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);	
		char sendBuf[100];
		sprintf(sendBuf, "Welcome %s to the server program~ \nNow, let's start talking...\n", inet_ntoa(addrClient.sin_addr));
		send(sockConn, sendBuf, strlen(sendBuf)+1, 0);
		char recvBuf[100];
		recv(sockConn, recvBuf, 100, 0);
		printf("%s\n", recvBuf);
		const char * sockConnName = "Client";
		HANDLE handle = CreateThread(NULL,0,Fun,NULL,0,NULL);
		CloseHandle(handle);
		while(true)
		{
			char talk[100];
			printf("Please enter what you want to say next:");
			gets(talk);
			send(sockConn, talk, strlen(talk)+1, 0);
			printf("\n");
		}		
		closesocket(sockConn);
	}
	printf("\n");
	system("pause");
	return 0;
}


