#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include<Windows.h>

int main()
{
	int ret=0;
	WSADATA WD;
	SOCKET server;
	SOCKADDR_IN fromaddr,serveraddr;
	ret=WSAStartup(MAKEWORD(2,2),&WD);
	if(ret!=0)
	{
		return -1; 
	}
	if(HIBYTE(WD.wVersion)!=2||LOBYTE(WD.wVersion)!=2)
	{
		WSACleanup();
		return -1;
	}
	server=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	serveraddr.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3333);
	ret=bind(server,(SOCKADDR*)&serveraddr,sizeof(SOCKADDR));
	int len;
	len=sizeof(serveraddr);
	HANDLE Mutex=CreateMutex(NULL,TRUE,NULL);
	

	FILE *file;
	long sum=0,size=0,size_once=0;
	float BL=0;
	char recvBuf[500]="\0",filename[100]="\0";
	while(1)
	{
		recvfrom(server,recvBuf,500,0,(struct sockaddr*)&fromaddr,&len);
		strcpy(filename,recvBuf);
		if((file=fopen(filename,"wb"))!=NULL)
		{
			printf("创建成功\n");
			//ReleaseMutex(Mutex);
			fclose(file);
		}
		else
		{
			printf("创建失败\n");
			ZeroMemory(recvBuf,500);
			continue;
		}
		ZeroMemory(recvBuf,500);
		recvfrom(server,recvBuf,500,0,(struct sockaddr*)&fromaddr,&len);
		size=atoi(recvBuf);
		printf("\n字节数为%ld\n",size);
		ZeroMemory(recvBuf,500);
		while(1)
		{
			WaitForSingleObject(Mutex,INFINITE);
			if((file=fopen(filename,"ab"))==NULL)
			{
				printf("追加失败\n");
				exit(1);
			}
			
			recvfrom(server,recvBuf,500,0,(struct sockaddr*)&fromaddr,&len);

			size_once=fwrite(recvBuf,strlen(recvBuf),1,file);
			printf("写入段数%ld",size_once);
			sum=ftell(file);
			fflush(file);
			BL=(float)sum/(float)size;
			if(sum==size)
			{
				printf("已接收%d%%\n",(int)(BL*100));
				printf("接收完毕\n");
				fclose(file);
				ZeroMemory(filename,100);
				ZeroMemory(recvBuf,500);
				break;
			}
			else
			{
				printf("已接收%d%%\n",(int)(BL*100));
				ZeroMemory(recvBuf,500);
				fclose(file);
			}
		}	
	}
	closesocket(server);
	WSACleanup();
	return 0;
}
