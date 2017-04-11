#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include<Windows.h>

long filesize(char filename[])//计算文件大小
{
	long size=0;
	FILE *fp;
	if((fp=fopen(filename,"rb"))==NULL)
	{
		printf("打开失败");
		exit(1);
	}
	fseek(fp,0,SEEK_END);
	size=ftell(fp);
	fclose(fp);
	return size;
}

int main()//发送文件
{
	int ret=0;
	WSADATA WD;
	SOCKET client;
	SOCKADDR_IN serveraddr;
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
	client=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	serveraddr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3333);
	int len;
	len=sizeof(serveraddr);
	
	//socket设置
	long sum=0,size=0,size_once=0;
	float BL=0;
	char sendBuf[500]="\0";
	char filename[100];
	printf("请输入文件名：                 （例如：C:\\User\\Administrator\\Desktop\\123.txt）\n");
	scanf("%s",filename);
	size=filesize(filename);
	printf("\n字节数为%ld\n",size);
	FILE *file;
	if((file=fopen(filename,"rb"))==NULL)
	{
		printf("打开失败\n");
		printf("请重新输入：sendfile\n");
		return 0;
	}
	else
	{
		sendto(client,filename,100,0,(struct sockaddr*)&serveraddr,len);
		sprintf(sendBuf,"%ld",size);
		sendto(client,sendBuf,500,0,(struct sockaddr*)&serveraddr,len);
		ZeroMemory(sendBuf,500);
		while(size!=sum)
		{
			size_once=fread(sendBuf,500,1,file);
			printf("读取段数%ld",size_once);
			sendto(client,sendBuf,500,0,(struct sockaddr*)&serveraddr,len);
			sum=ftell(file);
			BL=(float)sum/(float)size;
			printf("已发送%d%% \n",(int)(BL*100));
			ZeroMemory(sendBuf,500);
		}
		printf("发送完毕\n");
		fclose(file);
	}
	closesocket(client);
	WSACleanup();
	return 0;
}
