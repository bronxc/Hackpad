/**
 * @Description: HTTP server. thread pool implement.
 * @Environment: compile with gcc, running at linux.
 * @Author: xx
 * @Version: 1.0
 * @Time: 2017.5.7
 */

#include "rocket.h"
#include "rocketThread.h"
#include "rocketSocket.h"

/***************************************************************************
 * @Description: create threadpool object
 * @Function: threadpool* threadpoolCreate(int minThreadNum, int maxThreadNum, int queueMaxSize)
 * @Parameter: int minThreadNum
 * @Parameter: int maxThreadNum
 * @Parameter: int queueMaxSize
 * @Return: a newly created threadpool or NULL
****************************************************************************/
Threadpool* threadpoolCreate(int minThreadNum, int maxThreadNum, int queueMaxSize) {
	Threadpool* pool = NULL;
	int i = 0;
	
	//do while(0), single exit
	do {
		if((pool = (Threadpool*)malloc(sizeof(Threadpool))) == NULL) {
			//DEBUG
			//printf("malloc threadpool fail\n");
			break;
		}
		//init
		pool->minThreadNum = minThreadNum;
		pool->maxThreadNum = maxThreadNum;
		pool->liveThreadNum = minThreadNum;
		pool->busyThreadNum = 0;
		pool->waitExitThreadNum = 0;

		pool->queueFront = 0;
		pool->queueRear = 0;
		pool->queueSize = 0;
		pool->queueMaxSize = queueMaxSize;

		pool->shutdown = FALSE;

		if(pthread_mutex_init(&(pool->lock), NULL) != 0 
			|| pthread_mutex_init(&(pool->threadCounter), NULL) != 0
			|| pthread_cond_init(&(pool->queueNotFull), NULL) != 0
			|| pthread_cond_init(&(pool->queueNotEmpty), NULL) != 0) {
			//DEBUG
			//printf("init the lock or cond fail\n");
			break;
		}

		//accord to maxThreadNum, distribution space for pool->threads
		pool->threads = (pthread_t*)malloc(sizeof(pthread_t)*maxThreadNum);
		if(pool->threads == NULL) {
			//DEBUG
			//printf("malloc pool->threads fail\n");
			break;
		}
		//init 0
		memset(pool->threads, 0, sizeof(pthread_t)*maxThreadNum);

		//distribution space for taskQueue
		pool->taskQueue = (ThreadpoolTask*)malloc(sizeof(ThreadpoolTask)*queueMaxSize);
		if(pool->taskQueue == NULL) {
			//DEBUG
			//printf("malloc pool->taskQueue fail\n");
			break;
		}

		//start minThreadNum work thread
		for(i = 0; i < minThreadNum; i++) {
			pthread_create(&(pool->threads[i]), NULL, threadpoolThread, (void*)pool);
			//DEBUG
			//printf("start thread 0x%x...\n", (unsigned int)pool->threads[i]);
		}
		//start manage thread
		pthread_create(&(pool->manageTid), NULL, threadpoolManage, (void*)pool);

		return pool;
	}while(0);

	threadpoolFree(pool);		//happen error, free resource
	return NULL;
}

