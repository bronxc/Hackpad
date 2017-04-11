/*
 * Using: This is a demo of windows service, it can create a windows service and run, every 5 second
		  write log to disk.
 * Author: xx
 * Time: 2016.12.7
 */

#include <windows.h>
#include <time.h>
#include <iostream>
using namespace std;

//define
#define SLEEP_TIME 5000  
#define LOGFILE "C:\\test.txt"  
#define SERVICENAME "testNTService"  


//function 'ControlHandler', this is handle infomation from SCM
void ControlHandler(DWORD request);

//function 'ServiceMain', this is service enter function
void ServiceMain(int argc, char** argv);

//function 'writeLog', to write log to disk
int writeLog(const char* str);

/****************************************/
//define global variable

/*
typedef struct _SERVICE_STATUS {
  DWORD dwServiceType;					//The type of service
  DWORD dwCurrentState;					//The current state of the service
  DWORD dwControlsAccepted;				//The control codes the service accepts and processes in its handler function
  DWORD dwWin32ExitCode;				//The error code the service uses to report an error that occurs when it is starting or stopping
  DWORD dwServiceSpecificExitCode;		//A service-specific error code that the service returns when an error occurs while the service is starting or stopping. 
  DWORD dwCheckPoint;					//The check-point value the service increments periodically to report its progress during a lengthy start, stop, pause, or continue operation. 
  DWORD dwWaitHint;						//
} SERVICE_STATUS, *LPSERVICE_STATUS;
*/

SERVICE_STATUS g_ServiceStatus;   

SERVICE_STATUS_HANDLE g_hStatus;		//this is parameter of function 'setServiceStatus()', using change service status

/****************************************/

int main(int argc, char* argv[]) {
	SERVICE_TABLE_ENTRY serviceTable[2];

	//set service name
	serviceTable[0].lpServiceName = TEXT(SERVICENAME);
	//set a pointer to a ServiceMain function.
	serviceTable[0].lpServiceProc = (LPSERVICE_MAIN_FUNCTION)ServiceMain; 
	//set null
	serviceTable[1].lpServiceName = NULL;
	serviceTable[1].lpServiceProc = NULL;

	//Connects the main thread of a service process to the service control manager(SCM)
	StartServiceCtrlDispatcher(serviceTable);

	//join service, and set auto start
	system("sc create TestAuto binPath= \"C:\\Service.exe\"");
	system("sc config TestAuto start= auto");

	system("pause");
	return 0;
}

//Achieve function 'ServiceMain'
void ServiceMain(int argc, char** argv) {
	g_ServiceStatus.dwServiceType = SERVICE_WIN32;   
    g_ServiceStatus.dwCurrentState = SERVICE_START_PENDING;   
    g_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN | SERVICE_ACCEPT_PAUSE_CONTINUE;  
    g_ServiceStatus.dwWin32ExitCode = 0;   
    g_ServiceStatus.dwServiceSpecificExitCode = 0;   
    g_ServiceStatus.dwCheckPoint = 0;   
    g_ServiceStatus.dwWaitHint = 0;

	//Registers a function to handle extended service control requests.
	g_hStatus = RegisterServiceCtrlHandler(TEXT(SERVICENAME), (LPHANDLER_FUNCTION)ControlHandler);   
    if (g_hStatus == (SERVICE_STATUS_HANDLE)0) { 
        return;   
    }

	//execute success, change g_ServiceStatus.dwCurrentState
	g_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
	//Updates the service control manager's status information for the calling service.
	SetServiceStatus(g_hStatus, &g_ServiceStatus);

	//do something
	char buf[256];
	time_t ltime;

	while(true) {
        if(g_ServiceStatus.dwCurrentState == SERVICE_RUNNING) {  
            time( &ltime );  
            ctime_s( buf, sizeof(buf), &ltime );  
  
            if(writeLog(buf)) {
                g_ServiceStatus.dwCurrentState = SERVICE_STOPPED; 
                g_ServiceStatus.dwWin32ExitCode = -1; 
                SetServiceStatus(g_hStatus, &g_ServiceStatus);
                return;
            }
        }
		else if(g_ServiceStatus.dwCurrentState != SERVICE_PAUSED) {
            break;
        }
        Sleep(SLEEP_TIME);  
    }

}

//Achieve function 'ServiceMain'
void ControlHandler(DWORD request) {
	switch(request) {
		case SERVICE_CONTROL_PAUSE:
			writeLog("Pause.");
			g_ServiceStatus.dwWin32ExitCode = 0;   
			g_ServiceStatus.dwCurrentState = SERVICE_PAUSED; 
			break;
		case SERVICE_CONTROL_CONTINUE:  
			writeLog("Continue.");
			g_ServiceStatus.dwWin32ExitCode = 0;
			g_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
			break;
		case SERVICE_CONTROL_STOP:   
		    writeLog("Stop.");
		    g_ServiceStatus.dwWin32ExitCode = 0;
		    g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		    break;  
		case SERVICE_CONTROL_SHUTDOWN:   
		    writeLog("Shutdown.");
		    g_ServiceStatus.dwWin32ExitCode = 0;
		    g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		    break;
		default:
		    break;
	}

	SetServiceStatus (g_hStatus, &g_ServiceStatus);

	return;
}

//Achieve function 'ServiceMain'
int writeLog(const char* str) {
	FILE* log = fopen(LOGFILE, "a+");

	if(log == NULL) {
		return -1;
	}
	fprintf(log, "%s\n", str);
	fclose(log);

	return 0;
}