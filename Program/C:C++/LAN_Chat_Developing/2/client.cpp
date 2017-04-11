#include <Winsock2.h> 
#include <stdio.h>  
 #define INVALID_VALUE32 0xFFFF 
 #pragma comment(lib, "ws2_32.lib") 
 
  //客户端主函数开始 
int main() 
  {  
  int err = INVALID_VALUE32;  
  WORD ver; 
   WSADATA wsaData;  
    //定义版本号 
	 ver = MAKEWORD(2, 2);   /* 版本号为2.2版本,1.1也可以 */     
	   /* 接下来初始化 */  
	   err = WSAStartup(ver, &wsaData); 
	    if (err != 0)    /* 检查socket是否初始化成功 */ 
		 {  
		  return 0; 
		   }  
		   if (2 != (LOBYTE(wsaData.wVersion)) || (2 != HIBYTE(wsaData.wVersion)))
		     {    WSACleanup();    /* 版本错误则清楚导入的DLL */    
			 return 0; 
			  }   /* 开始socket的主体部分:创建socket */     
			   SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, 0); /* AF_INET表示网络使用的范围internetwork: UDP, TCP, etc,      */       
			   SOCKADDR_IN addrSrv; 
			    addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); 
				// 这里设置为服务器的IP地址,由于我在自己的机器上面写的,所以写回环地址了  
				addrSrv.sin_family           = AF_INET;  
				addrSrv.sin_port             = htons(7861);
				 /* 端口随便只要不跟系统冲突就行 */ 
				  /* 定义几个缓冲区,也是接受和发送的,设置成100即可 */  
				  char recvbuf[100]; 
				   char sendbuf[100];  
				    int len=sizeof(SOCKADDR);     
				printf("\n************欢迎使用本软件*******\n");   
 /* 下面进入死循环 */  
 while (1)  { 
   printf("\n请输入内容:\n"); 
     gets(sendbuf);   
	  sendto(sockClient, sendbuf, strlen(sendbuf)+1, 0, (SOCKADDR *)&addrSrv, len);  
	   recvfrom(sockClient, recvbuf, 100, 0, (SOCKADDR *)&addrSrv, &len); 
	     if ('q' == recvbuf[0])  
		  {    
		  sendto(sockClient, "q", strlen("q")+1, 0, (SOCKADDR *)&addrSrv, len); 
		     printf("The chat is end!\n"); 
			    break; 
				  }     
				  /* 将接收到的数据存入数据缓冲区，以便显示 */   
				   printf("%s say: %s", inet_ntoa(addrSrv.sin_addr), recvbuf);   
				      }    /* 最后将socket清空 */ 
					   closesocket(sockClient);  
					    WSACleanup();  
						 return 0; 
						  }
