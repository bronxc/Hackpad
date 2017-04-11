#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#pragma comment(lib,"ws2_32.lib")

HANDLE handout;
SOCKET sockConn;

int main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2,2);
	err = WSAStartup( wVersionRequested, &wsaData );
	if(err != 0)
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
	addrSrv.sin_port = htons(7000);
	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)); 
	listen(sockSrv, 2);
	SOCKADDR_IN  addrClient;
	int len = sizeof(SOCKADDR);
	sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);
	
	long size_once = 0;
	long size = 0;
	long  sum = 0;
	char sendBuf[100];
	FILE *fp;
	fp =fopen("D:\\1.txt","rb");
	size = fseek(fp,0,SEEK_END);
	size=ftell(fp);
	printf("%ld\n",size);
	sprintf(sendBuf,"%ld\n",size);
	send(sockConn,sendBuf,100,0);
	
		fseek(fp,0,SEEK_SET);
		
		while(size!=sum)
		{
			char talk[100];
			fread(talk,100,1,fp);
			puts(talk);
			send(sockConn,talk,100,0);
			sum=ftell(fp);
		}
		printf("·¢ËÍÍê±Ï\n");
	fclose(fp);
	closesocket(sockConn);
	system("pause");
	return 0;
}
