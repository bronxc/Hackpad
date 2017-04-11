//·þÎñÆ÷£º
#include<stdio.h>
#include<string.h>
#include<Winsock2.h>
#include<Windows.h> 
#pragma comment(lib,"ws2_32.lib")
#define MAX_BUF 65536
int main()
{
	WSAData wsaData;
	int err=WSAStartup(WINSOCK_VERSION,&wsaData);
	if(0!=err)
	{
		return -1;
	}
	SOCKET sock;
	sock=socket(AF_INET,SOCK_DGRAM,0);
	if(INVALID_SOCKET==sock)
	{
		printf("socket()Failed:%d\n",WSAGetLastError());
		WSACleanup();
		return -1;
	}
	
	sockaddr_in LocalAddr;
	LocalAddr.sin_family=AF_INET;
	LocalAddr.sin_port=htons(20000);
	LocalAddr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	err=bind(sock,(sockaddr*)&LocalAddr,sizeof(LocalAddr));
	if(SOCKET_ERROR==err)
	{
		printf("bind()Failed:%d\n",WSAGetLastError());
		closesocket(sock);
		WSACleanup();
		return -1;
	}
	
	char rbuf[MAX_BUF];
	memset(rbuf,0,MAX_BUF);
	sockaddr_in RemoteAddr;
	
	int RemoteLen = sizeof(RemoteAddr);

	while(1)
	{	
		memset(rbuf,0,1024);
		int rByte=recvfrom(sock,rbuf,1024,0,(sockaddr*)&RemoteAddr,&RemoteLen);
		
		if(SOCKET_ERROR==rByte)
		{
			printf("recvfrom()Failed:%d\n",WSAGetLastError());
			closesocket(sock);
			WSACleanup();
			return -1;
		}

	}

    closesocket(sock);
    WSACleanup();

	system("pause");
    return 0;
}
