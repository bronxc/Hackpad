# Python Socket  

--------------------------------  

### 0x00 前言  
介绍 Python 中的网络编程。


### 0x01 目录  

1. Python 的 Socket  
2. socket()函数  
3. 通讯实例  
4. Python Internet模块  



### 0x02 正文  
__1. Python 的 Socket__  
Socket又称"套接字"，应用程序通常通过"套接字"向网络发出请求或者应答网络请求，使主机间或者一台计算机上的进程间可以通讯。  

Python 提供了两个级别访问的网络服务：  

* 低级别的网络服务支持基本的 Socket，它提供了标准的 BSD Sockets API，可以访问底层操作系统Socket接口的全部方法。
* 高级别的网络服务模块 SocketServer， 它提供了服务器中心类，可以简化网络服务器的开发。



__2. socket()函数__  
Python 中，我们用 socket（）函数来创建套接字，语法格式如下：  

	socket.socket([family[, type[, protocol]]]) 
	
参数： 

* family：地址簇  
  socket.AF\_INET IPv4（默认）  
  socket.AF\_INET6 IPv6  
  socket.AF\_UNIX 只能够用于单一的Unix系统进程间通信  
* type：类型  
  socket.SOCK\_STREAM　　流式socket , for TCP （默认）  
  socket.SOCK\_DGRAM　　 数据报式socket , for UDP  
  socket.SOCK\_RAW 		原始套接字，普通的套接字无法处理ICMP、IGMP等网络报文，而SOCK\_RAW可以；其次，SOCK\_RAW也可以处理特殊的IPv4报文；此外，利用原始套接字，可以通过IP\_HDRINCL套接字选项由用户构造IP头。  
  
  socket.SOCK\_RDM	 是一种可靠的UDP形式，即保证交付数据报但不保证顺序。  
  
  SOCK\_RAM	用来提供对原始协议的低级访问，在需要执行某些特殊操作时使用，如发送ICMP报文。SOCK\_RAM通常仅限于高级用户或管理员运行的程序使用。  
  
  socket.SOCK\_SEQPACKET 可靠的连续数据包服务  

* protocol：协议  
  0　　（默认）与特定的地址家族相关的协议,如果是0，则系统就会根据地址格式和套接类别,自动选择一个合适的协议。
 
 
socket的方法：  

|函数|	描述|
|------|------|
|服务器端套接字||
|s.bind()|	绑定地址（host,port）到套接字， 在AF_INET下,以元组（host,port）的形式表示地址。|
|s.listen()|	开始TCP监听。backlog指定在拒绝连接之前，操作系统可以挂起的最大连接数量。该值至少为1，大部分应用程序设为5就可以了。|
|s.accept()|	被动接受TCP客户端连接,(阻塞式)等待连接的到来|
|客户端套接字||
|s.connect()|	主动初始化TCP服务器连接，。一般address的格式为元组（hostname,port），如果连接出错，返回socket.error错误。|
|s.connect_ex()|	connect()函数的扩展版本,出错时返回出错码,而不是抛出异常|
|公共用途的套接字函数||
|s.recv()|	接收TCP数据，数据以字符串形式返回，bufsize指定要接收的最大数据量。flag提供有关消息的其他信息，通常可以忽略。|
|s.send()|	发送TCP数据，将string中的数据发送到连接的套接字。返回值是要发送的字节数量，该数量可能小于string的字节大小。|
|s.sendall()|	完整发送TCP数据，完整发送TCP数据。将string中的数据发送到连接的套接字，但在返回之前会尝试发送所有数据。成功返回None，失败则抛出异常。|
|s.recvform()|	接收UDP数据，与recv()类似，但返回值是（data,address）。其中data是包含接收数据的字符串，address是发送数据的套接字地址。|
|s.sendto()|	发送UDP数据，将数据发送到套接字，address是形式为（ipaddr，port）的元组，指定远程地址。返回值是发送的字节数。|
|s.close()|	关闭套接字|
|s.getpeername()|	返回连接套接字的远程地址。返回值通常是元组（ipaddr,port）。|
|s.getsockname()|	返回套接字自己的地址。通常是一个元组(ipaddr,port)|
|s.setsockopt(level,optname,value)|	设置给定套接字选项的值。|
|s.getsockopt(level,optname[.buflen])|	返回套接字选项的值。|
|s.settimeout(timeout)|	设置套接字操作的超时期，timeout是一个浮点数，单位是秒。值为None表示没有超时期。一般，超时期应该在刚创建套接字时设置，因为它们可能用于连接的操作（如connect()）|
|s.gettimeout()|	返回当前超时期的值，单位是秒，如果没有设置超时期，则返回None。|
|s.fileno()|	返回套接字的文件描述符。|
|s.setblocking(flag)|	如果flag为0，则将套接字设为非阻塞模式，否则将套接字设为阻塞模式（默认值）。非阻塞模式下，如果调用recv()没有发现任何数据，或send()调用无法立即发送数据，那么将引起socket.error异常。|
|s.makefile()|	创建一个与该套接字相关连的文件|



__3. 通讯实例__  
服务端：  

	#! /usr/bin/python
	# coding=utf-8

	import socket       # 导入 socket 模块
	
	s = socket.socket() # 创建 socket 对象
	host = "127.0.0.1"  # 本地监听ip
	port = 7777         # 本地监听端口
	s.bind((host, port))# 绑定端口
	
	s.listen(5)         # 开始监听
	
	client,addr = s.accept()    # 等待客户端连入，阻塞式
	print "The client ip: ", addr
	client.send("Welcome!")     # 发送消息
	client.close()              # 关闭客户端对象
	
	s.close()                   # 关闭服务端对象
	

客户端： 

	#! /usr/bin/python
	# coding=utf-8

	import socket

	s = socket.socket()     # 创建 socket 对象
	host = "127.0.0.1"      # 服务端ip
	port = 7777             # 服务端监听端口

	s.connect((host, port)) # 向服务端发起连接请求
	print s.recv(1024)      # 接受服务端发送的数据
	s.close()               # 关闭 socket 对象

先打开服务端，再打开客户端，可以成功连接。



__4. Python Internet模块__  
以下列出了 Python 网络编程的一些重要模块：  

|协议|	功能用处|	端口号|	Python 模块|
|-----|-------|-------|----------|
|HTTP|	网页访问|	80|	httplib, urllib, xmlrpclib|
|NNTP|	阅读和张贴新闻文章，俗称为"帖子"|	119|nntplib|
|FTP|	文件传输|	20|	ftplib, urllib|
|SMTP|	发送邮件|	25|	smtplib|
|POP3|	接收邮件|	110	|poplib|
|IMAP4|	获取邮件|	143|	imaplib|
|Telnet|	命令行|	23|	telnetlib|
|Gopher|	信息查找|	70|	gopherlib, urllib|




</br>

----------------------------
References:  
菜鸟教程:  <http://www.runoob.com/python/python-tutorial.html>  
cnblogs.zhang_kk:  <http://www.cnblogs.com/zhangkui/p/5655428.html>   
</br>
Author: xx  
Time: 2017.2.21