/***************************************************************************
 * @Description: the worker thread
 * @Function: int* threadpoolThread(void* threadpool)
 * @Parameter: void* threadpool
 * @Return: void
****************************************************************************/
void* threadpoolThread(void* threadpool) {
	Threadpool* pool = (Threadpool*)threadpool;
	ThreadpoolTask task;

	while(TRUE) {
		//check whether there are tasks in the taskQueue
		pthread_mutex_lock(&(pool->lock));

		//queueSize == 0, show there are no tasks, and block this thread
		//use while, when second if is false, just need one thread execute pool->waitExitThreadNum--
		while((pool->queueSize == 0) && (!pool->shutdown)) {
			//DEBUG
			//printf("thread 0x%x is waiting\n", (unsigned int)pthread_self());
			pthread_cond_wait(&(pool->queueNotEmpty), &(pool->lock));
			//exit some thread
			if(pool->waitExitThreadNum > 0) {
				pool->waitExitThreadNum--;
				//live thread number must greater than min thread number
				if(pool->liveThreadNum > pool->minThreadNum) {
					//DEBUG
					//printf("thread 0x%x is exiting\n", (unsigned int)pthread_self());
					pool->liveThreadNum--;
					pthread_mutex_unlock(&(pool->lock));
					pthread_exit(NULL);
				}
			}
		}

		//if pool->shutdown == TRUE, exit each thread
		if(pool->shutdown) {
			pthread_mutex_unlock(&(pool->lock));
			//DEBUG
			//printf("thread 0x%x is exiting\n", (unsigned int)pthread_self());
			pthread_exit(NULL);
		}

		//get task from taskQueue
		task.function = pool->taskQueue[pool->queueFront].function;
		task.arg = pool->taskQueue[pool->queueFront].arg;
		pool->queueFront = (pool->queueFront + 1) % pool->queueMaxSize;
		pool->queueSize--;

		//notice new task can join
		pthread_cond_broadcast(&(pool->queueNotFull));
		//release threadpool lock
		pthread_mutex_unlock(&(pool->lock));

		//execute task
		//DEBUG
		//printf("thread 0x%x is working\n", (unsigned int)pthread_self());
		pthread_mutex_lock(&(pool->threadCounter));
		pool->busyThreadNum++;
		pthread_mutex_unlock(&(pool->threadCounter));
		//
		((*task.function))(task.arg);

		//finish task
		//DEBUG
		//printf("thread 0x%x end working\n", (unsigned int)pthread_self());
		pthread_mutex_lock(&(pool->threadCounter));
		pool->busyThreadNum--;
		pthread_mutex_unlock(&(pool->threadCounter));
	}

	return 0;
}

/***************************************************************************
 * @Description: add task into threadpool
 * @Function: int threadpoolAdd(Threadpool* pool, void*(*function)(void* arg), void* arg)
 * @Parameter: Threadpool* threadpool
 * @Parameter: void* (*function)(void* arg)
 * @Parameter: void* arg
 * @Return: int
****************************************************************************/
int threadpoolAdd(Threadpool* pool, void* (*function)(void* arg), void* arg) {
	pthread_mutex_lock(&(pool->lock));

	//if taskQueue is full, block
	while((pool->queueSize == pool->queueMaxSize) && (!pool->shutdown)) {
		pthread_cond_wait(&(pool->queueNotFull), &(pool->lock));
	}
	if(pool->shutdown) {
		pthread_mutex_unlock(&(pool->lock));
		return 0;
	}
	//add task into taskQueue
	pool->taskQueue[pool->queueRear].function = function;
	pool->taskQueue[pool->queueRear].arg = arg;
	pool->queueRear = (pool->queueRear + 1) % pool->queueMaxSize;
	pool->queueSize++;

	//after add task, awaken waiting thread
	pthread_cond_signal(&(pool->queueNotEmpty));
	pthread_mutex_unlock(&(pool->lock));

	return 0;
}

