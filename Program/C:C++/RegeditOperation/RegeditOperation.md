#RegeditOperation  

----------------------------------  

###0x00 前言  
使用 C++ 操作注册表样例  


###0x01 目录  
1. 打开注册表函数 RegOpenKeyEx 
2. 创建注册表项实例
3. 删除注册表项值的实例
4. 删除注册表项键的实例
5. 列举某个注册表项之下的所有子项实例


###0x02 正文  
#####1. 打开注册表函数 RegOpenKeyEx   
__RegOpenKeyEx函数原型__  

	LONG WINAPI RegOpenKeyEx(
		_In_        HKEY hKey,        // 要打开的键的句柄
  		_In_opt_    LPCTSTR lpSubKey, // 其子项
  		_Reserved_  DWORD ulOptions,  // 保留位，无用，请无视
  		_In_        REGSAM samDesired,// 打开权限
  		_Out_       PHKEY phkResult   // 返回打开的句柄
	);

__参数__  
参数一 hKey (输入参数)  
可以传入已存在的注册表句柄（HKEY类型），也可以传入默认存在的项如：HKEY_CLASSES_ROOT、HKEY_CURRENT_USER、HKEY_LOCAL_MACHINE、HKEY_USERS、HKEY_CURRENT_CONFIG

参数二 lpSubKey (输入参数、可选)  
子项字符串，可不填。如果有填写的话，那么久相当于打开 "hKey\lpSubKey" (参数一与参数二拼接起来) 的注册表项。

参数三 ulOptions (保留参数)  
保留参数，必须填 0。

参数四 samDesired (输入参数)  
打开的注册表项句柄的权限。常见如下： 

|权限名 |   权限|
|-------|-----|
|KEY\_READ (0x20019)|	读取权限|
|KEY\_WRITE (0x20006)|	写入权限|
|KEY\_SET\_VALUE (0x0002)	|创建、删除或修改|
KEY\_QUERY\_VALUE (0x0001)|	查询值
KEY\_CREATE\_LINK (0x0020)|	系统保留(无用)
KEY\_CREATE\_SUB\_KEY (0x0004)|	注册键和创建子键
KEY\_ENUMERATE\_SUB\_KEYS (0x0008)	|遍历子键
KEY\_EXECUTE (0x20019)|	相当于KEY\_READ
KEY\_ALL\_ACCESS (0xF003F)|	所有权限  

参数五 phkResult (输出参数)
返回输出的句柄。

__返回值__  
成功返回 `ERROR_SUCCESS` 即 0，失败则返回错误码。可以使用 `FormatMessage` 函数读取相应错误码的信息。


#####2. 创建注册表项实例  

	/** 	 * Using: This is a test for create a item in regedit 	 * Author: xx 	 * Version: 1.0 	 * Time: 2016.11.28 	 */	#include <windows.h>	#include <tchar.h>	#include <iostream>	using namespace std;	void showErrorCode(DWORD error_code);	/**     * core function   		LONG WINAPI RegCreateKey(   		_In_      HKEY hKey,          // 创建在哪个注册表项之下		_In_opt_  LPCTSTR lpSubKey,   // 项名	    _Out_     PHKEY phkResult     // 返回创建的句柄   		);	  */	int main(int argc, char* argv[]) {		HKEY hKey;		HKEY subKey;		DWORD result;		LPCTSTR str = _T("This is a test");			//open regedit, HKEY_CURRENT_USER\Software		result = RegOpenKeyEx(					HKEY_CURRENT_USER,		//open					TEXT("Software"),					0,						//retain parameter					KEY_WRITE,				//authority->write					&hKey					//open handle			);		if(result == ERROR_SUCCESS) {			cout << "openReg success" << endl;		}		else {			cout << "openReg Failed" << endl;			showErrorCode(result);		}			//add Reg item, "HKEY_CURRENT_USER\SoftWare\xxTest"		RegCreateKey(hKey, TEXT("xxTest"), &subKey);			//set value of "HKEY_CURRENT_USER\SoftWare\xxTest\name"		result = RegSetValueEx(			subKey,							TEXT("name"),				//"name"String			0,							//retain parameter			REG_SZ,						//type is string			(const BYTE*)str,			//first address of string			(_tcslen(str) + 1) * sizeof(TCHAR)					//byte number of string			);		if(result == ERROR_SUCCESS) {			cout << "set success" << endl;		}		else {			cout << "set failed" << endl;			showErrorCode(result);		}		//close Reg		RegCloseKey(hKey);			system("pause");		return 0;	}	void showErrorCode(DWORD error_code) {		WCHAR *msg = NULL;		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,            error_code,    	    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // 使用默认语言
    	    (LPTSTR)&msg,
    	    0,
    	    NULL		);		cout << "Error Code is " << error_code<< endl;		if(msg == NULL) {			cout << "Unknown Error" << endl;		}		else {			cout << "Formatted message: " << *msg << endl;;		}	}


