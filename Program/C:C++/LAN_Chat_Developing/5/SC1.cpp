#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#pragma comment(lib,"ws2_32.lib")

HANDLE handout;
SOCKET sockClient;

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
	addrSrv.sin_port = htons(7000);
	connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	
	long size_once = 0;
	long size = 0;
	long  sum = 0;
	char recvBuf[100];
	FILE *fp;
	fp =fopen("E:\\1.txt","wb");
	recv(sockClient, recvBuf, 100, 0);
	size = atoi(recvBuf);
	printf("%ld\n",size);
	while(size != sum)
	{
		char recvBuf[100];
		recv(sockClient,recvBuf,100,0);
		puts(recvBuf);
		fwrite(recvBuf,strlen(recvBuf),1,fp);
		sum = ftell(fp);
		fflush(fp);	
	}
	fclose(fp);	
	closesocket(sockClient);
	WSACleanup();
	return 0;
}
