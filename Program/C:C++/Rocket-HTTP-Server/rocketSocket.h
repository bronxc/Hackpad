/**
 * @Description: HTTP server. socket head file.
 * @Environment: compile with gcc, running at linux.
 * @Author: xx
 * @Version: 1.0
 * @Time: 2017.5.2
 */

#ifndef ROCKETSOCKET
#define ROCKETSOCKET

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <sys/stat.h>

#define SERVER_STRING "Server: RocketHTTPServer 1.0\r\n"
#define SERVER_PATH "www"
#define LOG_PATH "logs/log"
#define PORT 7777
#define BUF_SIZE 1024
#define ENV_SIZE 255
#define STDIN   0
#define STDOUT  1
#define STDERR  2

#define isSpace(x) isspace((int)(x))

/**
 * @Description: the data struct, description request header informaiton.
 *				 just support host, cookie key-value.
 */
typedef struct {
	char method[10];
	char path[64];
	char version[10];
	char host[22];
	char cookie[1024];		//for key-value, it can optimize hashmap.
	char param[1024];
	int execute;
}RequestHeader;

/**
 * @Description: the data struct, description response header informaiton.
 */
typedef struct {
	char version[10];
	char statusCode[10];
	char statusInfo[32];
	char server[32];
	char contentType[32];
	char cookie[1024];
}ResponseHeader;

int startUp();
void* acceptRequest(void* sock);
int getLine(int client, char* buf, int size);
int setRequestHeader(int client, RequestHeader* header);
int calcCookie(char* cookie);
int unImplemented(int client, ResponseHeader* rep);
int fileNotFound(int client, ResponseHeader* rep);
int internalServerError(int client, ResponseHeader* rep);
int readServerFile(int client, const char* path, ResponseHeader* rep);
int executeCGI(int client, const RequestHeader* header, ResponseHeader* rep);
int sendResponseHeader(int client, ResponseHeader* rep);
int writeLog(int client, const RequestHeader* header);
int errorDie(const char* str);

#endif