/***************************************************************************
 * @Description: threadpool manager
 * @Function: int* threadpoolManage(void* threadpool)
 * @Parameter: void* threadpool
 * @Return: void
****************************************************************************/
void* threadpoolManage(void* threadpool) {
	Threadpool* pool = (Threadpool*)threadpool;

	while(!pool->shutdown) {
		//time interval, execute manage
		sleep(DEFAULT_TIME);

		//get some value
		pthread_mutex_lock(&(pool->lock));
		int queueSize = pool->queueSize;
		int liveThreadNum = pool->liveThreadNum;
		pthread_mutex_unlock(&(pool->lock));

		pthread_mutex_lock(&(pool->threadCounter));
		int busyThreadNum = pool->busyThreadNum;
		pthread_mutex_unlock(&(pool->threadCounter));

		int i = 0;
		//create new thread
		//when number of task greater than number of live thread, and number of live thread less than number of max thread
		if(queueSize > liveThreadNum && liveThreadNum < pool->maxThreadNum) {
			pthread_mutex_lock(&(pool->lock));
			int add = 0;
			//each add DEFAULT_THREAD thread
			for(i = 0; add < DEFAULT_THREAD_VARY
				&& pool->liveThreadNum < pool->maxThreadNum
				&& i < pool->maxThreadNum; i++) {
				if(pool->threads[i] == 0 || !threadIsAlive(pool->threads[i])) {
					pthread_create(&(pool->threads[i]), NULL, threadpoolThread, (void*)pool);
					add++;
					pool->liveThreadNum++;
				}
			}

			pthread_mutex_unlock(&(pool->lock));
		}

		//destroy thread
		//when busyThreadNum*2 less than liveThreadNum, and liveThreadNum greater than minThreadNum
		if((busyThreadNum*2) < liveThreadNum && liveThreadNum > pool->minThreadNum) {
			//each destroy DEFAULT_THREAD_VARY thread
			pthread_mutex_lock(&(pool->lock));
			pool->waitExitThreadNum = DEFAULT_THREAD_VARY;
			pthread_mutex_unlock(&(pool->lock));
			//random
			for(i = 0; i < DEFAULT_THREAD_VARY; i++) {
				//notify thread that is not busy
				pthread_cond_signal(&(pool->queueNotEmpty));
			}
		}
	}

	return 0;
}

/***************************************************************************
 * @Description: judge thread is alive or not
 * @Function: int threadIsAlive(pthread_t tid)
 * @Parameter: pthread_t tid, thread id
 * @Return: int, TRUE show thread is alive.
****************************************************************************/
int threadIsAlive(pthread_t tid) {
	int signal = pthread_kill(tid, 0);		//send 0 singnal, test thread is alive
	if(signal == ESRCH) {
		return FALSE;
	}
	return TRUE;
}

/***************************************************************************
 * @Description: free threadpool resource
 * @Function: int threadpoolFree(Thread* pool)
 * @Parameter: Threadpool* threadpool
 * @Return: int
****************************************************************************/
int threadpoolFree(Threadpool* pool) {
	if(pool == NULL) {
		return -1;
	}
	if(pool->taskQueue != NULL) {
		free(pool->taskQueue);
	}
	if(pool->threads != NULL) {
		free(pool->threads);
		pthread_mutex_lock(&(pool->lock));
		pthread_mutex_destroy(&(pool->lock));
		pthread_mutex_lock(&(pool->threadCounter));
		pthread_mutex_destroy(&(pool->threadCounter));

		pthread_cond_destroy(&(pool->queueNotFull));
		pthread_cond_destroy(&(pool->queueNotEmpty));
	}
	free(pool);
	pool = NULL;

	return 0;
}

/***************************************************************************
 * @Description: destroy threadpool
 * @Function: int threadpoolDestroy(Threadpool* pool)
 * @Parameter: Threadpool* threadpool
 * @Return: int
****************************************************************************/
int threadpoolDestroy(Threadpool* pool) {
	//DEBUG
	//printf("threadpoolDestroy\n");

	int i = 0;
	if(pool == NULL) {
		return -1;
	}
	pool->shutdown = TRUE;

	//destroy manage thread
	pthread_join(pool->manageTid, NULL);

	//notify all thread
	for(i = 0; i < pool->liveThreadNum; i++) {
		pthread_cond_broadcast(&(pool->queueNotEmpty));
	}
	for(i = 0; i < pool->liveThreadNum; i++) {
		pthread_join(pool->threads[i], NULL);
	}
	threadpoolFree(pool);

	return 0;
}
