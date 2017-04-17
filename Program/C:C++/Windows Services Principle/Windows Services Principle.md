#Windows Services Principle  

------------------------------  

###0x00 前言  
Windows服务的原理和组成部分，以及编程。


###0x01 目录  
1. Windows服务简介
2. 服务控制管理器
3. 服务控制程序
4. 服务程序结构
5. 服务程序编写


###0x02 正文  
####1. Windows服务简介
Microsoft Windows 服务（即，以前的 NT 服务）使您能够创建在它们自己的 Windows 会话中可长时间运行的可执行应用程序。这些服务可以在计算机启动时自动启动，可以暂停和重新启动而且不显示任何用户界面。这种服务非常适合在服务器上使用，或任何时候，为了不影响在同一台计算机上工作的其他用户，需要长时间运行功能时使用。还可以在不同于登录用户的特定用户帐户或默认计算机帐户的安全上下文中运行服务。Windows中就被称作服务。Windows的服务由服务程序、服务控制程序（SCP，service control program）和服务控制管理器（SCM，service control manager）三个组件构成。

####2. 服务控制管理器  
SCM本身也是一个服务程序（windowssystem32servics.exe），作为windows的后台服务运行的。Winlogon在系统引导的早期会将SCM启动起来。  

服务控制管理器（Service Control Manager）：在系统启动的时候开始，是WIN系统的一部分，它是一个远程过程调用（RPC）服务器。这也是WIN服务系统的核心。  
SCM主要负责下面的东西：  

* 维护安装的服务数据库
* 在系统启动或者有命令的时候开始服务和驱动服务
* 枚举安装的服务和驱动
* 维护运行着的服务和驱动的状态
* 传输控制请求去运行服务  
* 锁定和解锁服务数据库  


SCM维护着注册表中的服务数据库，位于：HKEY\_LOCAL\_MACHINE\SYSTEM\CurrentControlSet\Services。其下的子键就是安装的服务和驱动服务。每个子键的名称就是服务名，当安装的时候由服务安全程序的 CreateService 函数指定。  
	
当系统安装的时候，最初的数据库就被创建。这个数据库包含系统启动时候的设备驱动。数据库中的每个服务和驱动的信息包括：  

* 服务类型。
服务执行时候是自己的进行还是同其他服务共享进行，是否是核心驱动还是文件系统驱动。
* 启动类型。
服务或者驱动服务是否是在系统启动的时候自动启动还是，是否是由SCM来接受控制请求来启动。启动类型也表明服务是否被禁止。
* 错误控制等级。
指明如果服务或者驱动服务启动失败的错误处理。
* 执行文件的全路径。
* 附加依赖信息决定启动的正确顺序。对于服务，这个信息包括在服务启动之前SCM需要先启动的指定服务，服务所属加载顺序组的名称，服务在组中启动顺序的标志符。对于驱动服务，这个信息包括驱动启动前需要启动的指定驱动。
* 对于服务，还有附加的帐号名称和密码。如果没有指定帐号，服务就使用LocalSystem帐号。
* 对于驱动，附加驱动对象名称，用于I/0系统加载设备驱动。如果没有指明对象名，I/O系统在驱动服务名称基础上创
建一个默认的名称。



####3. 服务控制程序
服务控制程序（SCP）则是控制服务应用程序的功能块，也是服务应用程序同服务管理器（SCM）之间的桥梁。服务控制程序可以完成这些动作：

* 如果服务启动类型为SERVICE\_DEMAND\_START，那么服务控制程序来启动服务
* 发送控制请求给运行着的服务
* 查询运行着的服务的当前状态

这些动作要求打开一个服务对象的句柄。



####4. 服务程序结构  
一个服务必须包含 main 、ServiceMain 和 控制处理函数。

__1.服务的main函数__   
服务通常是控制台程序，入口点就是main函数，main函数从注册表中服务的ImagePath值中获得参数。当SCM开始服务程序的时候，等待调用StartServiceCtrlDispatcher 函数。规则为：

