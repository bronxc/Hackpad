# Port Reuse  

---------------------------  

### 0x00 前言  
介绍一下在木马中使用的 __端口重用__ 和 __反弹式连接__。

### 0x01 正文  
#### 1. 反弹式连接  
一般的木马是客户端(控制端)主动连接的服务端(被控端)，但这种情况会被防火墙拦截，所以出现了反弹式连接，即：服务端(被控端)主动连接客户端(控制端)；这样防火墙一般是信任这样的连接的，如果被控端的出口端口用在80端口上，防火墙会认为用户是在浏览网页，除此之外，在局域网内通过NAT上网的用户，也可以通过反弹式连接穿透NAT了。

反弹式连接的方法：通过主页空间上的文件实现的，当客户端想与服务端建立连接时，它首先登录到FTP服务器，写主页空间上面的一个文件，并打开端口监听，等待服务端的连接，服务端定期用HTTP协议读取这个文件的内容，当发现是客户端让自己开始连接时，就主动连接，如此就可完成连接工作。


#### 2. 端口重用  
端口重用是说当一个服务端已经断开连接后，会进入到TIME_WAIT状态，只有等待TIME_WAIT结束后，才能重新使用该端口进行绑定，但通过 setsockopt函数可以立即重用该端口。

__setsockopt 函数__  

	int setsockopt(
	    SOCKET s,
	    int level,
	    int optname,
	    const char *optval,
	    int optlen
	);

* 参数一 `s`   
要改变的目标 Socket  
* 参数二 `level`  
第二个参数为选项的等级，  
* 参数三 `optname`  
设置参数三为 SO_REUSEADDR ，就可以重用已绑定的端口了。  
* 参数四、五 `*optval`, `optlen`  
为指定值的指针和大小。  

MSDN:  <https://msdn.microsoft.com/en-us/library/ms740476(VS.85).aspx>  

SO_REUSEADDR可以用在以下四种情况下。(摘自《Unix网络编程》卷一，即UNPv1)

* 1、当有一个有相同本地地址和端口的socket1处于TIME_WAIT状态时，而你启动的程序的socket2要占用该地址和端口，你的程序就要用到该选项。
* 2、SO_REUSEADDR允许同一port上启动同一服务器的多个实例(多个进程)。但每个实例绑定的IP地址是不能相同的。在有多块网卡或用IP Alias技术的机器可以测试这种情况。
* 3、SO_REUSEADDR允许单个进程绑定相同的端口到多个socket上，但每个socket绑定的ip地址不同。这和2很相似，区别请看UNPv1。
* 4、SO_REUSEADDR允许完全相同的地址和端口的重复绑定。但这只用于UDP的多播，不用于TCP。


### 0x02 程序  

	/**	 * Description: This is "Port Reuse"'s server.	 * Author: xx	 * Time: 2017.2.22	 * Version: 0.1	 */	#include <iostream>	#include "winsock2.h"	#pragma comment(lib, "ws2_32.lib")	using namespace std;	int main(int argc, char* argv[]) {		const int bufSize = 64;		WSADATA wsaData;		SOCKET sServer;		bool value = true;		SOCKET sClient;		SOCKADDR_IN sockServ;		char revBuf[bufSize];		char sendBuf[bufSize];		int retVal = 0;			if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {			cout << "WSAStartup failed" << endl;			system("pause");			return -1;		}		if(LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {			cout << "version isn't 2.2" << endl;			WSACleanup();			system("pause");			return -1;		}		sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);		if(sServer == INVALID_SOCKET) {			cout << "create socket failed" << endl;			WSACleanup();			system("pause");			return -1;		}	//set socket that can reuse		retVal = setsockopt(sServer, SOL_SOCKET, SO_REUSEADDR, (char*)&value, sizeof(value));		if(retVal != 0) {			cout << "setsockopt failed" << endl;			closesocket(sServer);			WSACleanup();			system("pause");			return -1;		}		sockServ.sin_family = AF_INET;		sockServ.sin_port = htons(7777);		sockServ.sin_addr.S_un.S_addr = inet_addr("10.211.55.5");		retVal = bind(sServer, (struct sockaddr *)&sockServ, sizeof(sockServ));		if(retVal == SOCKET_ERROR) {			cout << "bind failed" << endl;			closesocket(sServer);			WSACleanup();			system("pause");			return -1;		}		cout << "Listen......." << endl;		retVal = listen(sServer, 5);		if(retVal == SOCKET_ERROR) {			cout << "listen failed" << endl;			closesocket(sServer);			WSACleanup();			system("pause");			return -1;		}		int addrLen = sizeof(sockServ);		sClient = accept(sServer, (struct sockaddr*)&sockServ, &addrLen);		if(sClient == INVALID_SOCKET) {			cout << "accept failed" << endl;			closesocket(sServer);			WSACleanup();			system("pause");			return -1;		}			cout << "linked" << endl;		send(sClient, "Yeah, This is Server.", 21, 0);			system("pause");		return 0;	}


### winsock的多重绑定
在winsock的实现中，对于服务器的绑定是可以多重绑定的，在确定多重绑定使用谁的时候，根据一条原则是谁的指定最明确则将包递交给谁，而且没有权限之分，也就是说低级权限的用户是可以重绑定在高级权限如服务启动的端口上的,这是非常重大的一个安全隐患。 

这样的话，一个木马绑定到一个已经合法存在的端口上进行端口的隐藏，他通过自己特定的包格式判断是不是自己的包，如果是自己处理，如果不是通过127.0.0.1的地址交给真正的服务器应用进行处理。 从而达到端口隐藏的效果。

解决的方法很简单，在编写如上应用的时候，绑定前需要使用setsockopt指定SO_EXCLUSIVEADDRUSE要求独占所有的端口地址，而不允许复用。这样其它人就无法复用这个端口了。在 bind 的时候会碰到 10013 的错误。


#### 程序

	==


</br>

---------------------------
References:  
sina.\_BruceWong的博客:  <http://blog.sina.com.cn/s/blog_6347780c0102vis7.html>  
Lellansin:  <http://www.lellansin.com/木马，你好！（五）端口重用.html>  
CSDN.The Pursuit Of Heaven:  <http://blog.csdn.net/menghaibin2009/article/details/12514435>  
</br>
Author: xx  
Time: 2017.4.14