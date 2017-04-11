# C++ Multithreading  

------------------------------

### 0x00 前言 
C++11标准在标准库中为多线程提供了组件，这意味着使用C++编写与平台无关的多线程程序成为可能，而C++程序的可移植性也得到了有力的保证。  


### 0x01 正文  
C++标准并没有提供对多进程并发的原生支持，所以C++的多进程并发要靠其他API——这需要依赖相关平台。
C++11 标准提供了一个新的线程库，内容包括了管理线程、保护共享数据、线程间的同步操作、低级原子操作等各种类。标准极大地提高了程序的可移植性，以前的多线程依赖于具体的平台，而现在有了统一的接口进行实现。

C++11 新标准中引入了几个头文件来支持多线程编程：

* < thread > :包含std::thread类以及std::this\_thread命名空间。管理线程的函数和类在 中声明.
* < atomic > :包含std::atomic和std::atomic\_flag类，以及一套C风格的原子类型和与C兼容的原子操作的函数。
* < mutex > :包含了与互斥量相关的类以及其他类型和函数
* < future > :包含两个Provider类（std::promise和std::package\_task）和两个Future类（std::future和std::shared\_future）以及相关的类型和函数。
* < condition\_variable > :包含与条件变量相关的类，包括std::condition\_variable和std::condition\_variable\_any。


### 0x02 程序  
__线程的基本使用__  
1. 可会合（joinable）：这种关系下，主线程需要明确执行等待操作，在子线程结束后，主线程的等待操作执行完毕，子线程和主线程会合，这时主线程继续执行等待操作之后的下一步操作。主线程必须会合可会合的子线程。在主线程的线程函数内部调用子线程对象的wait函数实现，即使子线程能够在主线程之前执行完毕，进入终止态，也必须执行会合操作，否则，系统永远不会主动销毁线程，分配给该线程的系统资源也永远不会释放。

	// thread example
	#include <iostream>       // std::cout
	#include <thread>         // std::thread
 
	void foo() 
	{
	  // do stuff...
	  std::cout << "foo" << std::endl;
	}

	void bar(int x)
	{
	  // do stuff...
	  std::cout << "bar" << x << std::endl;
	}

	int main() 
	{
	  std::thread first (foo);     // spawn new thread that calls foo()
	  std::thread second (bar,0);  // spawn new thread that calls bar(0)

	  std::cout << "main, foo and bar now execute concurrently...\n";

	  // synchronize threads:
	  first.join();                // pauses until first finishes
	  second.join();               // pauses until second finishes

	  std::cout << "foo and bar completed.\n";
	  return 0;
	}

2.相分离（detached）：表示子线程无需和主线程会合，也就是相分离的，这种情况下，子线程一旦进入终止状态，这种方式常用在线程数较多的情况下，有时让主线程逐个等待子线程结束，或者让主线程安排每个子线程结束的等待顺序，是很困难或不可能的，所以在并发子线程较多的情况下，这种方式也会经常使用。

	#include <iostream>
	#include <thread>
	#include <unistd.h>
	using namespace std;
 
	void foo() {
	  cout << "foo" << endl;
	}

	void bar(int x) {
	  cout << "bar" << x << endl;
	}

	int main() {
	  thread first (foo);
	  thread second (bar,0);

	  std::cout << "main, foo and bar now execute concurrently...\n";

	  // synchronize threads:
	  first.detach();
	  second.detach();

	  sleep(3);
	  std::cout << "foo and bar completed.\n";

	  return 0;
	}



__互斥量__   
互斥量分为4种：  

1. std::mutex 独占的互斥量，不能递归使用 
2. std::timed\_mutex 带超时的独占的互斥量，不能递归使用 
3. std::recursive\_mutex 递归互斥量，不带超时功能 
4. std::recursive\_timed\_mutex 带超时的递归互斥量

代码：  

	// mutex example
	#include <iostream>
	#include <thread>
	#include <mutex>
	#include <unistd.h>
	using namespace std;

	mutex mtx;
	int count = 1;

	void addBlock() {
	  for(int i = 0; i < 5; i++) {
	    //加锁
	    mtx.lock();
	    cout << count << endl;
	    sleep(1);  //增加掩饰效果
	    count = count + 1;
	    //释放锁
	    mtx.unlock();
	  }
	}

	int main ()
	{
	  std::thread th1 (addBlock);
	  std::thread th2 (addBlock);

	  th1.join();
	  th2.join();

	  return 0;
	}




__原子变量__  
原子变量，为原子操作，不需要加锁 

	std::atomic<T> 
	
代码：  

	// atomic::operator=/operator T example:
	#include <iostream>       // std::cout
	#include <atomic>         // std::atomic
	#include <thread>         // std::thread, std::this_thread::yield
	#include <unistd.h>

	std::atomic<int> foo = {0};

	void addBlock() {
	  for(int i = 0; i < 5; i++) {
	    std::cout << foo << std::endl;
	    sleep(1);
	    foo = foo + 1;
	  }
	}

	int main ()
	{
	  std::thread first (addBlock);
	  std::thread second (addBlock);
	  first.join();
	  second.join();
	  return 0;
	}




</br>

----------------------------- 
References:  
cnblogs.256code生活与技术:  <http://www.cnblogs.com/haippy/p/3235560.html>  
C++ Reference:  <http://www.cplusplus.com/reference/>   
CSDN.IT小小鸟～～:  <http://blog.csdn.net/wwh578867817/article/details/46919703>  
CSDN.GyafdxIs的专栏:  <http://blog.csdn.net/gyafdxis/article/details/49620809>  
</br>
Author: xx  
Time: 2017.2.24