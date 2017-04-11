/**
 * Using: This is a test for create a item in regedit
 * Author: xx
 * Version: 1.0
 * Time: 2016.11.28
 */

#include <windows.h>
#include <tchar.h>
#include <iostream>
using namespace std;

void showErrorCode(DWORD error_code);

/**
 * core function
   LONG WINAPI RegCreateKey(
   _In_      HKEY hKey,          // 创建在哪个注册表项之下
   _In_opt_  LPCTSTR lpSubKey,   // 项名
   _Out_     PHKEY phkResult     // 返回创建的句柄
   );
 */

int main(int argc, char* argv[]) {
	HKEY hKey;
	HKEY subKey;
	DWORD result;
	LPCTSTR str = _T("This is a test");

	//open regedit, HKEY_CURRENT_USER\Software
	result = RegOpenKeyEx(
				HKEY_CURRENT_USER,		//open
				TEXT("Software"),
				0,						//retain parameter
				KEY_WRITE,				//authority->write
				&hKey					//open handle
		);

	if(result == ERROR_SUCCESS) {
		cout << "openReg success" << endl;
	}
	else {
		cout << "openReg Failed" << endl;
		showErrorCode(result);
	}

	//add Reg item, "HKEY_CURRENT_USER\SoftWare\xxTest"
	RegCreateKey(hKey, TEXT("xxTest"), &subKey);

	//set value of "HKEY_CURRENT_USER\SoftWare\xxTest\name"
	result = RegSetValueEx(
		subKey,				
		TEXT("name"),				//"name"String
		0,							//retain parameter
		REG_SZ,						//type is string
		(const BYTE*)str,			//first address of string
		(_tcslen(str) + 1) * sizeof(TCHAR)					//byte number of string
		);

	if(result == ERROR_SUCCESS) {
		cout << "set success" << endl;
	}
	else {
		cout << "set failed" << endl;
		showErrorCode(result);
	}

	//close Reg
	RegCloseKey(hKey);

	system("pause");
	return 0;
}

void showErrorCode(DWORD error_code) {
	WCHAR *msg = NULL;
	FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        error_code,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // 使用默认语言
        (LPTSTR)&msg,
        0,
        NULL
	);
	cout << "Error Code is " << error_code<< endl;
	if(msg == NULL) {
		cout << "Unknown Error" << endl;
	}
	else {
		cout << "Formatted message: " << *msg << endl;;
	}
}