#####3. 删除注册表项值的实例   

	/** 	 * Using: This is a test for delete value of key from regedit	 * Author: xx	 * Version 1.0	 * Time: 2016.11.29	 */	#include <windows.h>	#include <iostream>	using namespace std;	void showErrorText(DWORD error_code);	/**	 * core function
	   LONG WINAPI RegDeleteValue(	   _In_      HKEY hKey,          // 要删除目标注册表项的主体
	   _In_opt_  LPCTSTR lpValueName // 具体要删除的值
	   ); 	*/	int main(int argc, char* argv[]) {		HKEY hKey;		HKEY subKey;		DWORD result;		//open regedit		result = RegOpenKeyEx(			//open HKEY_CURRENT_USER/Software/xxTest			HKEY_CURRENT_USER,			TEXT("Software\\xxTest"),			0,			KEY_WRITE,			&hKey			);		if(result == ERROR_SUCCESS) {			cout << "open success" << endl;		}		else{			cout << "open failed" << endl;			showErrorText(result);		}		//delete "name" from HKEY_CURRENT_USER/Software/xxTest/		result = RegDeleteValue(hKey, TEXT("name"));		if(result == ERROR_SUCCESS) {			cout << "delete success" << endl;		}		else {			cout << "delete failed" << endl;			showErrorText(result);		}		RegCloseKey(hKey);		system("pause");		return 0;	}
	
	void showErrorCode(DWORD error_code) {		WCHAR *msg = NULL;		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,            error_code,    	    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // 使用默认语言
    	    (LPTSTR)&msg,
    	    0,
    	    NULL		);		cout << "Error Code is " << error_code<< endl;		if(msg == NULL) {			cout << "Unknown Error" << endl;		}		else {			cout << "Formatted message: " << *msg << endl;;		}	}


#####4. 删除注册表项键的实例  

	/** 	 * Using: This is a test for delete key from regedit	 * Author: xx	 * Version 1.0	 * Time: 2016.11.29	 */	#include <windows.h>	#include <iostream>	using namespace std;	void showErrorText(DWORD error_code);	/**	 * core function	   LONG WINAPI RegDeleteKey(	   _In_  HKEY hKey,          // regedit handle	   _In_  LPCTSTR lpSubKey    // will delete key name	   );	 */	int main(int argc, char* argv[]) {		HKEY hKey;		HKEY subKey;		DWORD result;		//open regedit		result = RegOpenKeyEx(			//open HKEY_CURRENT_USER/Software/			HKEY_CURRENT_USER,			TEXT("Software"),			0,			KEY_WRITE,			&hKey			);		if(result == ERROR_SUCCESS) {			cout << "open success" << endl;		}		else{			cout << "open failed" << endl;			showErrorText(result);		}		//delete HKEY_CURRENT_USER/Software/xxTest		result = RegDeleteKey(hKey, TEXT("xxTest"));		if(result == ERROR_SUCCESS) {			cout << "delete success" << endl;		}		else {			cout << "delete failed" << endl;			showErrorText(result);		}		RegCloseKey(hKey);		system("pause");		return 0;	}
	
	void showErrorCode(DWORD error_code) {		WCHAR *msg = NULL;		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,            error_code,    	    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // 使用默认语言
    	    (LPTSTR)&msg,
    	    0,
    	    NULL		);		cout << "Error Code is " << error_code<< endl;		if(msg == NULL) {			cout << "Unknown Error" << endl;		}		else {			cout << "Formatted message: " << *msg << endl;;		}	}


