#include <Winsock2.h> 
#include <stdio.h>  
 #define INVALID_VALUE32 0xFFFF 
 #pragma comment(lib, "ws2_32.lib") 
 
  //�ͻ�����������ʼ 
int main() 
  {  
  int err = INVALID_VALUE32;  
  WORD ver; 
   WSADATA wsaData;  
    //����汾�� 
	 ver = MAKEWORD(2, 2);   /* �汾��Ϊ2.2�汾,1.1Ҳ���� */     
	   /* ��������ʼ�� */  
	   err = WSAStartup(ver, &wsaData); 
	    if (err != 0)    /* ���socket�Ƿ��ʼ���ɹ� */ 
		 {  
		  return 0; 
		   }  
		   if (2 != (LOBYTE(wsaData.wVersion)) || (2 != HIBYTE(wsaData.wVersion)))
		     {    WSACleanup();    /* �汾��������������DLL */    
			 return 0; 
			  }   /* ��ʼsocket�����岿��:����socket */     
			   SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, 0); /* AF_INET��ʾ����ʹ�õķ�Χinternetwork: UDP, TCP, etc,      */       
			   SOCKADDR_IN addrSrv; 
			    addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); 
				// ��������Ϊ��������IP��ַ,���������Լ��Ļ�������д��,����д�ػ���ַ��  
				addrSrv.sin_family           = AF_INET;  
				addrSrv.sin_port             = htons(7861);
				 /* �˿����ֻҪ����ϵͳ��ͻ���� */ 
				  /* ���弸��������,Ҳ�ǽ��ܺͷ��͵�,���ó�100���� */  
				  char recvbuf[100]; 
				   char sendbuf[100];  
				    int len=sizeof(SOCKADDR);     
				printf("\n************��ӭʹ�ñ����*******\n");   
 /* ���������ѭ�� */  
 while (1)  { 
   printf("\n����������:\n"); 
     gets(sendbuf);   
	  sendto(sockClient, sendbuf, strlen(sendbuf)+1, 0, (SOCKADDR *)&addrSrv, len);  
	   recvfrom(sockClient, recvbuf, 100, 0, (SOCKADDR *)&addrSrv, &len); 
	     if ('q' == recvbuf[0])  
		  {    
		  sendto(sockClient, "q", strlen("q")+1, 0, (SOCKADDR *)&addrSrv, len); 
		     printf("The chat is end!\n"); 
			    break; 
				  }     
				  /* �����յ������ݴ������ݻ��������Ա���ʾ */   
				   printf("%s say: %s", inet_ntoa(addrSrv.sin_addr), recvbuf);   
				      }    /* ���socket��� */ 
					   closesocket(sockClient);  
					    WSACleanup();  
						 return 0; 
						  }