* SERVICE\_WIN32\_OWN\_PROCESS 类型的服务会从主线程立刻调用 StartServiceCtrlDispatcher 函数。可以在服务启动后完全初始化。
* SERVICE\_WIN32\_SHARE\_PROCESS类型的服务，在程序中进行公共初始化，可以在StartServiceCtrlDispatcher函数调用前在主线程中完成初始化，只要花费的时间少于30秒。否则，当主线程调用StartServiceCtrlDispatcher的时候必须创建另外一个线程去完成公共初始化。可以在 ServiceMain 函数中去完成每个服务单独的初始化。 

StartServiceCtrlDispatcher函数为在进程中的每个服务获得一个SERVICE\_TABLE\_ENTRY 结构。每个结构指定服务名和服务的入口点。如果StartServiceCtrlDispatcher函数调用成功，调用线程不会返回，直到所有运行服务的进程都终止。SCM通过命名管道控制这个线程的请求。这个线程就象发报机（调度器），完成下面任务：

* 当新的服务开始时，创建一个新的线程去调用适当的入口
* 调用适当的句柄函数去操作服务控制请求

当SCM启动一个服务进程的时候，就会调用StartServiceCtrlDispatcher函数，它接收一个服务入口列表或者单个服务进程的单个入口，每个入口点通过于入口通讯的服务名来鉴别。在建议一个命名管道同SCM通讯后，此函数陷入循环等待来自管道的SCM命令。SCM在每一次启动服务时发一个服务启动命令。而StartServiceCtrlDispatcher函数每接收一次命令就创建一个服务线程来调用服务的如后和执行服务的循环命令。StartServiceCtrlDispatcher函数等待来自SCM的命令，在所有进程的服务线程都停止并允许进程在离开时清除资源后，才将控制权交还给进程的主函数。

__2.服务的 ServiceMain 函数__  
ServiceMain函数是服务的入口点。

当服务控制程序要求运行新的服务，SCM启动该服务，并且发送一个开始请求到调度器。调度器创建一个新线程执行服务的ServiceMain函数。ServiceMain函数完成下面的任务：

* 立刻调用RegisterServiceCtrlHandlerEx 函数去注册服务的句柄控制请求，返回值就是服务的状态句柄，可以用来通知SCM服务的状态。
* 完成初始化。如果初始化代码执行的时间很短（少于1秒），初始化可以在ServiceMain函数中直接完成；如果初始化的时间长于1秒，那么调用SetServiceStatus 函数，在SERVICE_STATUS结构中指定SERVICE\_START\_PENDING 服务状态和等待时间。当初始化继续，服务应当另外调用SetServiceStatus 去报告进展。
* 当初始化完成，调用SetServiceStatus，在SERVICE\_STATUS 结构中指定服务状态为SERVICE\_RUNNING。
* 完成服务任务，或者，如果没有未决（pending）任务，返回。所有状态变化，都调用SetServiceStatus去报告。
* 如果在服务初始化或者运行中发生了错误，服务应该调用SetServiceStatus，指定SERVICE\_STOP\_PENDING 状态，如果清除过程比较长。一旦清除完成，从最后终止的线程调用SetServiceStatus，指定SERVICE\_STOPPED状态。确定要指定SERVICE\_STATUS结构中dwServiceSpecificExitCode 和 dwWin32ExitCode 来确定这个错误。  

__3.服务的控制处理函数__  
每个服务都有控制处理函数：HandlerEx 函数，它被控制发出者调用，当服务进程接受一个控制请求的时候，因此，这个函数以控制发出者的安全关系执行。无论什么时候HandlerEx被调用，服务都必须调用SetServiceStatus函数去向SCM报告服务状态，而不管是否服务的状态被改变。

