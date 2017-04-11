# Python Process control  

-------------------------------

### 0x00 前言  
本文介绍了 Python 中的流程控制语句。


### 0x01 目录  
1. if条件语句  
2. while循环语句  
3. for 循环语句  
4. 循环嵌套
5. pass语句


### 0x02 正文  
__1. if条件语句__  
Python条件语句是通过一条或多条语句的执行结果（True或者False）来决定执行的代码块。    
Python程序语言指定任何非0和非空（null）值为true，0 或者 null为false。  

Python 编程中 if 语句用于控制程序的执行，基本形式为：  

	if 判断条件：
	    执行语句……
	else：
	    执行语句……
	    
其中"判断条件"成立时（非零），则执行后面的语句，而执行内容可以多行，以缩进来区分表示同一范围。  
else 为可选语句，当需要在条件不成立时执行内容则可以执行相关语句，例子：  

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-

	flag = False
	name = 'xx'
	if name == 'python':         # 判断变量否为'python'
	    flag = True          # 条件成立时设置标志为真
	    print 'welcome boss'    # 并输出欢迎信息
	else:
	    print name              # 条件不成立时输出变量名称
	    
	#$ python test.py 
	#xx
	
由于 python 并不支持 switch 语句，所以多个条件判断，只能用 elif 来实现：  

	if 判断条件1:
	    执行语句1……
	elif 判断条件2:
	    执行语句2……
	elif 判断条件3:
	    执行语句3……
	else:
	    执行语句4……
	    
如果判断需要多个条件需同时判断时，可以使用 or （或），表示两个条件有一个成立时判断条件成功；使用 and （与）时，表示只有两个条件同时成立的情况下，判断条件才成功。  

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-

	num = 9
	if num >= 0 and num <= 10:    # 判断值是否在0~10之间
	    print 'hello'
	    
	#$ python test.py 
	#hello

>注: 当if有多个条件时可使用括号来区分判断的先后顺序，括号中的判断优先执行，此外 and 和 or 的优先级低于>（大于）、<（小于）等判断符号，即大于和小于在没有括号的情况下会比与或要优先判断。


__2. while循环语句__  
Python 编程中 while 语句用于循环执行程序，即在某条件下，循环执行某段程序，以处理需要重复处理的相同任务。  
执行语句可以是单个语句或语句块。判断条件可以是任何表达式，任何非零、或非空（null）的值均为true。 当判断条件假false时，循环结束。

	while 判断条件：
	    执行语句……

举个例子：  

	#!/usr/bin/python

	count = 0
	while (count < 9):
	    print 'The count is:', count
	    count = count + 1

	print "Good bye!"
	
	“”“
	$ python test.py 
	The count is: 0
	The count is: 1
	The count is: 2
	The count is: 3
	The count is: 4
	The count is: 5
	The count is: 6
	The count is: 7
	The count is: 8
	Good bye!
	“”“

循环语句中还有另外两个重要的命令 continue，break 来跳过循环，continue 用于跳过该次循环，break 则是用于退出循环。

	#!/usr/bin/python
	# coding=utf-8

	i = 1
	while i < 10:   
	    i += 1
	    if i%2 > 0:     # 非双数时跳过输出
	        continue
	    print i         # 输出双数2、4、6、8、10

	i = 1
	while 1:            # 循环条件为1必定成立
	    print i         # 输出1~10
	    i += 1
	    if i > 10:     # 当i大于10时跳出循环
	        break
	
循环使用 else 语句  
在 python 中，while … else 表示这样的意思，while 中的语句和普通的没有区别，else 中的语句会在循环正常执行完（即 while 不是通过 break 跳出而中断的）的情况下执行，for … else 也是一样。

	#!/usr/bin/python

	count = 0
	while count < 10:
	    print count
	    count = count + 1
	    if count == 3:
	        break
	else:
	    print "Complete traversal"
	    
	#$ python test.py 
	#0
	#1
	#2



__3. for 循环语句__  
Python for循环可以遍历任何序列的项目，如一个列表或者一个字符串。  

	for iterating_var in sequence:
	   statements(s)
	 
举个例子： 

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-
 
	for letter in 'Python':     # 第一个实例
	    print 'current letter: ', letter
	     
	fruits = ['banana', 'apple',  'mango']
	for fruit in fruits:        # 第二个实例
	    print 'current: ', fruit
	    
	#$ python test.py 
	#current letter:  P
	#current letter:  y
	#current letter:  t
	#current letter:  h
	#current letter:  o
	#current letter:  n
	#current:  banana
	#current:  apple
	#current:  mango

也可以通过索引进行访问：  

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-
 
	fruits = ['banana', 'apple',  'mango']
	for index in range(3):
	    print index
	    print 'current: ', fruits[index]
	    
	#$ python test.py 
	#0
	#current:  banana
	#1
	#current:  apple
	#2
	#current:  mango




__4. 循环嵌套__  
循环可以进行嵌套，以下实例使用了嵌套循环输出2~100之间的素数：  

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-

	i = 2
	while(i < 100):
	    j = 2
	    while(j <= (i/j)):
	        if not(i%j): break
	        j = j + 1
	    if (j > i/j) : print i, " 是素数"
	    i = i + 1



__5. pass语句__    
Python pass是空语句，是为了保持程序结构的完整性。  
pass 不做任何事情，一般用做占位语句。  

举个例子：  

	#!/usr/bin/python
	# -*- coding: UTF-8 -*- 

	# 输出 Python 的每个字母
	for letter in 'Python':
	    if letter == 'h':
	        pass
	        print '这是 pass 块'
	    print '当前字母 :', letter
	    
	#$ python test.py 
	#当前字母 : P
	#当前字母 : y
	#当前字母 : t
	#这是 pass 块
	#当前字母 : h
	#当前字母 : o
	#当前字母 : n





</br>

-------------------------------  
References:  
菜鸟教程:  <http://www.runoob.com/python/python-tutorial.html>  

</br>
Author: xx  
Time: 2017.1.19 