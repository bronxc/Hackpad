#C++ 函数指针  

-----------------------

###0x00 前言  
一个使用函数指针的样例

###0x01 正文  

	#include <iostream>	using namespace std;	//定义一个函数指针	typedef char (*pFunc)(char b);	char func(char a) {		return a;	}	int main(int argc, char* argv[]) {		pFunc pfunc = func;		cout << pfunc('b') << endl;		system("pause");		return 0;	}


</br>

----------------------  
References:  


</br>
Author: xx  
Time: 2016.11.22