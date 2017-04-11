#Python Multithread  

------------------------------  

### 0x00 前言  
介绍在 Python 中的多线程编程。  

### 0x01 目录  

1. Python 多线程简介  
2. thread   
3. threading  
4. 线程同步  


### 0x02 正文  
__1. Python 多线程简介__   
Python 提供两种使用线程的方式： `thread` 函数和用 `threading` 类。`thread` 是低级模块，`threading` 是高级模块，对 `thread` 进行了封装。绝大多数情况下，我们只需要使用 `threading` 这个高级模块。  

>特别注意：在 Python 中，有一个GIL锁：Global Interpreter Lock（全局解释锁），任何Python线程执行前，必须先获得GIL锁，然后，每执行100条字节码，解释器就自动释放GIL锁，让别的线程有机会执行。这个GIL全局锁实际上把所有线程的执行代码都给上了锁，所以，多线程在Python中只能交替执行，即使100个线程跑在100核CPU上，也只能用到1个核。  
所以，对于 CPU密集型的计算，多线程就几乎没有效果；但对于IO密集型的计算，多线程的效果就很明显了。


__2. thread__   
Python 不推荐这种使用方式，这里简单介绍一下：  

举个例子：  

	#coding: utf-8
	import thread
	from time import sleep, ctime

	def loop0():
	    print 'loop0 start at：', ctime()
	    print 'loop0挂起4秒'
	    sleep(4)
	    print 'loop0 done at：', ctime()

	def loop1():
	    print 'loop1 start at：', ctime()
	    print 'loop1挂起2秒'
	    sleep(2)
	    print 'loop1 done at：', ctime()

	print 'main thread start!'
	thread.start_new_thread(loop0, ())
	thread.start_new_thread(loop1, ())
	sleep(6)  #主线程睡眠等待子线程结束
	print 'all done at:', ctime()
	
	#$ python test.py 
	"""
	main thread start!
	loop0 start at： Mon Feb 20 17:09:57 2017
	 loop1 start at： Mon Feb 20 17:09:57 2017
	loop0挂起4秒
	loop1挂起2秒
	loop1 done at： Mon Feb 20 17:09:59 2017
	loop0 done at： Mon Feb 20 17:10:01 2017
	all done at: Mon Feb 20 17:10:03 2017
	"""
	
	

__3. threading__  
使用Threading模块创建线程，直接从threading.Thread继承，然后重写__init__方法和run方法：  

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-

	import threading
	import time

	class myThread (threading.Thread):   #继承父类threading.Thread
	    def __init__(self, name, delay):
	        threading.Thread.__init__(self)
	        self.name = name
	        self.delay = delay 

	    def run(self):                   #把要执行的代码写到run函数里面 线程在创建后会直接运行run函数 
	        print "Starting " + self.name
	        self.print_time(self.name, self.delay, 3)
	        print "Exiting " + self.name

	    def print_time(self, threadName, delay, counter):
	        while counter:
	            time.sleep(delay)
	            print "%s: %s" % (threadName, time.ctime(time.time()))
	            counter -= 1

	# 创建新线程
	thread1 = myThread("Thread-1", 1)
	thread2 = myThread("Thread-2", 2)

	# 开启线程
	thread1.start()
	thread2.start()

	print "Exiting Main Thread"
	
	#$ python test.py 
	"""
	Starting Thread-1Starting Thread-2

	 Exiting Main Thread
	Thread-1: Mon Feb 20 17:25:09 2017
	Thread-2: Mon Feb 20 17:25:10 2017
	Thread-1: Mon Feb 20 17:25:10 2017
	Thread-1: Mon Feb 20 17:25:11 2017
	Thread-2: Mon Feb 20 17:25:12 2017
	Thread-1: Mon Feb 20 17:25:12 2017
	Thread-1: Mon Feb 20 17:25:13 2017
	Exiting Thread-1
	Thread-2: Mon Feb 20 17:25:14 2017
	Thread-2: Mon Feb 20 17:25:16 2017
	Thread-2: Mon Feb 20 17:25:18 2017
	Exiting Thread-2
	"""



__4. 线程同步__  
如果多个线程共同对某个数据修改，则可能出现不可预料的结果，为了保证数据的正确性，需要对多个线程进行同步。  
使用Thread对象的Lock和Rlock可以实现简单的线程同步，这两个对象都有acquire方法和release方法，对于那些需要每次只允许一个线程操作的数据，可以将其操作放到acquire和release方法之间。  

	import threading
	import time
 
	counter = 0
	mutex = threading.Lock()
  
	class MyThread(threading.Thread):
	    def __init__(self):
	        threading.Thread.__init__(self)
               
	    def run(self):
	        global counter, mutex
	        time.sleep(1);
	        if mutex.acquire():
	            counter += 1
	            print "I am %s, set counter:%s" % (self.name, counter)
	            mutex.release()

	for i in range(0, 10):
	    my_thread = MyThread()
	    my_thread.start()
	    
	#$ python test.py
	""" 
	I am Thread-1, set counter:1
	I am Thread-4, set counter:2
	I am Thread-7, set counter:3
	I am Thread-9, set counter:4
	I am Thread-3, set counter:5
	I am Thread-8, set counter:6
	I am Thread-10, set counter:7
	I am Thread-2, set counter:8
	I am Thread-5, set counter:9
	I am Thread-6, set counter:10
	"""




</br>

----------------------------
References:  
菜鸟教程:  <http://www.runoob.com/python/python-tutorial.html>  
廖雪峰的官方网站:  <http://www.liaoxuefeng.com/wiki/0014316089557264a6b348958f449949df42a6d3a2e542c000/00143192823818768cd506abbc94eb5916192364506fa5d000>  
CSDN.穆穆里的专栏 :  <http://blog.csdn.net/whoami021/article/details/21265031?utm_source=tuicool&utm_medium=referral>  
cnblogs.Anka9080 :  <http://www.cnblogs.com/anka9080/p/5276858.html>   
</br>
Author: xx  
Time: 2017.2.20