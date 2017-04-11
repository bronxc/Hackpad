#include <stdio.h>
#include <windows.h>

DWORD WINAPI Fun(LPVOID lpParamter)
{
	while(1)
	{
		printf("Hello,");
		Sleep(1000);
	}
}

int main()
{
	HANDLE handle = CreateThread(NULL,0,Fun,NULL,0,NULL);
	CloseHandle(handle);
	while(1)
	{
		printf("world\n");
		Sleep(1000);
	}
	return 0;
}
