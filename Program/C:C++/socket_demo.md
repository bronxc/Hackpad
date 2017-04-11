#Socket Demo


###0x01 简介
这是一个socket通讯的简单示例。  


__服务端与客户端__  
服务端与客户端在计算机的世界里，凡是提供服务的一方我们称为服务端（Server），而接受服务的另一方我们称作客户端（Client）。

网站提供网页数据的服务，使用者接受网站所提供的数据服务，所以使用者在这里就是客户端，响应使用者要求的网站即称为服务端。

不过客户端及服务端的关系不见得一定建立在两台分开的机器上，同一台机器中也有这种主从关系的存在，提供服务的服务端及接受服务的客户端也有可能都在同一台机器上。

__Socket__

socket的英文原义是“孔”或“插座”。作为4BDS UNIX的进程通信机制，取后一种意思。通常也称作"套接字"，用于描述IP地址和端口，是一个通信链的句柄。

Scoket程勋分为服务端与客户端，服务端程序监听端口，等待客户端程序的连接。客户端程序发起连接，等待服务端的相应。客户端想要连接上服务端的话，需要 知道服务端的ip地址。

例如，客户想要访问百度网站的首页，通过浏览器访问http://www.baidu.com。浏览器发出请求之后，先是DNS服务器将百度的域名解析成ip地址之后，访问到ip地址为115.239.210.27服务器的80端口（http协议默认在80端口），请求发送后，百度的服务器作为响应将页面的源代码发送至客户端（通过浏览器右键->源代码，或者ctrl+u可以看到服务器返回的页面源代码），随后浏览器将源代码渲染成页面。这样用户就看到了百度网站的首页。

__头文件和库文件__

在windows系统上，当前的Windows Socket接口是Windows Sockets 2，所有接口函数都是有Ws2\_32.dll导出。在进行程序设计时，相关的数据类型、结构定义、函数声明等位于头文件winsock2.h中，编译时需要包含此文件，并且连接到库Ws2\_32.lib。


__常用的socket函数介绍__

* WSAStartup () 函数

WSAStartup函数的功能使加载Ws2\_32.dll等Socket程序运行的环境。在程序初始化后，Socket程序运行所依赖的动态链接库不一定已经在家，WSAStartup保证了Socket 动态链接库的加载。

	int WSAStartup(
		__in WORD wVersionRequested,
		__out LPWSADATA lpWSAData
	); 
参数一 `wVersionRequested`  
Socket程序库的版本，一般使用MAKEWORD(2,2)宏生成。

参数二 `lpWSAData`  
输出参数，指向 WSADATA 结构的指针，用于返回Socket库初始化的信息。

返回值 用来判断程序是否成功加载

* WSACleanup () 函数

与 WSAStartup 相反， WSACleanup 释放Ws2\_32.dll，函数无参数。

* Socket () 函数

Socket函数的功能是建立一个绑定到制定协议和传输类型的Socket。

	SOCKET WSAAPI socket(
		__in int af,
		__in int type,
		__in int protocol
	);
参数一 `af`  
address family的缩写，制定该Socket使用哪一种类型的网络地址。可以是IPv4（AF\_INET），也可以是IPv6（AF\_INET6）、蓝牙（AF\_BTM）、NetBios（AF\_NETBIOS）等。

参数二 `type`  
设置传输类型，常见类型有 SOCK\_STREAM、 SOCK\_DGRAM、 SOCK\_RAM、 SOCK\_SEQPACKET 等。SOCK\_STREAM 类型是基于连接的（TCP），所收的数据时数据流形式的，传输层的数据包已经经过处理。SOCK_DGRAM是基于报文（UDP）。如果制定为SOCK\_RAM，那么可以建立原始套接字，所收到的数据是以数据包（包括包头）的形式存在的。

参数三 `protocol`  
设置传输协议，常用的协议为 IPPROTO\_TCP 和 IPPROTO\_UDP。

* colsesocket() 函数

与 socket 函数对应，用于关闭 socket

	int WSAAPI closesocket(
		 __in SOCKET s
	);
参数一 `s`  
指定要关闭的socket

* sockaddr 和 sockaddr\_in 结构体a

sockaddr、 SOCKADDR、 sockaddr\_in、 SOCKADDR\_IN 这 几个结构用于表示地址很端口。在IPv4下，这几个结构体是可以通用的。

	typedef struct sockaddr {
 
		#if (_WIN32_WINNT < 0x0600)
		    u_short sa_family;
		#else 
		    ADDRESS_FAMILY sa_family; // Address family.
		#endif //(_WIN32_WINNT < 0x0600)
 
	    CHAR sa_data[14]; // Up to 14 bytes of direct address.
	} SOCKADDR, *PSOCKADDR, FAR *LPSOCKADDR;

