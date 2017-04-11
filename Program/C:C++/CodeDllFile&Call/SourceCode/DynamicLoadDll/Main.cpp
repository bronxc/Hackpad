#include <windows.h>
#include <iostream>
using namespace std;

//define 函数指针类型
typedef int (*AddFunc)(int a, int b);

int main(int argc, char* argv[]) {
	int a=10, b=5;
   
	HINSTANCE hDll = LoadLibrary(TEXT("Dll_demo.dll"));
	/*
	格式为hdll=LoadLibrary（“DLL地址”）；
	这里字符串类型是LPSTR，当是unicode字符集的时候会不行，
	因此要在配置-属性-常规里面把默认字符集“unicode”改成支持多字符扩展即可。
	或者：
	在这里使用 TEXT 转换一下
	*/

	AddFunc add = (AddFunc)GetProcAddress(hDll, "add");
	//GetProcAddress函数检索指定的动态链接库(DLL)中的输出库函数地址。

	if(add != NULL) {
		cout << add(a, b) << endl;
	}

	//release dll
	FreeLibrary(hDll);

	system("pause");
	return 0;
}