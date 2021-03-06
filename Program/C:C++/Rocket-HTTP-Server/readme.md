# Rocket HTTP Server  

------------------------------------  

### 0x00前言  
额，一个学习用的 HTTP 服务器，取了个sb的名字，，，哈哈哈哈。。

### 0x01正文 
实现什么的直接看代码吧，这里说下思路和一些优化的方式。  

在 Tinyhttpd 的基础上，添加了 cookie 生成的部分，log记录的功能，并使用线程池提高了并发。

__1.思路:__  
网络处理部分：

1. 建立一个初始化线程池
2. 建立socket监听端口
3. 利用阻塞型 accept 接受用户的连接
4. 使用方法将新连接作为一个任务传入到线程池中，线程进行任务处理
5. 读取用户的请求头，将需要的内容(目前仅提取method, path, version, host, cookie, parameters)封装成结构体
6. 当请求方法支持并且服务器文件存在时，开始处理用户请求
7. 判断服务器文件是否具有可执行权限，若可执行则进入CGI解析分支，否则读取普通的HTML页面
8. 普通页面读取就是文件操作，CGI解析是fork一个新进程，利用匿名管道进行进程间通信，将CGI的执行结果作为响应包的内容
9. 当服务器处理完成后，返回响应包

线程池部分：

1. 建立一个初始化线程池
2. 当新连接来到时，作为一个任务加入到线程池中
3. 加入到线程池中后，唤醒一个等待线程进行处理
4. 线程执行完毕后，继续阻塞等待任务
5. 有一个管理线程，进行线程池的管理，当任务队列中的任务数大于当前存活线程数时，创建新的线程到线程池中；当忙线程*2小于当前存活线程数时，销毁一些线程
6. 附录：在 httpd 运行过程中，有三类线程：1.主线程(main)：进行accept处理，2.管理线程：进行线程池的管理，3.工作线程：进行任务的执行

__2.一些建议:__  

1. 大部分的请求头还没有处理。
2. 请求头和响应头可以修改为变长结构体。(因为请求头和相应头中的字段个数和字段长度都不确定) 
3. 可将网络IO优化成 epoll 的多路IO复用，极大的提高效率。

__3.文件结构:__  
`rocket.h`: 一些公用的头文件和预定义  
`Rocket.c`: 程序的入口，main函数  
`rocketSocket.h`: 程序Socket处理相关内容的头文件，预定义，结构体和函数声明  
`rocketSocket.c`: 上面这个文件的实现  
`rocketThread.h`: 程序线程池处理相关内容的头文件，预定义，结构体和函数声明  
`rocketThread.c`: 上面这个文件的实现  
`www/`: 存放网页文件夹  
`logs/`: 存放log记录的文件夹  
`makefile`: 编译 httpd 可执行文件  
`readme.md`: 一些简介  

__4.Suggestion:__  
0x7fancyxx@gmail.com

</br>

-----------------------------------
References:  
Tinyhttpd源码

Author: xx  
Time: 2017.5.8