sockaddr_in:

	typedef struct sockaddr_in {
 
		#if(_WIN32_WINNT < 0x0600)
		    short sin_family; 
		#else //(_WIN32_WINNT < 0x0600)
		    ADDRESS_FAMILY sin_family;
		#endif //(_WIN32_WINNT < 0x0600)
 
	    USHORT sin_port;
	    IN_ADDR sin_addr;
	    CHAR sin_zero[8];
	} SOCKADDR_IN, *PSOCKADDR_IN;

* bind() 函数

服务器端，将Socket与网络地址和端口绑定起来，函数原型如下：

	int WSAAPI bind(
		__in SOCKET s,
		__in_bcount(namelen) const struct sockaddr FAR * name,
		__in int namelen
	);
参数一 `s`  
要绑定的socket

参数二 `name`  
要绑定的网络地址结构体

参数三 `namelen`  
name参数所指向的结构体的大小

* listen() 函数

设置 socket 的状态为监听，使客户端程序可以进行连接，函数原型：

	int WSAAPI listen(
		__in SOCKET s,
		__in int backlog
	);
参数一 `s`  
绑定的socket

参数二 `backlog`  
指定最大并发响应连接数(完成连接过程的队列的最大值)

* accept() 函数

接受客户端的连接

	SOCKET WSAAPI accept(
		__in SOCKET s,
		__out_bcount_opt(*addrlen) struct sockaddr FAR * addr,
		__inout_opt int FAR * addrlen
	);
参数一 `s`  
正在监听的socket，该 socket 使用 listen() 设置。

参数二 `addr` (可选)  
指针，指向一缓冲区，其中接收为通讯层所知的连接实体的地址。Addr参数的实际格式由套接口创建时所产生的地址族确定。

参数三 `addrlen` (可选)  
指针，指向存有addr地址长度的整形数。

返回：成功:非负描述字   失败:-1

>accept 默认会阻塞进程，直到有客户端建立连接后返回，它返回的是连接用的 socket 。如果 accept 成功返回，则服务器与客户已经正确建立连接了，此时服务器通过 accept 返回的 socket 来完成与客户的通信。

* send() 函数

向连接的另一端发送数据，不论是客户还是服务器应用程序都用 send 函数来向 TCP 连接的另一端发送数据。

	int WSAAPI send(
		__in SOCKET s,
		__in_bcount(len) const char FAR * buf,
		__in int len,
		__in int flags
	);
参数一 `s`  
指定发送端socket描述符。

参数二 `*buf`  
指明存放要发送的数据的缓冲区。

参数三 `len`  
指明实际要发送的数据的字节数。

参数四 `flags`  
指明发送的方法，常见宏MSG\_DONTROUTE、MSG\_OOB等，一般置0。
将*buf指向的字符串发送至客户端

* recv() 函数

不论是客户还是服务器应用程序都用 recv 函数 从 TCP 连接的另一端接收数据。

	int WSAAPI recv(
		__in SOCKET s,
		__out_bcount_part(len, return) __out_data_source(NETWORK) char FAR * buf,
		__in int len,
		__in int flags
	);
参数一 `s`  
指定接收端socket描述符；

参数二 `*buf`  
指明一个缓冲区，该缓冲区用来存放recv函数接收到的数据；

参数三 `len`   
指明buf的长度；

参数四 `flags`  
指明接收的方法，常见宏 MSG\_DONTROUTE、 MSG\_OOB 等，一般置0。
获取到客户端返回的字符串并将其写入到buf中




###0x02 代码  

