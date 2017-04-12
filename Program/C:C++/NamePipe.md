# NamePipe  

---------------------------  

### 0x00 前言  
“命名管道”又名“命名管线”（Named Pipes），是一种简单的进程间通信（IPC）机制，Microsoft Windows大都提供了对它的支持（但不包括Windows CE）。命名管道可在同一台计算机的不同进程之间或在跨越一个网络的不同计算机的不同进程之间，支持可靠的、单向或双向的数据通信。推荐用命名管道作为进程通信方案的一项重要的原因是它们充分利用了Windows内建的安全特性（ACL等）。

命名管道是一种在进程间通信的方式，但由于它支持网络上的不同计算机的不同进程之间进行通信，而且在通信的过程不占用端口，我们这里可以用它来进行网络间的通信。


### 0x01 命名管道  
__如何使用命名管道__  

1. 创建命名管道：`CreateNamedPipe`
2. 等待客户端连接命名管道：`ConnectNamedPipe`
3. 客户端连接命名管道：`WaitNamedPipe`
4. 客户端打开命名管道：`CreateFile`
5. 读取命名管道内容：`ReadFile`
6. 向命名管道写入内容：`WriteFile`
7. 客户端调用 `CloseHandle` 关闭 CreateFile 打开的管道
8. 服务端调用 `DisconnectNamedPipe` 和 `CloseHandle` 关闭管道

>函数详细使用请到 MSDN 查询。


__降低安全描述符(DACL)权限__  
当使用 `CreateNamePipe` 创建命名管道时，若该函数的最后一个参数 `lpSecurityAttributes` 为0，则windows默认是只支持本地命名管道通信的，不能支持网络的，这里需要设置一下安全描述符的权限。

1. 使用 `InitializeSecurityDescriptor` 初始化一个安全描述符
2. 使用 `SetSecurityDescriptorDacl` 设置权限
3. 将安全描述符属性赋值给 `sa`  


代码： 

	SECURITY_ATTRIBUTES sa;

然后在创建命名管道时，将参数 `lpSecurityAttributes`  设置为 `sa`。


__注意一些限制__

1. 要开启guest账户。(
2. 要关掉防火墙。
3. 组策略-》windows设置-》安全设置-》本地策略-》用户权限分配-》拒绝从网络访问这台计算机；删掉guest用户。
4. 管道路径只能用服务端的计算机名字(域名)不能用IP地址，所以需要手动修改客户端的host文件。


### 0x02 程序 
服务端：  

	/**
	
	
客户端： 

	/**




</br>

----------------------------  
References:  
CSDN.MoreWindows Blog:  <http://blog.csdn.net/morewindows/article/details/8260087>  
CSDN:  <http://bbs.csdn.net/topics/310203566>  
CSDN.viki34的专栏:  <http://blog.csdn.net/viki34/article/details/17955147>  
百度百科:  <http://baike.baidu.com/link?url=esPwgN4cFhgceajtq5Gg_0wCEDLHXufDtVWQSpi8hiWbF-6XUavqXPuHuGrWUSF1xvnGiFCN7_rwqnTjiXrJvuR2Pbrr1Onk5Zc0ub7Fq2qeVbSBfCwZehU4OlHd6yDE>  
</br>
Author: xx  
Time: 2017.2.24