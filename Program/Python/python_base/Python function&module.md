# Python function&module  

-------------------------------  

### 0x00 前言  
介绍了 Python 中的函数，模块，文件IO操作，异常处理。

### 0x01 目录  
1. 函数  
	1.1 定义一个函数  
	1.2 按引用传递参数  
	1.3 关键词参数  
	1.4 缺省参数  
	1.5 不定长参数  
	1.6 匿名函数  
	1.7 return 语句  
	1.8 全局变量和局部变量  

2. 模块  
	2.1 import 语句  
	2.2 form ... import 语句  
	2.3 命名空间与作用域  
	2.4 dir 函数  
	2.5 globals 和 locals 函数  
	2.6 reload 函数  
	2.7 包  

3. 文件IO  
	3.1 打印到屏幕  
	3.2 读取键盘输入  
	3.3 File 对象
	3.4 文件操作  
	3.5 文件定位  
	3.6 新建，修改，删除文件  
	3.7 File 方法  

4. 异常处理  
	4.1 异常处理  
	4.2 except 语句  
	4.3 finally 语句  
	4.4 输出异常的内容  
	4.5 手动抛出异常  
	4.6 Python 的标准异常  
	4.7 用户自定义异常类  




### 0x02 正文  
#### 1. 函数  
函数是组织好的，可重复使用的，用来实现单一，或相关联功能的代码段。  
函数能提高应用的模块性，和代码的重复利用率。你已经知道Python提供了许多内建函数，比如print()。但你也可以自己创建函数，这被叫做用户自定义函数。  


__1.1 定义一个函数__  
你可以定义一个由自己想要功能的函数，以下是简单的规则：

* 函数代码块以 def 关键词开头，后接函数标识符名称和圆括号()。
* 任何传入参数和自变量必须放在圆括号中间。圆括号之间可以用于定义参数。
* 函数的第一行语句可以选择性地使用文档字符串—用于存放函数说明。
* 函数内容以冒号起始，并且缩进。
* return [表达式] 结束函数，选择性地返回一个值给调用方。不带表达式的return相当于返回 None。

例子：  

	#!/usr/bin/python
	# coding=utf-8
 
	# 定义函数
	def printme(str):
	    "打印任何传入的字符串"
	    print str
	    return

	# 调用函数
	printme("我要调用用户自定义函数!")
	printme("再次调用同一函数")
	
	#$ python test.py 
	#我要调用用户自定义函数!
	#再次调用同一函数



__1.2 按引用传递参数__  
所有参数（自变量）在Python里都是按引用传递。如果你在函数里修改了参数，那么在调用这个函数的函数里，原始的参数也被改变了。

	#!/usr/bin/python
	# coding=utf-8
 
	# 可写函数说明
	def changeme( mylist ):
	    "修改传入的列表"
	    mylist.append([1,2,3,4]);
	    print "函数内取值: ", mylist
	    return
             
	# 调用changeme函数
	mylist = [10,20,30];
	changeme( mylist );
	print "函数外取值: ", mylist
	
	#$ python test.py 
	#函数内取值:  [10, 20, 30, [1, 2, 3, 4]]
	#函数外取值:  [10, 20, 30, [1, 2, 3, 4]]
	


__1.3 关键词参数__  
普通的参数须以正确的顺序传入函数。调用时的数量必须和声明时的一样。  而关键词允许函数调用时参数的顺序与声明时不一致，因为 Python 解释器能够用参数名匹配参数值。  

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-
 
	def printinfo(name, age):
	    "打印任何传入的字符串"
	    print "Name: ", name
	    print "Age ", age
              
	printinfo(age=5, name="kitty")
	
	#$ python test.py 
	#Name:  kitty
	#Age  5



