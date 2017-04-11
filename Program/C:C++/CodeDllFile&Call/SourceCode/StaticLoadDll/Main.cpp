#include "DllDemoHeader.h"
#include <iostream>
using namespace std;

//load Dll_demo.lib
#pragma comment(lib, "Dll_demo.lib")

int main(int argc, char* argv[]) {

	cout << add(2, 3) << endl;

	system("pause");
	return 0;
}