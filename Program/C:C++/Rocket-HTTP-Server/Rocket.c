/**
 * @Description: HTTP server.
 * @Environment: compile with gcc, running at linux.
 * @Author: xx
 * @Version: 1.0
 * @Time: 2017.5.2
 */

#include "rocket.h"
#include "rocketThread.h"
#include "rocketSocket.h"

//threadpool DEBUG
/*
void* process(void *arg) {
    printf("thread 0x%x working on task %d\n ",(unsigned int)pthread_self(),*(int *)arg);
    sleep(3);
    printf("task %d is end\n",*(int *)arg);

	return 0;
}
*/

/***************************************************************************
 * @Description: main function
 * @Function: int main(int argc, char* argv[])
 * @Parameter: int argc
 * @Parameter: char* argv[]
 * @Return: 0
****************************************************************************/
int main(int argc, char* argv[]) {
	int httpd = -1;
	int client = -1;
	struct sockaddr_in clientAddr;
	socklen_t clientAddrLen = sizeof(clientAddr);

	Threadpool* pool = threadpoolCreate(3, 100, 100);
	printf("init finish...\n");

	httpd = startUp();
	printf("httpd running on port %d\n", PORT);

	while(TRUE) {
		client = accept(httpd, (struct sockaddr*)&clientAddr, &clientAddrLen);
		if(client == -1) {
			errorDie("accept fail");
		}
		threadpoolAdd(pool, acceptRequest, (void*)&client);
	}
	threadpoolDestroy(pool);

	/*threadpool DEBUG
	Threadpool* pool = threadpoolCreate(3, 100, 100);
	printf("pool init\n");

	int num[7];
	int i = 0;
	for(i = 0; i < 7; i++) {
		num[i] = i;
		printf("add task %d\n", i);
		threadpoolAdd(pool, process, (void*)&num[i]);
	}

	sleep(25);
	threadpoolDestroy(pool);
	*/

	return 0;
}