__1.4 缺省参数__  
调用函数时，缺省参数的值如果没有传入，则被认为是默认值。 

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-
 
	def printinfo(name, age=20):
	    "打印任何传入的字符串"
	    print "Name: ", name
	    print "Age ", age
              
	printinfo(age=5, name="kitty")
	printinfo(name="hello") 
	
	#$ python test.py 
	#Name:  kitty
	#Age  5
	#Name:  hello
	#Age  20	

>默认参数必须放在函数参数列表的最后（相对于非默认值参数）



__1.5 不定长参数__  
有时需要一个函数能处理比当初声明时更多的参数。这些参数叫做不定长参数，和上述2种参数不同，声明时不会命名。基本语法如下：  

	def functionname([formal_args,] [*var_args_tuple,] [**var_args_dictionary]):
	   "函数_文档字符串"
	   function_suite
	   return [expression]

例子： 

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-
 
	def printinfo(var, *varTuple, **varDict):
	    print var
	    print varTuple
	    print varDict

	printinfo(10, 'a', 'b', a=1, b=2)
	
	#$ python test.py 
	#10
	#('a', 'b')
	#{'a': 1, 'b': 2}
	


> 1. 以一个 * 开始的参数，代表一个任意长的元组；
> 2. 以一个 ** 开始的参数，代表一个任意长的字典；
> 3. \* 开始的参数必须在普通参数后面，\*\* 开始的参数必须在普通参数的后面，且要在 \* 开始的参数的后面。



__1.6 匿名函数__  
python 使用 lambda 来创建匿名函数。

* lambda只是一个表达式，函数体比def简单很多。
* lambda的主体是一个表达式，而不是一个代码块。仅仅能在lambda表达式中封装有限的逻辑进去。
* lambda函数拥有自己的命名空间，且不能访问自有参数列表之外或全局命名空间里的参数。
* 虽然lambda函数看起来只能写一行，却不等同于C或C++的内联函数（后者的目的是调用小函数时不占用栈内存从而增加运行效率）。

lambda函数的语法只包含一个语句：  

	lambda [arg1 [,arg2,.....argn]]:expression
	
举个例子：  

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-
 
	# 函数说明
	sum = lambda arg1, arg2: arg1 + arg2
  
	# 调用sum函数
	print "相加后的值为 : ", sum( 10, 20 )
	print "相加后的值为 : ", sum( 20, 20 )
	
	#$ python test.py 
	#相加后的值为 :  30
	#相加后的值为 :  40



__1.7 return 语句__  
return语句表达式退出函数，选择性地向调用方返回一个表达式。不带参数值的return语句返回None。  

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-
 
	# 函数说明
	def sum(arg1, arg2):
	    # 返回2个参数的和."
	    total = arg1 + arg2
	    print "函数内 : ", total
	    return total;
              
	# 调用sum函数
	total = sum( 10, 20 );
	print "函数外 : ", total
	
	#$ python test.py 
	#函数内 :  30
	#函数外 :  30



__1.8 全局变量和局部变量__  
定义在函数内部的变量拥有一个局部作用域，定义在函数外的拥有全局作用域。  
局部变量只能在其被声明的函数内部访问，而全局变量可以在整个程序范围内访问。  

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-

	para1 = 1
	para2 = 2

	# 函数说明
	def change():
	    global para1    #para1 是全局的
	    print "函数内para1 : ", para1
	    para1 = 10
	    print "函数内para1 : ", para1

	    para2 = 20      #para2 是局部的
	    print "函数内para2 : ", para2
              
	# 调用change函数
	change()
	print "函数外para1 : ", para1
	print "函数外para2 : ", para2
	
	#$ python test.py 
	#函数内para1 :  1
	#函数内para1 :  10
	#函数内para2 :  20
	#函数外para1 :  10
	#函数外para2 :  2




#### 2. 模块  
模块让你能够有逻辑地组织你的Python代码段。  
把相关的代码分配到一个 模块里能让你的代码更好用，更易懂。  
模块也是Python对象，具有随机的名字属性用来绑定或引用。  
简单地说，模块就是一个保存了Python代码的文件。模块能定义函数，类和变量。模块里也能包含可执行的代码。  


