/**
 * @Description: HTTP server. thread head file.
 * @Environment: compile with gcc, running at linux.
 * @Author: xx
 * @Version: 1.0
 * @Time: 2017.5.7
 */

#ifndef ROCKETTHREAD
#define ROCKETTHREAD

#include <pthread.h>
#include <errno.h>

#define DEFAULT_TIME 10			//each 10 second check
#define MIN_WAIT_TASK_NUM 10	//if queue_size > MIN_WAIT_TASK_NUM, add new thread into pool
#define DEFAULT_THREAD_VARY 10	//each create or destory number of thread

//description task struct
typedef struct {
	void* (*function)(void*);	//function point, callback function
	void* arg;					//parameters
}ThreadpoolTask;

//description thread pool struct
typedef struct {
	pthread_mutex_t lock;				//threadpool lock
	pthread_mutex_t threadCounter;		//record busy thread counter lock
	pthread_cond_t queueNotFull;		//when task queue is full, block thread that add task
	pthread_cond_t queueNotEmpty;		//when task queue is empty, block thread that wait task

	pthread_t *threads;					//record echo thread's tid
	pthread_t manageTid;				//manage thread's tid
	ThreadpoolTask* taskQueue;			//task queue

	int minThreadNum;					//threadpool min thread number
	int maxThreadNum;					//threadpool max thread number
	int liveThreadNum;					//threadpool live thread number
	int busyThreadNum;					//threadpool busy thread number
	int waitExitThreadNum;				//threadpool need destory thread number

	int queueFront;						//taskQueue front
	int queueRear;						//taskQueue rear
	int queueSize;						//taskQueue task number
	int queueMaxSize;					//taskQueue max task number

	int shutdown;						//show threadpool status, 'FALSE' show destory threadpool
}Threadpool;

Threadpool* threadpoolCreate(int minThreadNum, int maxThreadNum, int queueMaxSize);
void* threadpoolThread(void* threadpool);
int threadpoolAdd(Threadpool* pool, void* (*function)(void* arg), void* arg);
void* threadpoolManage(void* threadpool);
int threadIsAlive(pthread_t tid);
int threadpoolFree(Threadpool* pool);
int threadpoolDestroy(Threadpool* pool);

#endif