**Server**

	/**	 *Topic:This a Demo for socket,and this is server	 *version:1.0	 *author:xx	 *time:2016.9.12	 */	#include <iostream>	#include "winsock2.h"	#pragma comment(lib, "ws2_32.lib")	using namespace std;	int main(int argc, char* argv[]) {		const int bufSize = 64;		WSADATA	wsaData;	//WSADATA variable		SOCKET sServer;	//Server Socket		SOCKET sClient;	//Client Socket		SOCKADDR_IN addrServ;	//Address of Server		char revBuf[bufSize];	//receive message buffer		char sendBuf[bufSize];	//send message buffer		int retVal;		//run result,return value			//init socket 动态库		if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {			cout << "WSAStartup Failed" << endl;			return -1;		}		/*		 * 确认WinSock DLL支持2.2	  	 * 请注意如果DLL支持的版本大于2.2至2.2
		 * 它仍然会返回wVersion2.2的版本		*/		if(LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 2){	        // 启动错误，程序结束	        WSACleanup(); // 终止Winsock 2 DLL (Ws2_32.dll) 的使用			cout << "This dll version isn't 2.2" << endl;	        return -1;	    }		//create socket		sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);		if(sServer == INVALID_SOCKET) {			cout << "socket Failed" << endl;			WSACleanup();		//release resource of WSAStartup			return -1;		}		//Server socket address		addrServ.sin_family = AF_INET;		//use IPV4		addrServ.sin_port = htons(7777);	//port = 7777		addrServ.sin_addr.s_addr = htonl(INADDR_ANY);		/**		 * 这里INADDR_ANY 表示不确定地址，也就是所有地址；绑定在本机上的任意网卡上.		 * htonl函数将将主机数转换成无符号长整型的网络字节顺序。本函数将一个32位数从主机字节顺序转换成网络字节顺序。		 */		//bind socket		retVal = bind(sServer, (LPSOCKADDR)&addrServ, sizeof(addrServ));		if(retVal == SOCKET_ERROR) {			cout << "bind Failed" << endl;			closesocket(sServer);			WSACleanup();			return -1;		}		//Listen		retVal = listen(sServer, 1);		if(retVal == SOCKET_ERROR) {			cout << "Listen Failed" << endl;			closesocket(sServer);			WSACleanup();			return -1;		}		//accept request from client		sockaddr_in addrClient;		int addrClientLen = sizeof(addrClient);		//accept 会阻塞进程，直到有客户端连接上来为止.		sClient = accept(sServer, (sockaddr FAR*)&addrClient, &addrClientLen);		if(sClient == INVALID_SOCKET) {			cout << "Accept Failed" << endl;			closesocket(sServer);			WSACleanup();			return -1;		}		//accept message form client		while(true) {			ZeroMemory(revBuf, bufSize);			retVal = recv(sClient, revBuf, bufSize, 0);			if(retVal == SOCKET_ERROR) {				cout << "Receive Message Failed" << endl;				closesocket(sServer);				closesocket(sClient);				WSACleanup();			}			if(revBuf[0] == '0') {				break;			}			cout << "Form Client: " << revBuf << endl;			cout << "Send to Client: " << endl;			cin >> sendBuf;			send(sClient, sendBuf, strlen(sendBuf), 0);		}		//quit		closesocket(sServer);		closesocket(sClient);		WSACleanup();		system("pause");		return 0;	}	
**Client**
	/**	 *Topic:This a Demo for socket,and this is client 	 *version:1.0	 *author:xx	 *time:2016.9.13	 */	#include <iostream>	#include "winsock2.h"	#pragma comment(lib, "ws2_32.lib")	using namespace std;	int main(int argc, char* argv[]) {		const int bufSize = 64;		WSADATA wsa;	//WSADATA variable		SOCKET sHost;	//Server socket		SOCKADDR_IN servAddr;	//Address of Server		char sendBuf[bufSize];	//Send Message		char revBuf[bufSize];	//Receive Message		int retVal;				//init Socket variable		if(WSAStartup(MAKEWORD(2,2), &wsa) != 0) {			cout << "WSAStartup Failed" << endl;			return -1;		}		//Create socket		sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);		if(sHost == INVALID_SOCKET) {			cout << "socket Failed" << endl;			WSACleanup();			return -1;		}		//set address of server		servAddr.sin_family = AF_INET;		servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");		servAddr.sin_port = htons(7777);		//link server		int servAddrLen = sizeof(servAddr);		retVal = connect(sHost, (LPSOCKADDR)&servAddr, servAddrLen);		if(retVal == SOCKET_ERROR) {			cout << "connect Failed" << endl;			closesocket(sHost);			WSACleanup();			return -1;		}		//start message		while(true) {			ZeroMemory(sendBuf, bufSize);			cout << "Send to Server: ";			cin >> sendBuf;			retVal = send(sHost, sendBuf, strlen(sendBuf), 0);			if(retVal == SOCKET_ERROR) {				cout << "send Failed" << endl;				closesocket(sHost);				WSACleanup();				return -1;			}			ZeroMemory(revBuf, bufSize);			recv(sHost, revBuf, bufSize, 0);			cout << endl << "Receive Form Server: " << revBuf << endl;		}		//quit		closesocket(sHost);		WSACleanup();		return 0;	}  
	
	
	
</br> 

----------------------------------  
References:  
Lellansin's 冰森:  <http://www.lellansin.com/windows-api-教程（九）-网络编程.html>  
Author:  xx  
Time: 2016.10.15