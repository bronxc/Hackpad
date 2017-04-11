/*��Ϊ����������Ҫ�󶨡�bind�������ص�IP��ַ�Ͻ��м�����listen����������Ļ����Ͽ����ж��������Ҳ���ж��IP��ַ����ʱ����Ҫѡ������ĸ�IP���棬���ָ��ΪINADDR_ANY����ôϵͳ����Ĭ�ϵ���������IP��ַ����
 
��Ϊ�ͻ��ˣ���Ҫ���ӡ�connect����Զ�˵ķ�������Ҳ��Ҫָ��Զ�˷������ģ�ip, port���ԡ�
��Ȼ������������£������ܽ�IP��ַָ��ΪINADDR_ANY��ϵͳ�����ġ�
 
Server��*/
#include <winsock2.h>
#pragma comment(lib, "WS2_32.lib")
#include <stdio.h>

int main() 
{
    WORD wVersionRequested;//�汾��
    WSADATA wsaData;
    int err;
 
    wVersionRequested = MAKEWORD(2, 2);//2.2�汾���׽���
    //�����׽��ֿ�,���ʧ�ܷ���
    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0)
    {
        return 0;
    }
 
    //�жϸߵ��ֽ��ǲ���2,�������2.2�İ汾���˳�
    if (LOBYTE(wsaData.wVersion) != 2 || 
         
        HIBYTE(wsaData.wVersion) != 2)
         
    {
        return 0;
    }
     
         //������ʽ�׽���,����TCP(SOCK_STREAM)
 
         SOCKET socSrv = socket(AF_INET, SOCK_STREAM, 0);
 
         //Socket��ַ�ṹ��Ĵ���
 
         SOCKADDR_IN addrSrv;
 
         addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//ת��Unsigned long��Ϊ�����ֽ����
         addrSrv.sin_family = AF_INET;//ָ����ַ��
         addrSrv.sin_port = htons(6000);
        //ָ���˿ں�,��sin_family������,�����������������ֽ���,�����Ҫת��
 
         //���׽��ְ󶨵�һ���˿ںźͱ��ص�ַ��
         bind(socSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));//������sizeof��strlen����
 
         listen(socSrv, 5);
         
         SOCKADDR_IN addrClient;//�����������տͻ���Socket�Ľṹ��
 
         int len = sizeof(SOCKADDR);//��ʼ������,�������������г�ʼ����sizeof
 
         //ѭ���ȴ����ܿͻ��˷�������
 
         while (1)
         {
                   //�ȴ��ͻ������������������󣬽�����������
 
                   //����һ���µĶ�Ӧ�ڴ˴����ӵ��׽��֣�accept����
                   //��ʱ�����ڴ˷�������
 
                   SOCKET sockConn = accept(socSrv, (SOCKADDR*)&addrClient, &len);
 
                   char sendBuf[100];
 
                   sprintf(sendBuf, "Welcome %s to JoyChou", 
 
                            inet_ntoa(addrClient.sin_addr));//��ʽ�����
 
                   //�÷��ص��׽��ֺͿͻ��˽���ͨ��
 
                   send(sockConn, sendBuf, strlen(sendBuf)+1, 0);//�෢��һ���ֽ�
 
                   //��������
 
                   char recvBuf[100];
 
                   recv(sockConn, recvBuf, 100, 0);
 
                   printf("%s\n", recvBuf);
                   closesocket(sockConn);
 
         }
}
