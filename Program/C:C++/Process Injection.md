# Process Injection  

------------------------------  

### 0x00 前言  
进程注入是指：让一个线程在别的进程中执行。  

利用 DLL 文件，在 DLL 文件第一次被装载进进程时，会执行 DllMain 中的 DLL\_PROCESS\_ATTACH 下的代码。  

进程注入的优点是：  

1. 需要插入到远程进程的内存空间是通过virtualAllocEx这样的函数分配的，只存在于内存中，如果不是内存查杀，很难发现。
2. 可以复用宿主进程的名称、端口，更加隐蔽  



### 0x01 进程注入流程    
进程注入的流程：  

1. 将系统权限提升到Debug模式，因为只有debug模式才能打开远程进程的handle。(`EnableDebugPrivilege`)
2. 打开远程进程。(`OpenProcess`)
3. 将 DLL 文件的路径分配到目标内容空间中。(`VirtualAllocEx`)
4. 将DLL文件内容写入到远程进程。(`WriteProcessMemory`)
5. 在宿主进程中启动新线程完成插入。(`CreateRemoteThread`)


>上面提到的函数到 MSDN 查看详细的使用方法。


### 0x02 程序  
恶意的 DLL 文件代码： 
`DllHeader.h`:  

	#ifndef dllDemoHeader
	
`Main`:  

	#include <windows.h>




进程插入代码： 

	/**




</br> 

-------------------------------
References: 
cnblogs.茄子写字板:  <http://www.cnblogs.com/handt/archive/2012/08/09/2627277.html>  
淡泊明志，宁静致远:  <http://andylin02.iteye.com/blog/459483>  
</br>
Author: xx  
Time: 2017.2.22