__2.1 import 语句__  
想使用Python源文件，只需在另一个源文件里执行import语句，语法如下：  

	import module1[, module2[,... moduleN]
	
当解释器遇到import语句，如果模块在当前的搜索路径就会被导入。  

例子：  
首先我们写了一个 support.py 的文件，内容是：  

	def printFunc(par):
	   print "Hello : ", par
	  
然后写一个测试文件 test.py

	#! /usr/bin/python
	# coding=utf-8

	# 导入模块
	import support

	# 调用
	support.printFunc("xx")
	
	#$ python test.py 
	#Hello :  xx
	
>Python解析器对模块位置的搜索顺序  
>1.当前目录。2.如果不在当前目录，Python 则搜索在 shell 变量 PYTHONPATH 下的每个目录。3.如果都找不到，Python会察看默认路径。UNIX下，默认路径一般为/usr/local/lib/python/。



__2.2 form ... import 语句__  
Python的from语句让你从模块中导入一个指定的部分到当前命名空间中。语法如下：  

	from modname import name1[, name2[, ... nameN]]
	
例如使用 `from support import printFunc` ，这个声明不会把整个 support 模块导入到当前的命名空间中，它只会将 support 里的 printFunc 单个引入到执行这个声明的模块的全局符号表。

如果使用 `from support import *`， 可以把一个模块的所有内容全都导入到当前的命名空间，但这种方式不应该过多使用，可能会导致命名冲突。



__2.3 命名空间与作用域__  
(对函数那一章的"全局变量和局部变量"的补充)  

变量是拥有匹配对象的名字（标识符）。命名空间是一个包含了变量名称们（键）和它们各自相应的对象们（值）的字典。  
一个Python表达式可以访问局部命名空间和全局命名空间里的变量。如果一个局部变量和一个全局变量重名，则局部变量会覆盖全局变量。  
每个函数都有自己的命名空间。类的方法的作用域规则和通常函数的一样。  
Python会智能地猜测一个变量是局部的还是全局的，它假设任何在函数内赋值的变量都是局部的。  
因此，如果要给全局变量在一个函数里赋值，必须使用global语句。  


__2.4 dir 函数__  
dir()函数一个排好序的字符串列表，内容是一个模块里定义过的名字。返回的列表容纳了在一个模块里定义的所有模块，变量和函数。

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-
 
	# 导入内置math模块
	import math
  
	content = dir(math)
	print content
	
	#$ python test.py 
	"""['__doc__', '__file__', '__name__', '__package__', 'acos', 'acosh', 'asin', 'asinh', 'atan', 'atan2', 'atanh', 'ceil', 'copysign', 'cos', 'cosh', 'degrees', 'e', 'erf', 'erfc', 'exp', 'expm1', 'fabs', 'factorial', 'floor', 'fmod', 'frexp', 'fsum', 'gamma', 'hypot', 'isinf', 'isnan', 'ldexp', 'lgamma', 'log', 'log10', 'log1p', 'modf', 'pi', 'pow', 'radians', 'sin', 'sinh', 'sqrt', 'tan', 'tanh', 'trunc']"""



__2.5 globals 和 locals 函数__  
根据调用地方的不同，globals()和locals()函数可被用来返回全局和局部命名空间里的名字。  
如果在函数内部调用locals()，返回的是所有能在该函数里访问的命名。  
如果在函数内部调用globals()，返回的是所有在该函数里能访问的全局名字。  
两个函数的返回类型都是字典。所以名字们能用keys()函数摘取。  

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-
 
	para1 = 1
	para2 = 2

	def func():
	    para3 = 1
	    print globals()
	    print locals()

	func()
	
	#$ python test.py 
	"""{'__builtins__': <module '__builtin__' (built-in)>, '__file__': 'test.py', '__package__': None, 'para2': 2, 'para1': 1, 'func': <function func at 0x10f4132a8>, '__name__': '__main__', '__doc__': None}"""
	#{'para3': 1}


__2.6 reload 函数__  
当一个模块被导入到一个脚本，模块顶层部分的代码只会被执行一次。  
因此，如果你想重新执行模块里顶层部分的代码，可以用reload()函数。该函数会重新导入之前导入过的模块。语法如下：  

	reload(module_name)
	
举个例子，先写一个 support.py 模块：  

	print "This is support.py module"

	def hello():
	    print "hello()"
	    
测试文件：  

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-
 
	import support

	support.hello()
	support.hello()

	reload(support)
	
	#$ python test.py 
	#This is support.py module
	#hello()
	#hello()
	#This is support.py module



__2.7 包__  
包是一个分层次的文件目录结构，它定义了一个由模块及子包，和子包下的子包等组成的Python的应用环境。  
在 pack 目录下的support1.py文件, support2.py, support3.py。supprt1.py 文件有如下源代码, 其余两个相似：  

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-
 
	def support1():
	   print "I'm support1.support1 in pack"
	   
现在，在 pack 目录下创建文件 \_\_init\_\_.py：

	from support1 import support1
	from support2 import support2
	from support3 import support3

现在写一个测试文件：  

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-
 
	# 导入 pack 包
	import pack

	pack.support1()
	pack.support2()
	pack.support3()
	
	#$ python test.py 
	#I'm support1.support1 in pack
	#I'm support2.support2 in pack
	#I'm support3.support3 in pack
	



#### 3. 文件IO  
__3.1 打印到屏幕__  
最简单的输出方法是用print语句，你可以给它传递零个或多个用逗号隔开的表达式。此函数把你传递的表达式转换成一个字符串表达式，并将结果写到标准输出如下：  

	#!/usr/bin/python
	# -*- coding: UTF-8 -*- 

	print "Python 是一个非常棒的语言，不是吗？"
	
	#$ python test.py 
	#Python 是一个非常棒的语言，不是吗？
	


__3.2 读取键盘输入__  
Python提供了两个内置函数从标准输入读入一行文本，默认的标准输入是键盘。  

* raw_input
* input

##### raw_input函数
raw_input([prompt]) 函数从标准输入读取一个行，并返回一个字符串（去掉结尾的换行符）：

	#!/usr/bin/python
	# -*- coding: UTF-8 -*- 

	str = raw_input("Please ipnput:  ")
	print str
	
	#$ python test.py 
	#Please ipnput:  hello
	#hello

##### input函数
input([prompt]) 函数和 raw_input([prompt]) 函数基本类似，但是 input 可以接收一个Python表达式作为输入，并将运算结果返回。  

	#!/usr/bin/python
	# -*- coding: UTF-8 -*- 

	str = input("Please ipnput:  ")
	print str
	
	#$ python test.py 
	#Please ipnput:  [x*5 for x in range(2,10,2)]
	#[10, 20, 30, 40]



__3.3 File 对象__  
Python 用 file 对象做大部分的文件操作。  

##### open函数  
必须先用Python内置的open()函数打开一个文件，创建一个file对象，相关的方法才可以调用它进行读写。  

	file object = open(file_name [, access_mode][, buffering])

各个参数的细节如下：

* file\_name：file\_name变量是一个包含了你要访问的文件名称的字符串值。
* access\_mode：access\_mode决定了打开文件的模式：只读，写入，追加等。所有可取值见如下的完全列表。这个参数是非强制的，默认文件访问模式为只读(r)。
* buffering:如果buffering的值被设为0，就不会有寄存。如果buffering的值取1，访问文件时会寄存行。如果将buffering的值设为大于1的整数，表明了这就是的寄存区的缓冲大小。如果取负值，寄存区的缓冲大小则为系统默认。  

打开文件的模式：

|模式|	描述|
|--------|-----------|
|r|	以只读方式打开文件。文件的指针将会放在文件的开头。这是默认模式。|
|rb|	以二进制格式打开一个文件用于只读。文件指针将会放在文件的开头。这是默认模式。|
|r+|	打开一个文件用于读写。文件指针将会放在文件的开头。|
|rb+|	以二进制格式打开一个文件用于读写。文件指针将会放在文件的开头。|
|w|	打开一个文件只用于写入。如果该文件已存在则将其覆盖。如果该文件不存在，创建新文件。|
|wb|	以二进制格式打开一个文件只用于写入。如果该文件已存在则将其覆盖。如果该文件不存在，创建新文件。|
|w+|	打开一个文件用于读写。如果该文件已存在则将其覆盖。如果该文件不存在，创建新文件。|
|wb+|	以二进制格式打开一个文件用于读写。如果该文件已存在则将其覆盖。如果该文件不存在，创建新文件。|
|a|	打开一个文件用于追加。如果该文件已存在，文件指针将会放在文件的结尾。也就是说，新的内容将会被写入到已有内容之后。如果该文件不存在，创建新文件进行写入。|
|ab|	以二进制格式打开一个文件用于追加。如果该文件已存在，文件指针将会放在文件的结尾。也就是说，新的内容将会被写入到已有内容之后。如果该文件不存在，创建新文件进行写入。|
|a+|	打开一个文件用于读写。如果该文件已存在，文件指针将会放在文件的结尾。文件打开时会是追加模式。如果该文件不存在，创建新文件用于读写。|
|ab+|	以二进制格式打开一个文件用于追加。如果该文件已存在，文件指针将会放在文件的结尾。如果该文件不存在，创建新文件用于读写。|


##### File对象的属性
一个文件被打开后，你有一个file对象，你可以得到有关该文件的各种信息。  

|属性|	描述|
|---------|---------|
|file.closed|	返回true如果文件已被关闭，否则返回false。|
|file.mode|	返回被打开文件的访问模式。|
|file.name|	返回文件的名称。|
|file.softspace|	如果用print输出后，必须跟一个空格符，则返回0。否则返回1。|

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-
 
	# 打开一个文件
	fo = open("foo.txt", "wb")
	print "文件名: ", fo.name
	print "是否已关闭 : ", fo.closed
	print "访问模式 : ", fo.mode
	print "末尾是否强制加空格 : ", fo.softspace
	
	#$ python test.py 
	#文件名:  foo.txt
	#是否已关闭 :  False
	#访问模式 :  wb
	#末尾是否强制加空格 :  0



__3.4 文件操作__  
##### close方法
File 对象的 close() 方法刷新缓冲区里任何还没写入的信息，并关闭该文件，这之后便不能再进行写入。  
当一个文件对象的引用被重新指定给另一个文件时，Python 会关闭之前的文件。用 close() 方法关闭文件是一个很好的习惯。语法：  

	fileObject.close()
	
例子：  

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-
 
	# 打开一个文件
	fo = open("foo.txt", "wb")
	print "文件名: ", fo.name
  
	# 关闭打开的文件
	fo.close()
	
	#$ python test.py 
	#文件名:  foo.txt




##### read方法  
read() 方法从一个打开的文件中读取一个字符串。需要重点注意的是，Python字符串可以是二进制数据，而不是仅仅是文字。
语法：

	fileObject.read([count])

在这里，被传递的参数是要从已打开文件中读取的字节计数。该方法从文件的开头开始读入，如果没有传入count，它会尝试尽可能多地读取更多的内容，很可能是直到文件的末尾。  

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-
 
	# Hello,Python. > foo.txt
	# 打开一个文件
	fo = open("foo.txt", "r+")
	str = fo.read(10);
	print "读取的字符串是 : ", str
	# 关闭打开的文件
	fo.close()
	
	#$ python test.py 
	#读取的字符串是 :  Hello,Pyth



##### write方法  
write() 方法可将任何字符串写入一个打开的文件。需要重点注意的是，Python字符串可以是二进制数据，而不是仅仅是文字。  
write() 方法不会在字符串的结尾添加换行符('\n')。语法：

	fileObject.write(string);
	
例子：  
	
	#!/usr/bin/python
	# -*- coding: UTF-8 -*-
 
	# 打开一个文件
	fo = open("foo.txt", "wb")
	fo.write("This is test")

	# 关闭打开的文件
	fo.close()

	#$ python test.py
	#$ cat foo.txt
	#This is test



__3.5 文件定位__  
##### tell() 方法
tell()方法告诉你文件内的当前位置；换句话说，下一次的读写会发生在文件开头这么多字节之后。  

##### seek() 方法
seek（offset [,from]）方法改变当前文件的位置。Offset变量表示要移动的字节数。From变量指定开始移动字节的参考位置。  
如果from被设为0，这意味着将文件的开头作为移动字节的参考位置。如果设为1，则使用当前的位置作为参考位置。如果它被设为2，那么该文件的末尾将作为参考位置。  

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-
 
	# 打开一个文件
	fo = open("foo.txt", "r+")
	str = fo.read(10);
	print "读取的字符串是 : ", str
  
	# 查找当前位置
	position = fo.tell();
	print "当前文件位置 : ", position

	# 把指针再次重新定位到文件开头
	position = fo.seek(0, 0);
	str = fo.read(10);
	print "重新读取字符串 : ", str
	# 关闭打开的文件
	fo.close()
	
	#$ python test.py 
	#读取的字符串是 :  Hello,Pyth
	#当前文件位置 :  10
	#重新读取字符串 :  Hello,Pyth



__3.6 重命名，删除文件及目录__  
以下方法需要导入 os 模块。

##### rename() 方法
使用 rename()方法修改文件名，语法： 

	os.rename(current_file_name, new_file_name)

##### remove() 方法
使用 remove() 方法删除文件，语法：  

	os.remove(file_name)

##### mkdir() 方法
使用 mkdir()方法 在当前目录下创建新的目录，语法： 

	os.mkdir(name)

##### chdir() 方法
使用 chdir() 方法来改变当前的目录，语法： 

	os.chdir(name)
	
>getcwd()方法显示当前的工作目录。

##### rmdir() 方法
使用 rmdir() 方法删除目录，目录名称以参数传递。  
在删除这个目录之前，它的所有内容应该先被清除。语法： 

	os.rmdir(name)

>如果要删除非空的目录，需要遍历文件，然后逐个删除。


__3.7 File 方法__  

|方法|描述|
|-------|-------|
|file.close()|关闭文件。关闭后文件不能再进行读写操作。|
|file.flush()|刷新文件内部缓冲，直接把内部缓冲区的数据立刻写入文件, 而不是被动的等待输出缓冲区写入。|
|file.fileno()|返回一个整型的文件描述符(file descriptor FD 整型), 可以用在如os模块的read方法等一些底层操作上。|
|file.isatty()|如果文件连接到一个终端设备返回 True，否则返回 False。|
|file.next()|返回文件下一行。|
|file.read([size])|从文件读取指定的字节数，如果未给定或为负则读取所有。|
|file.readline([size])|读取整行，包括 "\n" 字符。|
|file.readlines([sizehint])|读取所有行并返回列表，若给定sizeint>0，返回总和大约为sizeint字节的行, 实际读取值可能比sizhint较大, 因为需要填充缓冲区。|
|file.seek(offset[, whence])|设置文件当前位置|
|file.tell()|返回文件当前位置。|
|file.truncate([size])|截取文件，截取的字节通过size指定，默认为当前文件位置。|
|file.write(str)|将字符串写入文件，没有返回值。|
|file.writelines(sequence)|向文件写入一个序列字符串列表，如果需要换行则要自己加入每行的换行符。|




#### 4. 异常处理  
异常即是一个事件，该事件会在程序执行过程中发生，影响了程序的正常执行。  
一般情况下，在Python无法正常处理程序时就会发生一个异常。  
异常是Python对象，表示一个错误。  
当Python脚本发生异常时我们需要捕获处理它，否则程序会终止执行。  

__4.1 异常处理__  
捕捉异常可以使用try/except语句。  
try/except语句用来检测try语句块中的错误，从而让except语句捕获异常信息并处理。  
语法：

	try:
		<statement>        #运行别的代码
	except <exception_name>：
		<statement>        #如果在try部份引发了'exception_name'异常
	except <exception_name>，<parameter>:
		<statement>        #如果引发了'exception_name'异常，获得附加的数据
	else:
		<statement>        #如果没有异常发生

try的工作原理是，当开始一个try语句后，python就在当前程序的上下文中作标记，这样当异常出现时就可以回到这里，try子句先执行，接下来会发生什么依赖于执行时是否出现异常：

* 如果当try后的语句执行时发生异常，python就跳回到try并执行第一个匹配该异常的except子句，异常处理完毕，控制流就通过整个try语句（除非在处理异常时又引发新的异常）。
* 如果在try后的语句里发生了异常，却没有匹配的except子句，异常将被递交到上层的try，或者到程序的最上层（这样将结束程序，并打印缺省的出错信息）。
* 如果在try子句执行时没有发生异常，python将执行else语句后的语句（如果有else的话），然后控制流通过整个try语句。  

举个例子，在当前目录下有一文件 foo.txt，权限为 555

	#!/usr/bin/python

	try:
	    fh = open("foo.txt", "w")
	    fh.write("This is test file")
	except IOError:
	    print "Error: Not found or read failed"
	else:
	    print "write success"
	    fh.close()
	    
	#$ python test.py 
	#Error: Not found or read failed



__4.2 except 语句__  
##### 使用except而不带任何异常类型  
使用不带任何异常类型使用except，将会捕获所有发生的异常。  
（但这不是一个很好的方式，我们不能通过该程序识别出具体的异常信息。）

##### 使用except而带多种异常类型
也可以使用相同的except语句来处理多个异常信息：  

	try:
		正常的操作
	except(Exception1[, Exception2[,...ExceptionN]]]):
	   发生以上多个异常中的一个，执行这块代码
	else:
	   如果没有异常执行这块代码