服务控制程序可以使用ControlService函数发出控制请求。所有的服务都必须接受和处理SERVICE\_CONTROL\_INTERROGATE控制码。可以通过SetServiceStatus来同意或者禁止接受其他控制码。要接收SERVICE\_CONTROL\_DEVICEEVENT 控制码，必须调用RegisterDeviceNotification函数。服务可以处理用户自定义的控制码。控制处理必须在30秒以内返回，否则SCM就会返回一个错误。如果服务需要完成一个很长的任务，应该创建一个新的线程去完成这个长任务，然后返回。这可以防止服务阻碍控制发者。

当用户关闭系统，所有的控制处理要调用SetServiceStatus设置SERVICE\_ACCEPT\_SHUTDOWN控制码去接收
SERVICE\_CONTROL\_SHUTDOWN控制码，它们都会按照服务数据库中的顺序依次被通知。默认情况下，在系统关闭前，一个服务通常有大约20秒去完成清除任务。当时间过了之后，系统会关闭进程，而不管服务是否完成了关闭。请注意，如果系统停留在shutdown状态（不是restarted 和 powered down），服务仍然是在运行的。

如果服务需要时间去清除，它可以发送 STOP\_PENDING 状态消息，连同一个等待时间，这样，服务控制器在报告系统服务关闭之前才知道应该待多长时间，无论如何，都有一个服务控制器需要等待的时间，防止服务停留在shutdown状态。要改变这个时间限制，可以修改HKEY\_LOCAL\_MACHINE\SYSTEM\CurrentControlSet\Control中的WaitToKillServiceTimeout值。



