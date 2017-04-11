/**
 * Using: This is a test for delete key from regedit
 * Author: xx
 * Version 1.0
 * Time: 2016.11.29
 */

#include <windows.h>
#include <iostream>
using namespace std;

void showErrorText(DWORD error_code);

/**
 * core function
   LONG WINAPI RegDeleteKey(
   _In_  HKEY hKey,          // regedit handle
   _In_  LPCTSTR lpSubKey    // will delete key name
   );
 */

int main(int argc, char* argv[]) {
	HKEY hKey;
	HKEY subKey;
	DWORD result;

	//open regedit
	result = RegOpenKeyEx(
		//open HKEY_CURRENT_USER/Software/
		HKEY_CURRENT_USER,
		TEXT("Software"),
		0,
		KEY_WRITE,
		&hKey
		);

	if(result == ERROR_SUCCESS) {
		cout << "open success" << endl;
	}
	else{
		cout << "open failed" << endl;
		showErrorText(result);
	}

	//delete HKEY_CURRENT_USER/Software/xxTest
	result = RegDeleteKey(hKey, TEXT("xxTest"));

	if(result == ERROR_SUCCESS) {
		cout << "delete success" << endl;
	}
	else {
		cout << "delete failed" << endl;
		showErrorText(result);
	}

	RegCloseKey(hKey);

	system("pause");
	return 0;
}

void showErrorText(DWORD error_code) {
	WCHAR *msg = NULL;
	FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        error_code,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Ê¹ÓÃÄ¬ÈÏÓïÑÔ
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