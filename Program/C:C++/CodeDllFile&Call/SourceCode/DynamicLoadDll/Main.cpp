#include <windows.h>
#include <iostream>
using namespace std;

//define ����ָ������
typedef int (*AddFunc)(int a, int b);

int main(int argc, char* argv[]) {
	int a=10, b=5;
   
	HINSTANCE hDll = LoadLibrary(TEXT("Dll_demo.dll"));
	/*
	��ʽΪhdll=LoadLibrary����DLL��ַ������
	�����ַ���������LPSTR������unicode�ַ�����ʱ��᲻�У�
	���Ҫ������-����-���������Ĭ���ַ�����unicode���ĳ�֧�ֶ��ַ���չ���ɡ�
	���ߣ�
	������ʹ�� TEXT ת��һ��
	*/

	AddFunc add = (AddFunc)GetProcAddress(hDll, "add");
	//GetProcAddress��������ָ���Ķ�̬���ӿ�(DLL)�е�����⺯����ַ��

	if(add != NULL) {
		cout << add(a, b) << endl;
	}

	//release dll
	FreeLibrary(hDll);

	system("pause");
	return 0;
}