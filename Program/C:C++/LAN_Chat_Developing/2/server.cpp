#include <Winsock2.h> 
#include <stdio.h>   
#define INVALID_VALUE32 0xFFFF 
#pragma comment(lib, "ws2_32.lib")   
int main() 
{  int err = INVALID_VALUE32; 
 WORD ver;
   WSADATA wsaData;    //����汾��  ver = MAKEWORD(2, 2);   
   /* �汾��Ϊ2.2�汾,1.1Ҳ���� */     
     /* ��������ʼ�� */  
	 err = WSAStartup(ver, &wsaData);  
	 if (err != 0)    
	 /* ���socket�Ƿ��ʼ���ɹ� */  
	 {   
	 return 0;  
	 }  
	 if ((LOBYTE(wsaData.wVersion) != 2) || (HIBYTE(wsaData.wVersion) != 2))
	   {    
	   WSACleanup();    /* �汾��������������DLL */    
	   return 0;  
	   }   /* ��ʼsocket�����岿��:����socket */      
	   SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0); /* AF_INET��ʾ����ʹ�õķ�Χinternetwork: UDP, TCP, etc,                                                        SOCK_STREAM��ʾʹ�õ���TCP                                                        SOCK_DGRAM ��ʾʹ�õ���UDP���� */  SOCKADDR_IN addrSrv;  addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);  addrSrv.sin_family           = AF_INET;  addrSrv.sin_port             = htons(7861); /* �˿����ֻҪ����ϵͳ��ͻ���� */   /* ���濪ʼ��bind���� */  bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)); //�󶨶˿� sockSrvҪǿ��ת����SOCKADDR   
 
 /* ���弸��������,Ҳ�ǽ��ܺͷ��͵�,���ó�100���� */  
 char recvbuf[100]; 
  char sendbuf[100];
    char tmpbuf[100];   
	SOCKADDR_IN addrClient;// �����ϵĿͻ���ip��ַ 
	 int len = sizeof(SOCKADDR);   
	   printf("\n************��ӭʹ�ñ����*******\n");   /* ���������ѭ�� */ 
	    while (1)  {  
		 recvfrom(sockSrv, recvbuf, 100, 0, (SOCKADDR *)&addrClient, &len); 
		      if ('q' == recvbuf[0])  
			   {    
			   sendto(sockSrv, "q", strlen("q")+1, 0, (SOCKADDR *)&addrClient, len);
			       printf("The chat is end!\n"); 
				      break;  
					   }    /* �����յ������ݴ������ݻ��������Ա���ʾ */  
					    sprintf(tmpbuf,"%s say: %s ",inet_ntoa(addrClient.sin_addr), recvbuf);  
						 printf("%s\n", tmpbuf);       
						   printf("prease input:\n");  
						    gets(sendbuf);   
							sendto(sockSrv, sendbuf, strlen(sendbuf)+1, 0, (SOCKADDR *)&addrClient, len);
							   }   /* ���socket��� */ 
							    closesocket(sockSrv);  
								 WSACleanup(); 
								   return 0; 
								   } 