__4.3 finally 语句__  
finally 语句无论是否发生异常都将执行最后的代码。  

	try:
		<statements>
	catch
		<statements>
	finally:
		<statements>    #无论是否发生异常，都会执行


__4.4 输出异常的内容__  
一个异常可以带上参数，可作为输出的异常信息参数。可以通过except语句来捕获异常的内容，(异常是通过类实现的，这个参数相当于是类的一个实例)语法：  

	try:
	   正常的操作
	except ExceptionType, Argument:
	   你可以在这输出 Argument 的值...
	#或者
	except ExceptionType as Argument:
	
举个例子：  

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-

	# 定义函数
	def temp_convert(var):
	    try:
	        return int(var)
	    except ValueError, Argument:
	        print "参数没有包含数字\n", Argument

	# 调用函数
	temp_convert("xyz");
	
	#$ python test.py 
	#参数没有包含数字
	#invalid literal for int() with base 10: 'xyz'



__4.5 手动抛出异常__  
使用 raise 语句自己触发异常。语法：  

	raise [Exception [, args [, traceback]]]

语句中Exception是异常的类型（例如，NameError）参数是一个异常参数值。该参数是可选的，如果不提供，异常的参数是"None"。  
最后一个参数是可选的（在实践中很少使用），如果存在，是跟踪异常对象。  