####5. 服务程序编写  

	/*	 * Using: This is a demo of windows service, it can create a windows service and run, every 5 second		  write log to disk.	 * Author: xx	 * Time: 2016.12.7	 */	#include <windows.h>	#include <time.h>	#include <iostream>	using namespace std;	//define	#define SLEEP_TIME 5000  	#define LOGFILE "C:\\test.txt"  	#define SERVICENAME "testNTService"  	//function 'ControlHandler', this is handle infomation from SCM	void ControlHandler(DWORD request);	//function 'ServiceMain', this is service enter function	void ServiceMain(int argc, char** argv);	//function 'writeLog', to write log to disk	int writeLog(const char* str);	/****************************************/	//define global variable	/*	typedef struct _SERVICE_STATUS {	  DWORD dwServiceType;					//The type of service	  DWORD dwCurrentState;					//The current state of the service	  DWORD dwControlsAccepted;				//The control codes the service accepts and processes in its handler function	  DWORD dwWin32ExitCode;				//The error code the service uses to report an error that occurs when it is starting or stopping	  DWORD dwServiceSpecificExitCode;		//A service-specific error code that the service returns when an error occurs while the service is starting or stopping. 	  DWORD dwCheckPoint;					//The check-point value the service increments periodically to report its progress during a lengthy start, stop, pause, or continue operation. 	  DWORD dwWaitHint;						//	} SERVICE_STATUS, *LPSERVICE_STATUS;	*/	SERVICE_STATUS g_ServiceStatus;   	SERVICE_STATUS_HANDLE g_hStatus;		//this is parameter of function 'setServiceStatus()', using change service status	/****************************************/	int main(int argc, char* argv[]) {		SERVICE_TABLE_ENTRY serviceTable[2];		//set service name		serviceTable[0].lpServiceName = TEXT(SERVICENAME);		//set a pointer to a ServiceMain function.		serviceTable[0].lpServiceProc = (LPSERVICE_MAIN_FUNCTION)ServiceMain; 		//set null		serviceTable[1].lpServiceName = NULL;		serviceTable[1].lpServiceProc = NULL;		//Connects the main thread of a service process to the service control manager(SCM)		StartServiceCtrlDispatcher(serviceTable);		//join service, and set auto start		system("sc create TestAuto binPath= \"C:\\Service.exe\"");		system("sc config TestAuto start= auto");		system("pause");		return 0;	}	//Achieve function 'ServiceMain'	void ServiceMain(int argc, char** argv) {		g_ServiceStatus.dwServiceType = SERVICE_WIN32;   	    g_ServiceStatus.dwCurrentState = SERVICE_START_PENDING;   	    g_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN | SERVICE_ACCEPT_PAUSE_CONTINUE;  	    g_ServiceStatus.dwWin32ExitCode = 0;   	    g_ServiceStatus.dwServiceSpecificExitCode = 0;   	    g_ServiceStatus.dwCheckPoint = 0;   	    g_ServiceStatus.dwWaitHint = 0;		//Registers a function to handle extended service control requests.		g_hStatus = RegisterServiceCtrlHandler(TEXT(SERVICENAME), (LPHANDLER_FUNCTION)ControlHandler);   	    if (g_hStatus == (SERVICE_STATUS_HANDLE)0) { 	        return;   	    }		//execute success, change g_ServiceStatus.dwCurrentState		g_ServiceStatus.dwCurrentState = SERVICE_RUNNING;		//Updates the service control manager's status information for the calling service.		SetServiceStatus(g_hStatus, &g_ServiceStatus);		//do something		char buf[256];		time_t ltime;		while(true) {	        if(g_ServiceStatus.dwCurrentState == SERVICE_RUNNING) {  	            time( &ltime );  	            ctime_s( buf, sizeof(buf), &ltime );    	            if(writeLog(buf)) {	                g_ServiceStatus.dwCurrentState = SERVICE_STOPPED; 	                g_ServiceStatus.dwWin32ExitCode = -1; 	                SetServiceStatus(g_hStatus, &g_ServiceStatus);	                return;	            }	        }			else if(g_ServiceStatus.dwCurrentState != SERVICE_PAUSED) {	            break;	        }	        Sleep(SLEEP_TIME);  	    }	}	//Achieve function 'ServiceMain'	void ControlHandler(DWORD request) {		switch(request) {			case SERVICE_CONTROL_PAUSE:				writeLog("Pause.");				g_ServiceStatus.dwWin32ExitCode = 0;   				g_ServiceStatus.dwCurrentState = SERVICE_PAUSED; 				break;			case SERVICE_CONTROL_CONTINUE:  				writeLog("Continue.");				g_ServiceStatus.dwWin32ExitCode = 0;				g_ServiceStatus.dwCurrentState = SERVICE_RUNNING;				break;			case SERVICE_CONTROL_STOP:   			    writeLog("Stop.");			    g_ServiceStatus.dwWin32ExitCode = 0;			    g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;			    break;  			case SERVICE_CONTROL_SHUTDOWN:   			    writeLog("Shutdown.");			    g_ServiceStatus.dwWin32ExitCode = 0;			    g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;			    break;			default:			    break;		}		SetServiceStatus (g_hStatus, &g_ServiceStatus);		return;	}	//Achieve function 'ServiceMain'	int writeLog(const char* str) {		FILE* log = fopen(LOGFILE, "a+");		if(log == NULL) {			return -1;		}		fprintf(log, "%s\n", str);		fclose(log);			return 0;	}
	

代码文件见附件，附件还包含有 MSDN 的 Demo



</br>

-------------------------------  
Refereneces:  
CSDN.B_H_L的专栏: <http://blog.csdn.net/b_h_l/article/details/23919119>  
MSDN:  <https://msdn.microsoft.com/zh-cn/ms683500(v=vs.85)>  
CSDN.iw1210的专栏:  <http://blog.csdn.net/iw1210/article/details/38059569>
codeproject.Mohit Arora:  <https://www.codeproject.com/articles/499465/simple-windows-service-in-cplusplus>  
CSDN.nodeathphoenix的专栏:  <http://blog.csdn.net/nodeathphoenix/article/details/24181509>  
MSDN:  <https://code.msdn.microsoft.com/CppWindowsService-cacf4948#content>  
ChinaUnix.我的爱好:  <http://blog.chinaunix.net/uid-20476365-id-1942518.html>  
CSDN.xcbeyond:  <http://blog.csdn.net/xcbeyond/article/details/38024633>  

Author: xx  
Time: 2016.12.13 