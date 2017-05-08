/**
 * @Description: HTTP server. socket implement.
 * @Environment: compile with gcc, running at linux.
 * @Author: xx
 * @Version: 1.0
 * @Time: 2017.5.2
 */

#include "rocket.h"
#include "rocketSocket.h"

/***************************************************************************
 * @Description: This function starts the process of listening for web  connections
 *				 on 80 port.
 * @Function: int startUp()
 * @Return: socket
****************************************************************************/
int startUp() {
	int httpd = -1;
	struct sockaddr_in serverAddr;

	httpd = socket(PF_INET, SOCK_STREAM, 0);
	if(httpd == -1) {
		errorDie("socket fail");
	}

	memset(&(serverAddr), 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	int on = 1;
	if(setsockopt(httpd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
		errorDie("setsockopt fail");
	}

	if(bind(httpd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
		errorDie("bind fail");
	}

	if(listen(httpd, 5) == -1) {
		errorDie("listen fail");
	}
	
	return httpd;
}

/***************************************************************************
 * @Description: when new client accept, execute this function to handle.
 * @Function: void* acceptRequest(void* sock)
 * @Parameter: void* sock, client socket description.
 * @Return: int
****************************************************************************/
void* acceptRequest(void* sock) {
	int client = *(int*)sock;
	RequestHeader* header = (RequestHeader*)malloc(sizeof(RequestHeader));
	ResponseHeader* response = (ResponseHeader*)malloc(sizeof(ResponseHeader));

	//get request header
	setRequestHeader(client, header);

	//set common informations
	sprintf(response->version, "HTTP/1.0 ");
	sprintf(response->server, SERVER_STRING);

	//produce cookie
	if(strlen(header->cookie) == 0) {
		calcCookie(response->cookie);
	}

	//write log
	writeLog(client, header);

	//only support method 'GET' and 'POST'
	if((strcasecmp(header->method, "GET") != 0) && (strcasecmp(header->method, "POST") != 0)) {
		unImplemented(client, response);
	}
	//judge file exist
	else if(header->execute == -1) {
		fileNotFound(client, response);
	}
	//static html
	else if(header->execute == 0) {
		readServerFile(client, header->path, response);
	}
	else if(header->execute == 1) {
		executeCGI(client, header, response);
	}
	else {
		printf("error\n");
		exit(-1);
	}

	free(header);
	free(response);
	header = NULL;
	response = NULL;

	return 0;
}

/***************************************************************************
 * @Description: get request header infomations, and set. this process just
 *				 support parameter of header inlcude: Host, Cookie.
 * @Function: RequestHeader setRequestHeader(int sock)
 * @Parameter: int sock, client socket description.
 * @Return: RequestHeader, header that is set.
****************************************************************************/
int setRequestHeader(int client, RequestHeader* header) {
	char buf[BUF_SIZE];
	int i = 0;
	int j = 0;
	int len = 0;
	struct stat st;		//file description struct

	//init header value
	header->cookie[0] = '\0';			//init
	header->param[0] = '\0';			//init '\0'
	header->execute = 0;

	//eg: GET /index.html HTTP/1.0
	len = getLine(client, buf, BUF_SIZE);
	while(!isSpace(buf[i])) {		//method
		header->method[i] = buf[i];
		i += 1;
	}
	header->method[i] = '\0';

	sprintf(header->path, SERVER_PATH);		//header->path = "www"
	i += 1;
	j = strlen(SERVER_PATH);
	while(!isSpace(buf[i]) && buf[i] != '?') {		//path
		header->path[j] = buf[i];
		i += 1;
		j += 1;
	}
	header->path[j] = '\0';
	//if path="www/", modify "www/index.html"
	if(header->path[strlen(header->path)-1] == '/') {
		strcat(header->path, "index.html");
	}

	//method is 'GET', read parameters from url.
	if(strcasecmp(header->method, "GET") == 0 && buf[i] == '?') {
		i += 1;
		j = 0;
		while(!isSpace(buf[i])) {
			header->param[j] = buf[i];
			i += 1;
			j += 1;
		}
		header->param[j] = '\0';
	}
	else {
		while(!isSpace(buf[i])) {
			i += 1;
		}
	}

	i += 1;
	j = 0;
	while(i < len) {			//version
		header->version[j] = buf[i];
		i += 1;
		j += 1;
	}
	header->version[j] = '\0';

	//eg: Host: 127.0.0.1:7777
	len = getLine(client, buf, BUF_SIZE);
	i = 6;			//strlen("Host: ")
	j = 0;
	while(i < len) {
		header->host[j] = buf[i];
		i += 1;
		j += 1;
	}
	header->host[j] = '\0';

	//find Cookie value
	char key[64] = {0};
	while(len != 0) {
		//for don't modify other key-value.
		len = getLine(client, buf, BUF_SIZE);
		i = 0;
		while(buf[i] != ':') {
			key[i] = buf[i];
			i += 1;
		}
		key[i] = '\0';
		if(strcasecmp(key, "Cookie") == 0) {
			j = 0;
			i += 2;			//ingore :<blank>
			while(i < len) {
				header->cookie[j] = buf[i];
				i += 1;
				j += 1;
			}
			header->cookie[j] = '\0';
		}
	}

	//read post parameter
	if(strcasecmp(header->method, "POST") == 0) {
		//read from buffer of recv
		int n = recv(client, buf, BUF_SIZE, 0);
		i = 0;
		while(i < n) {
			header->param[i] = buf[i];
			i += 1;
		}
		header->param[i] = '\0';
	}

	//set execute or not.
	//execute = -1 show file not found,
	//execute = 0 show normal html.
	//execute = 1 show execute.
	if(stat(header->path, &st) == -1) {
		header->execute = -1;
	}
	else {
		//if file is executable, header->execute = 1
		if(st.st_mode & S_IXUSR ||
		   st.st_mode & S_IXGRP ||
		   st.st_mode & S_IXOTH) {
			header->execute = 1;
		   }
	}
	
	return 0;
}

/***************************************************************************
 * @Description: read request header infomations, and split by '\r\n', 
 *				 return each line. but can not read parameter of post method.
 * @Function: int getLine(int sock, char* buf, int size)
 * @Parameter: int client, client socket description.
 * @Parameter: char* buf, buffer.
 * @Parameter: int size, length of buffer.
 * @Return: int, length of characters.
****************************************************************************/
int getLine(int client, char* buf, int size) {
	int i = 0;
	char c = '\0';
	int n = 0;

	while((i < size-1) && (c != '\r')) {
		n = recv(client, &c, 1, 0);
		if(n > 0) {
			buf[i] = c;
			i += 1;
		}
		else {		// n == 0
			c = '\r';
		}
	}
	buf[i-1] = '\0';

	//ignore '\n' at end of line.
	recv(client, &c, 1, 0);

	return i-1;
}

/***************************************************************************
 * @Description: when user first send request, server calculate random cookie,
 *				 and set response.cookie.  the cookie calculate by random + time.
 * @Function: int calcCookie(char* cookie)
 * @Parameter: char* cookie, response.cookie
 * @Return: int
****************************************************************************/
int calcCookie(char* cookie) {
	int buf = 0;

	srand(time(NULL));
	buf = rand();
	sprintf(cookie, "Set-Cookie: Part_Number=%d;\r\n", buf);

	return 0;
}

/***************************************************************************
 * @Description: just implement GET and POST, other method unImplemented.
 * @Function: int unImplemented(int client)
 * @Parameter: int client, client socket description
 * @Parameter: Response* rep, 
 * @Return: int
****************************************************************************/
int unImplemented(int client, ResponseHeader* rep) {
	char buf[1024];

	sprintf(rep->statusCode, "501 ");
	sprintf(rep->statusInfo, "Method Not Implemented\r\n");
	sprintf(rep->contentType, "Content-Type: text/html\r\n");
	sendResponseHeader(client, rep);

	sprintf(buf, "<HTML><HEAD><TITLE>Method Not Implemented\r\n		\
						   </TITLE></HEAD>\r\n									\
						   <BODY><P>HTTP request method not supported.</P>\r\n	\
						   </BODY></HTML>\r\n");
	send(client, buf, strlen(buf), 0);
	close(client);

	return 0;
}

/***************************************************************************
 * @Description: file not found, response not found html.
 * @Function: int fileNotFound(int client)
 * @Parameter: int client, client socket description
 * @Parameter: Response* rep, 
 * @Return: int
****************************************************************************/
int fileNotFound(int client, ResponseHeader* rep) {
	char buf[BUF_SIZE];

	sprintf(rep->statusCode, "404 ");
	sprintf(rep->statusInfo, "Not Found\r\n");
	sprintf(rep->contentType, "Content-Type: text/html\r\n");
	sendResponseHeader(client, rep);

	sprintf(buf, "<HTML><HEAD><TITLE>Not Found\r\n						\
						   </TITLE></HEAD>\r\n							\
						   <BODY><P>The file not found.</P>\r\n			\
						   </BODY></HTML>\r\n");
	send(client, buf, strlen(buf), 0);
	close(client);

	return 0;
}

/***************************************************************************
 * @Description: the HTTP server happen error, response HTTP-internal Server Error.
 * @Function: internalServerError(int client, ResponseHeader* rep)
 * @Parameter: int client, client socket description
 * @Parameter: Response* rep, 
 * @Return: int
****************************************************************************/
int internalServerError(int client, ResponseHeader* rep) {
	char buf[BUF_SIZE];

	sprintf(rep->statusCode, "500 ");
	sprintf(rep->statusInfo, "HTTP-internal Server Error\r\n");
	sprintf(rep->contentType, "Content-Type: text/html\r\n");
	sendResponseHeader(client, rep);

	sprintf(buf, "<HTML><HEAD><TITLE>HTTP-internal Server Error\r\n			\
						   </TITLE></HEAD>\r\n								\
						   <BODY><P>HTTP-internal Server Error.</P>\r\n		\
						   </BODY></HTML>\r\n");
	send(client, buf, strlen(buf), 0);
	close(client);

	return 0;
}

/***************************************************************************
 * @Description: read server file, normal html.
 * @Function: int readServerFile(int client, const char* path)
 * @Parameter: int client, client socket description
 * @Parameter: const char* path, file path
 * @Parameter: Response* rep, 
 * @Return: int
****************************************************************************/
int readServerFile(int client, const char* path, ResponseHeader* rep) {
	FILE* resource = NULL;
	char buf[BUF_SIZE];

	//file is readable or not.
	resource = fopen(path, "r");
	if(resource == NULL) {
		fileNotFound(client, rep);
	}
	else {
		//header
		sprintf(rep->statusCode, "200 ");
		sprintf(rep->statusInfo, "Success\r\n");
		sprintf(rep->contentType, "Content-Type: text/html\r\n");
		sendResponseHeader(client, rep);
		//content
		fgets(buf, sizeof(buf), resource);
		while (!feof(resource)) {
			send(client, buf, strlen(buf), 0);
			fgets(buf, sizeof(buf), resource);
		}

		close(client);
	}

	fclose(resource);
	return 0;
}

/***************************************************************************
 * @Description: execute cgi program, and send response.
 * @Function: int executeCGI(int client, const RequestHeader* header, ResponseHeader* rep)
 * @Parameter: int client, client socket description
 * @Parameter: const RequestHeader* header
 * @Parameter: ResponseHeader* rep
 * @Return: int
****************************************************************************/
int executeCGI(int client, const RequestHeader* header, ResponseHeader* rep) {
	char c = '\0';
	int cgiOutput[2];
	pid_t pid;

	//create pipe
	if(pipe(cgiOutput) < 0) {
		internalServerError(client, rep);
		return -1;
	}

	//fork
	if((pid = fork()) < 0) {
		internalServerError(client, rep);
		return -1;
	}

	if(pid == 0) {	//child process, execute cgi program.
		char methodEnv[ENV_SIZE];
		char queryEnv[ENV_SIZE];
		char contentEnv[ENV_SIZE];

		dup2(cgiOutput[1], STDOUT);
		close(cgiOutput[0]);
		sprintf(methodEnv, "REQUEST_METHOD=%s", header->method);
		putenv(methodEnv);
		//GET
		if(strcasecmp(header->method, "GET") == 0) {
			sprintf(queryEnv, "QUERY_STRING=%s", header->param);
			putenv(queryEnv);
		}
		//POST
		else {
			sprintf(contentEnv, "CONTENT_LENGTH=%s", header->param);
			putenv(contentEnv);
		}
		//execute
		execl(header->path, NULL);
		exit(0);
	}
	else {		//parent process
		//header
		sprintf(rep->statusCode, "200 ");
		sprintf(rep->statusInfo, "Success\r\n");
		sprintf(rep->contentType, "Content-Type: text/html\r\n");
		sendResponseHeader(client, rep);

		//send content from pipe[0]
		close(cgiOutput[1]);
		while(read(cgiOutput[0], &c, 1) > 0) {
			send(client, &c, 1, 0);
		}
		close(client);
	}
	return 0;
}

/***************************************************************************
 * @Description: send response header.
 * @Function: int sendResponseHeader(int client, Response* rep)
 * @Parameter: int client, client socket description
 * @Parameter: ResponseHeader* rep
 * @Return: int
****************************************************************************/
int sendResponseHeader(int client, ResponseHeader* rep) {
	
	send(client, rep->version, strlen(rep->version), 0);
	send(client, rep->statusCode, strlen(rep->statusCode), 0);
	send(client, rep->statusInfo, strlen(rep->statusInfo), 0);
	send(client, rep->server, strlen(rep->server), 0);
	send(client, rep->contentType, strlen(rep->contentType), 0);
	send(client, rep->cookie, strlen(rep->cookie), 0);
	send(client, "\r\n", 2, 0);

	return 0;
}

/***************************************************************************
 * @Description: log module.
 * @Function: int writeLog(int client, const RequestHeader* header)
 * @Parameter: int client, client socket description
 * @Parameter: const RequestHeader* header
 * @Return: int
 *
 * @Suggestions: this function just write some informations about headers, it 
 *				 should write headers, response and some execute infomations.
 *				 define log struct is good idea.
****************************************************************************/
int writeLog(int client, const RequestHeader* header) {
	char buf[BUF_SIZE] = {0};
	FILE* resource = NULL;
	struct sockaddr_in clientAddr;
	socklen_t len = sizeof(clientAddr);
	time_t timeTemp;
	char timeStr[30] = {0};

	//time
	time(&timeTemp);
	strcpy(timeStr, ctime(&timeTemp));
	//delete '\n'
	timeStr[strlen(timeStr)-1] = '\0';

	//ip
	getpeername(client, (struct sockaddr*)&clientAddr, &len);

	//time ip method path version parameters
	sprintf(buf, "%s %s %s %s %s %s\n", timeStr,
								   inet_ntoa(clientAddr.sin_addr),
								   header->method,
								   header->path,
								   header->version,
								   header->param);
	resource = fopen(LOG_PATH, "a");
	if(resource == NULL) {
		exit(-1);
	}
	else {
		fputs(buf, resource);
	}

	fclose(resource);
	return 0;
}

/***************************************************************************
 * @Description: print error information and exit process.
 * @Function: void errorDie(const char* str)
 * @Return: int
****************************************************************************/
int errorDie(const char* str) {
	perror(str);
	exit(1);

	return 0;
}