举个例子：  

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-

	# 定义函数
	def myException( level ):
	    if level < 1:
	        raise Exception("Invalid level!", level)
	        # 触发异常后，后面的代码就不会再执行

	try:
	    myException(0)                #触发异常
	except "Invalid level!":
	    print "1"
	else:
	    print "2"
	    
	#$ python test.py 
	"""
	Traceback (most recent call last):
	  File "test.py", line 11, in <module>
	    myException(0)                #触发异常
	  File "test.py", line 7, in myException
	    raise Exception("Invalid level!", level)
	Exception: ('Invalid level!', 0)
	"""


__4.6 Python 的标准异常__  

|异常名称|	描述|
|---------|-------|
|BaseException|	所有异常的基类|
|SystemExit|	解释器请求退出|
|KeyboardInterrupt|	用户中断执行(通常是输入^C)|
|Exception|	常规错误的基类|
|StopIteration|	迭代器没有更多的值|
|GeneratorExit|	生成器(generator)发生异常来通知退出|
|StandardError|	所有的内建标准异常的基类|
|ArithmeticError|	所有数值计算错误的基类|
|FloatingPointError|	浮点计算错误|
|OverflowError|	数值运算超出最大限制|
|ZeroDivisionError|	除(或取模)零 (所有数据类型)|
|AssertionError|	断言语句失败|
|AttributeError|	对象没有这个属性|
|EOFError|	没有内建输入,到达EOF 标记|
|EnvironmentError|	操作系统错误的基类|
|IOError|	输入/输出操作失败|
|OSError|	操作系统错误|
|WindowsError|	系统调用失败|
|ImportError|	导入模块/对象失败|
|LookupError|	无效数据查询的基类|
|IndexError|	序列中没有此索引(index)|
|KeyError|	映射中没有这个键|
|MemoryError|	内存溢出错误(对于Python 解释器不是致命的)|
|NameError|	未声明/初始化对象 (没有属性)|
|UnboundLocalError|	访问未初始化的本地变量|
|ReferenceError|	弱引用(Weak reference)试图访问已经垃圾回收了的对象|
|RuntimeError|	一般的运行时错误|
|NotImplementedError|	尚未实现的方法|
|SyntaxError	Python| 语法错误|
|IndentationError|	缩进错误|
|TabError	Tab| 和空格混用|
|SystemError|	一般的解释器系统错误|
|TypeError|	对类型无效的操作|
|ValueError|	传入无效的参数|
|UnicodeError	Unicode| 相关的错误|
|UnicodeDecodeError	Unicode| 解码时的错误|
|UnicodeEncodeError	Unicode| 编码时错误|
|UnicodeTranslateError	Unicode| 转换时错误|
|Warning|	警告的基类|
|DeprecationWarning|	关于被弃用的特征的警告|
|FutureWarning|	关于构造将来语义会有改变的警告|
|OverflowWarning|	旧的关于自动提升为长整型(long)的警告|
|PendingDeprecationWarning|	关于特性将会被废弃的警告|
|RuntimeWarning|	可疑的运行时行为(runtime behavior)的警告|
|SyntaxWarning|	可疑的语法的警告|
|UserWarning|	用户代码生成的警告|



__4.7 用户自定义异常类__ 
通过创建一个新的异常类，程序可以命名它们自己的异常。异常应该是典型的继承自Exception类，通过直接或间接的方式。  

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-

	# 定义异常类
	class OverZero(Exception):
	    def __init__(self, value):
	        Exception.__init__(self)
	        self.value = value

	# 测试
	try:
	    num = 1
	    if(num > 0):
	        raise OverZero(num)
	except OverZero as e:
	    print "catch OverZero Exception. the value is ",e.value
	    
	#$ python test.py 
	#catch OverZero Exception. the value is  1



</br>

-------------------------------  
References:  
菜鸟教程:  <http://www.runoob.com/python/python-tutorial.html>  
</br>
Author: xx  
Time: 2017.1.30