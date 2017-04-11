#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#pragma comment(lib,"ws2_32.lib")

HANDLE handout;
SOCKET sockConn;
int hig = 0;

int Gotoxy(int x,int y);
int SetSize();
int Load();
int ShowConnect(int con);
int ShowChat();
int Chatting();
int Sending();
DWORD WINAPI Fun(LPVOID lpParamter);

int main()
{
	SetSize();
	/*Load();
	Chatting();*/
	return 0;
}

int Gotoxy(int x,int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;	
	handout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handout,coord);
	return 0;
}

int SetSize()
{
	system("mode con cols=75 lines=25");
	return 0;
}

int Load()
{
	handout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handout, 0xF0);
	for(int i = 0;i < 25;i++)
	{
		Gotoxy(24+i,7);
		printf("%2s", "");
	}
	for(int i = 0;i < 4;i++)
	{
		Gotoxy(24,7+i);
		printf("%2s\n", "");
	}
	for(int i = 0;i < 25;i++)
	{
		Gotoxy(24+i,11);
		printf("%2s", "");
	}
	for(int i = 0;i < 4;i++)
	{
		Gotoxy(48,7+i);
		printf("%2s\n", "");
	}
	SetConsoleTextAttribute(handout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	Gotoxy(28,8);
	printf("Waiting for ");
	Gotoxy(35,9);
	printf("Client....");
	Gotoxy(26,12);
	printf("Welcome to Chatting Room");
	Gotoxy(32,13);
	printf("Server Now");
	return 0;
}

int ShowConnect()
{
	system("cls");
	Gotoxy(28,8);
	printf("                   ");
	Gotoxy(35,9);
	printf("           ");
	Gotoxy(27,8);
	printf("Client is ");
	Gotoxy(30,9);
	printf("connecting");
	for(int i = 0;i < 6;i++)
	{
		printf(".");
		Sleep(500);
	}
	ShowChat();
	return 0;
}

int ShowChat()
{
	system("cls");
	handout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handout, 0xF0);
	for(int i = 0;i < 65;i++)
	{
		Gotoxy(6+i,1);
		printf("%2s", "");
	}
	for(int i = 0;i < 22;i++)
	{
		Gotoxy(6,1+i);
		printf("%2s","");
	}
	for(int i = 0;i < 65;i++)
	{
		Gotoxy(6+i,22);
		printf("%2s", "");
	}
	for(int i = 0;i < 22;i++)
	{
		Gotoxy(72,1+i);
		printf("%2s","");
	}
	SetConsoleTextAttribute(handout, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	for(int i = 0;i < 20;i++)
	{
		Gotoxy(55,2+i);
		printf("¡ö");
	}
	for(int i = 0;i < 45;i++)
	{
		Gotoxy(9+i,6);
		printf("--");
	}
	SetConsoleTextAttribute(handout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	Gotoxy(61,3);
	printf("Server");
	Gotoxy(57,5);
	printf("Server IP:");
	Gotoxy(57,6);
	printf("127.0.0.1");
	Gotoxy(57,8);
	printf("Client IP:");
	Gotoxy(57,9);
	printf("127.0.0.1");
	Gotoxy(57,14);
	printf("NOTICE:");
	Gotoxy(57,15);
	printf("1.exit");
	Gotoxy(57,16);
	printf("2.send");
	return 0;
}

int Chatting()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2,2);
	err = WSAStartup( wVersionRequested, &wsaData );
	if(err != 0)
	{
		return -1;
	}
	if ( LOBYTE( wsaData.wVersion ) != 2 ||	HIBYTE( wsaData.wVersion ) != 2 )
	{
		WSACleanup();
		return -1;
	}
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);	
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(7000);
	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)); 
	listen(sockSrv, 2);
	SOCKADDR_IN  addrClient;
	int len = sizeof(SOCKADDR);
	sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);
	ShowConnect();
	char sendBuf[100];
	sprintf(sendBuf, "Welcome To Chatting Room", inet_ntoa(addrClient.sin_addr));
	send(sockConn, sendBuf, strlen(sendBuf)+1, 0);
	char recvBuf[100];
	recv(sockConn, recvBuf, 100, 0);
	Gotoxy(9,7);
	printf("%s\n", recvBuf);
	const char * sockConnName = "Client";
	HANDLE handle = CreateThread(NULL,0,Fun,NULL,0,NULL);
	CloseHandle(handle);
	while(true)
	{
		char talk[100];
		Gotoxy(9,2);
		printf("Please enter say:");
		Gotoxy(9,3);
		gets(talk);
		Gotoxy(9,8+hig);
		printf("I say:");
		puts(talk);
		hig++;
		Gotoxy(9,3);
		for(int i = 0;i < strlen(talk);i++)
		{
			printf(" ");
		}
		send(sockConn, talk, strlen(talk)+1, 0);
		if(strcmp(talk,"exit") == 0)
		{
			Gotoxy(0,23);
			exit(0);
		}
		if(strcmp(talk,"send") == 0)
		{
			Sending();
		}
	}		
	closesocket(sockConn);
	return 0;
}

DWORD WINAPI Fun(LPVOID lpParamter)
{
	while(true)
	{
		char recvBuf[100];
		Gotoxy(9,3);
		recv(sockConn, recvBuf, 100, 0);
		if(strcmp(recvBuf,"exit") == 0)
		{
			Gotoxy(0,23);
			printf("The Client is Offline...\n");
			system("pause");
			exit(0);
		}
		Gotoxy(9,8+hig);
		printf("Client Says: %s\n",recvBuf);
		hig++;
	}
}

int Sending()
{
	Gotoxy(9,8+hig);
	SetConsoleTextAttribute(handout,FOREGROUND_RED);
	printf("Error:I am sorry");
	hig++;
	Gotoxy(9,8+hig);
	printf("The function is maintained");
	hig++;
	SetConsoleTextAttribute(handout, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	return 0;
}








