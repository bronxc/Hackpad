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

	/**
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
    	    (LPTSTR)&msg,
    	    0,
    	    NULL


#####3. 删除注册表项值的实例   

	/**
	   LONG WINAPI RegDeleteValue(
	   _In_opt_  LPCTSTR lpValueName // 具体要删除的值
	   );
	
	void showErrorCode(DWORD error_code) {
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
    	    (LPTSTR)&msg,
    	    0,
    	    NULL


#####4. 删除注册表项键的实例  

	/**
	
	void showErrorCode(DWORD error_code) {
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
    	    (LPTSTR)&msg,
    	    0,
    	    NULL


#####5. 列举某个注册表项之下的所有子项实例  

	/**





</br>  

---------------------------------  
References:  
Lellansin's 冰森:  <http://www.lellansin.com/windows-api-教程（十）-注册表操作.html>    
MSDN:  <https://msdn.microsoft.com/en-us/library/windows/desktop/ms724875(v=vs.85).aspx>

</br>
Author: xx  
Time: 2016.11.29  

