#include "stdio.h"
#include <windows.h>

DWORD WINAPI ThreadProc(LPVOID lpParameter);

int main()
{
    int i = 0;
    DWORD test = 0;    ///< 0表示第一个子线程
    HANDLE handle;
    DWORD numThreadId = 0;
    
    for (i = 0; i < 6; ++i)
    {
        ///< 线程创建完毕后立即执行【由第5个参数决定】
        handle = CreateThread(NULL, 0, ThreadProc, (LPVOID)&test, 0, &numThreadId);
        if (handle)
        {
            Sleep(1000);        ///< 为了让test每次是不同的值
            test = numThreadId;    ///< 表示"上一个"子线程线程ID
            printf("thread %lld success start...\n", numThreadId);
            CloseHandle(handle);
        }
    }
    Sleep(1000);
    
    return 0;
}


DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
    if (0 == *((DWORD *)lpParameter))
    {
        printf("currunt thread is run\n");
    }
    else
    {
        printf("forward threadID is %lld\n", *((DWORD *)lpParameter));
    }
    
    return 0;
}
