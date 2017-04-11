/**
 * Using: This is a test for exe auto start by regedit
 * Author: xx
 * Version: 1.0
 * Time: 2016.11.29
 */

#include <windows.h>
#include <tchar.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    HKEY hKey;
    DWORD result;
    LPCTSTR str = _T("C:\\Test.exe");
	//test.exe is print "HelloWorld" in console, in C:\\

    //open regedit, HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run
    result = RegOpenKeyEx(
                HKEY_CURRENT_USER,      //open
                TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),
                0,                      //retain parameter
                KEY_WRITE,              //authority->write
                &hKey                   //open handle
        );

    if(result == ERROR_SUCCESS) {
        cout << "openReg success" << endl;
    }
    else {
        cout << "openReg Failed" << endl;
    }

    //set value of "HKEY_CURRENT_USER\SoftWare\xxTest\name"
    result = RegSetValueEx(
        hKey,             
        TEXT("AutoStartForTest"),   
        0,                          //retain parameter
        REG_SZ,                     //type is string
        (const BYTE*)str,           //first address of string
        (_tcslen(str) + 1) * sizeof(TCHAR)                  //byte number of string
        );

    if(result == ERROR_SUCCESS) {
        cout << "set success" << endl;
    }
    else {
        cout << "set failed" << endl;
    }
	
    //close Reg
    RegCloseKey(hKey);

    system("pause");
    return 0;
}
