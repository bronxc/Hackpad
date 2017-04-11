/**
 * Using: This is a test for delete value of key from regedit
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
   LONG WINAPI RegDeleteValue(
   _In_      HKEY hKey,          // Ҫɾ��Ŀ��ע����������
   _In_opt_  LPCTSTR lpValueName // ����Ҫɾ����ֵ
   );
 */

int main(int argc, char* argv[]) {
	HKEY hKey;
	HKEY subKey;
	DWORD result;

	//open regedit
	result = RegOpenKeyEx(
		//open HKEY_CURRENT_USER/Software/xxTest
		HKEY_CURRENT_USER,
		TEXT("Software\\xxTest"),
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

	//delete "name" from HKEY_CURRENT_USER/Software/xxTest/
	result = RegDeleteValue(hKey, TEXT("name"));

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
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // ʹ��Ĭ������
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