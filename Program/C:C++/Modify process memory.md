# Modify process memory  

--------------------------------  
### 0x00 前言  
内存修改器，就是那种常见的单机游戏修改器的东西。下面说一下这个东西的原理。


### 0x01 正文  
\- -！


### 0x02 程序  
下面是一段 C++ 的代码，（暂时还没写注释...

	#include <iostream>	#include <Windows.h>	using namespace std;	const int arrayMax = 100000;	int arrayLength = 0;	int resultLength = 0;	void readProcess(HANDLE hProcess, int processId, int value, int address[]);	void siftProcess(HANDLE hProcess, int processId, int siftValue, int address[], int resultArray[]);	void writeProcess(HANDLE hProcess, int processId, int result, int resultArray[]);	int main(int argc, char* argv[]) {		//		int processId = 0;		HANDLE hProcess;		int value = 0;		int siftValue = 0;		int result = 0;		int address[arrayMax] = {0};		int resultArray[10] = {0};		cout << "input processId: (refer for command 'tasklist')" << endl;		cin >> processId;		cout << "input search value: " << endl;		cin >> value;		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);		if(hProcess == NULL) {			cout << "OpenProcess Faild" << endl;		}	    else	    {			readProcess(hProcess, processId, value, address);				cout << "input sift value: " << endl;			cin >> siftValue;			siftProcess(hProcess, processId, siftValue, address, resultArray);			cout << "Address Result: " << endl;			for(int x = 0; x < resultLength; x++) {				cout << "0x" << hex << resultArray[x] << endl;		}					cout << "input modify value: " << endl;			cin >> result;			writeProcess(hProcess, processId, result, resultArray);		}		CloseHandle(hProcess);		system("pause");		return 0;	}	void readProcess(HANDLE hProcess, int processId, int value, int address[]) {		int tmp = 0;		for(int i = 0x10000; i < 500 * 1024 * 1024; i = i + sizeof(DWORD)/sizeof(byte)) {			if(ReadProcessMemory(hProcess, (LPCVOID)i, &tmp, sizeof(DWORD)/sizeof(byte), NULL)) {				if(tmp == value) {					if(arrayLength < arrayMax) {						address[arrayLength] = i;						arrayLength = arrayLength + 1;					}					else {						cout << "read value over " << arrayMax << "from memory." << endl;						break;					}				}			}			else {				if(i % 0x100000 == 0) {					cout << "Read Address: 0x" << hex << i << endl;				}			}		}	}	void siftProcess(HANDLE hProcess, int processId, int siftValue, int address[], int resultArray[]) {		int tmp = 0;		cout << "start sift" << endl;		for(int i = 0; i < arrayLength; i = i + 1) {			//cout << "xxxxxx:   " << hex << address[i] << endl;				if(ReadProcessMemory(hProcess, (LPCVOID)address[i], &tmp, sizeof(DWORD)/sizeof(byte), NULL)) {				if(tmp == siftValue) {					if(resultLength < 10) {						resultArray[resultLength] = address[i];						resultLength = resultLength + 1;					}					else {						cout << "there are still many common value" << endl;					}				}			}		}	}	void writeProcess(HANDLE hProcess, int processId, int result, int resultArray[]) {		for(int i = 0; i < resultLength; i++) {			if(WriteProcessMemory(hProcess, (LPVOID)resultArray[i], &result, sizeof(4),0)) {				cout << "Modify value of 0x" << hex << resultArray[i] << " address." << endl; 			}			else {				cout << "WritProcessMemory Faild" << endl;			}		}		cout << "Finish..." << endl;	}



------------------------------  
References:  

</br>
Author: xx  
Time: 2017.2.3