#####5. 列举某个注册表项之下的所有子项实例  

	/**	 * Using: Query all key in branch of regedit	 * From: MSDN   https://msdn.microsoft.com/en-us/library/ms724256	 * Time: 2016.11.29	 */	// QueryKey - Enumerates the subkeys of key and its associated values.	//     hKey - Key whose subkeys and values are to be enumerated.	#include <windows.h>	#include <stdio.h>	#include <tchar.h>	#define MAX_KEY_LENGTH 255	#define MAX_VALUE_NAME 16383 	void QueryKey(HKEY hKey) 	{ 	    TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name	    DWORD    cbName;                   // size of name string 	    TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 	    DWORD    cchClassName = MAX_PATH;  // size of class string 	    DWORD    cSubKeys=0;               // number of subkeys 	    DWORD    cbMaxSubKey;              // longest subkey size 	    DWORD    cchMaxClass;              // longest class string 	    DWORD    cValues;              // number of values for key 	    DWORD    cchMaxValue;          // longest value name 	    DWORD    cbMaxValueData;       // longest value data 	    DWORD    cbSecurityDescriptor; // size of security descriptor 	    FILETIME ftLastWriteTime;      // last write time  	    DWORD i, retCode;  	    TCHAR  achValue[MAX_VALUE_NAME]; 	    DWORD cchValue = MAX_VALUE_NAME;  	    // Get the class name and the value count. 	    retCode = RegQueryInfoKey(	        hKey,                    // key handle 	        achClass,                // buffer for class name 	        &cchClassName,           // size of class string 	        NULL,                    // reserved 	        &cSubKeys,               // number of subkeys 	        &cbMaxSubKey,            // longest subkey size 	        &cchMaxClass,            // longest class string 	        &cValues,                // number of values for this key 	        &cchMaxValue,            // longest value name 	        &cbMaxValueData,         // longest value data 	        &cbSecurityDescriptor,   // security descriptor 	        &ftLastWriteTime);       // last write time  	    // Enumerate the subkeys, until RegEnumKeyEx fails.    	    if (cSubKeys)	    {	        printf( "\nNumber of subkeys: %d\n", cSubKeys);	        for (i=0; i<cSubKeys; i++) 	        { 	            cbName = MAX_KEY_LENGTH;	            retCode = RegEnumKeyEx(hKey, i,	                     achKey, 	                     &cbName, 	                     NULL, 	                     NULL, 	                     NULL, 	                     &ftLastWriteTime); 	            if (retCode == ERROR_SUCCESS) 	            {	                _tprintf(TEXT("(%d) %s\n"), i+1, achKey);	            }	        }	    }  	    // Enumerate the key values. 	    if (cValues) 	    {	        printf( "\nNumber of values: %d\n", cValues);	        for (i=0, retCode=ERROR_SUCCESS; i<cValues; i++) 	        { 	            cchValue = MAX_VALUE_NAME; 	            achValue[0] = '\0'; 	            retCode = RegEnumValue(hKey, i, 	                achValue, 	                &cchValue, 	                NULL, 	                NULL,	                NULL,	                NULL); 	            if (retCode == ERROR_SUCCESS ) 	            { 	                _tprintf(TEXT("(%d) %s\n"), i+1, 	achValue); 	            } 	        }	    }	}	int __cdecl _tmain(void)	{	   HKEY hTestKey;	   if( RegOpenKeyEx( HKEY_CURRENT_USER,	        TEXT("SOFTWARE\\Microsoft"),	        0,	        KEY_READ,	        &hTestKey) == ERROR_SUCCESS	      )	   {	      QueryKey(hTestKey);	   }   	   RegCloseKey(hTestKey);	   system("pause");	   return 0;	}





</br>  

---------------------------------  
References:  
Lellansin's 冰森:  <http://www.lellansin.com/windows-api-教程（十）-注册表操作.html>    
MSDN:  <https://msdn.microsoft.com/en-us/library/windows/desktop/ms724875(v=vs.85).aspx>

</br>
Author: xx  
Time: 2016.11.29  


