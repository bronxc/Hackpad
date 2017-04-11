/*Client：*/
 
#include <winsock2.H>
#pragma comment(lib, "Ws2_32.lib")
#include <stdio.h>
#include <string.h>
 
int main()
{   
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
     
    wVersionRequested = MAKEWORD( 2, 2 );
     
    err = WSAStartup( wVersionRequested, &wsaData );
    if ( err != 0 ) {
         
        return 0;
    }
     
     
    if ( LOBYTE( wsaData.wVersion ) != 2 ||
        HIBYTE( wsaData.wVersion ) != 2 ) 
    {
         
        WSACleanup( );
        return 0; 
    }
    SOCKET socketClient = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN addrSrv;
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(6000);
    addrSrv.sin_addr.S_un.S_addr = inet_addr("192.168.1.101");//服务器端的IP地址
     
    connect(socketClient, (SOCKADDR *)&addrSrv, sizeof(SOCKADDR));
    char recvBuf[256];
    char sendBuf[] = "This is Joychou";
    recv(socketClient, recvBuf, 256, 0);
    printf("%s\n", recvBuf);
    send(socketClient, sendBuf, strlen(sendBuf) + 1, 0);
    closesocket(socketClient);
    WSACleanup();
     
}
