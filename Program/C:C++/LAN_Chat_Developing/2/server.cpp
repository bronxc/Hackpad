#include <Winsock2.h> 
#include <stdio.h>   
#define INVALID_VALUE32 0xFFFF 
#pragma comment(lib, "ws2_32.lib")   
int main() 
{  int err = INVALID_VALUE32; 
 WORD ver;
   WSADATA wsaData;    //定义版本号  ver = MAKEWORD(2, 2);   
   /* 版本号为2.2版本,1.1也可以 */     
     /* 接下来初始化 */  
	 err = WSAStartup(ver, &wsaData);  
	 if (err != 0)    
	 /* 检查socket是否初始化成功 */  
	 {   
	 return 0;  
	 }  
	 if ((LOBYTE(wsaData.wVersion) != 2) || (HIBYTE(wsaData.wVersion) != 2))
	   {    
	   WSACleanup();    /* 版本错误则清楚导入的DLL */    
	   return 0;  
	   }   /* 开始socket的主体部分:创建socket */      
	   SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0); /* AF_INET表示网络使用的范围internetwork: UDP, TCP, etc,                                                        SOCK_STREAM表示使用的是TCP                                                        SOCK_DGRAM 表示使用的是UDP类型 */  SOCKADDR_IN addrSrv;  addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);  addrSrv.sin_family           = AF_INET;  addrSrv.sin_port             = htons(7861); /* 端口随便只要不跟系统冲突就行 */   /* 下面开始绑定bind网卡 */  bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)); //绑定端口 sockSrv要强制转换成SOCKADDR   
 
 /* 定义几个缓冲区,也是接受和发送的,设置成100即可 */  
 char recvbuf[100]; 
  char sendbuf[100];
    char tmpbuf[100];   
	SOCKADDR_IN addrClient;// 连接上的客户端ip地址 
	 int len = sizeof(SOCKADDR);   
	   printf("\n************欢迎使用本软件*******\n");   /* 下面进入死循环 */ 
	    while (1)  {  
		 recvfrom(sockSrv, recvbuf, 100, 0, (SOCKADDR *)&addrClient, &len); 
		      if ('q' == recvbuf[0])  
			   {    
			   sendto(sockSrv, "q", strlen("q")+1, 0, (SOCKADDR *)&addrClient, len);
			       printf("The chat is end!\n"); 
				      break;  
					   }    /* 将接收到的数据存入数据缓冲区，以便显示 */  
					    sprintf(tmpbuf,"%s say: %s ",inet_ntoa(addrClient.sin_addr), recvbuf);  
						 printf("%s\n", tmpbuf);       
						   printf("prease input:\n");  
						    gets(sendbuf);   
							sendto(sockSrv, sendbuf, strlen(sendbuf)+1, 0, (SOCKADDR *)&addrClient, len);
							   }   /* 最后将socket清空 */ 
							    closesocket(sockSrv);  
								 WSACleanup(); 
								   return 0; 
								   } 
