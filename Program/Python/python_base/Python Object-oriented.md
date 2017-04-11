# Python Object-oriented  

--------------------------------  

### 0x00 前言  
介绍了 Python 中的面向对象操作。

### 0x01 目录  
1. 面向对象技术简介  
2. 类的创建  
3. 访问属性  
4. 类属性和方法的访问控制权限  
5. Python的内置属性  
6. 销毁对象(垃圾回收)  
7. 类的继承  
8. 方法重写  
9. Python中的重载方法  




### 0x02 正文  
__1. 面向对象技术简介__  

* __类(Class)__: 用来描述具有相同的属性和方法的对象的集合。它定义了该集合中每个对象所共有的属性和方法。对象是类的实例。

* __类变量__：类变量在整个实例化的对象中是公用的。类变量定义在类中且在函数体之外。类变量通常不作为实例变量使用。

* __数据成员__：类变量或者实例变量用于处理类及其实例对象的相关的数据。

* __方法重写__：如果从父类继承的方法不能满足子类的需求，可以对其进行改写，这个过程叫方法的覆盖（override），也称为方法的重写。

* __实例变量__：定义在方法中的变量，只作用于当前实例的类。

* __继承__：即一个派生类（derived class）继承基类（base class）的字段和方法。继承也允许把一个派生类的对象作为一个基类对象对待。例如，有这样一个设计：一个Dog类型的对象派生自Animal类，这是模拟"是一个（is-a）"关系（例图，Dog是一个Animal）。

* __实例化__：创建一个类的实例，类的具体对象。

* __方法__：类中定义的函数。

* __对象__：通过类定义的数据结构实例。对象包括两个数据成员（类变量和实例变量）和方法。



__2. 类的创建__  
使用 class 语句来创建一个新类，class 之后为类的名称并以冒号结尾，如下实例:

	class ClassName:
	   '类的帮助信息'   #类文档字符串
	   class_suite  #类体

实例：  

	#! /usr/bin/python
	# coding=utf-8

	class Student:
	    count = 0

	    def __init__(self, name, classes):
	        self.name = name
	        self.classes = classes
	        Student.count += 1

	    def displayCount(self):
	        print "Total Student: %d" % Student.count
	
	    def displayStudent(self):
	        print "Name: ", self.name, "; Classes: ", self.classes
	    
	# 创建一个 Student 类
	stu = Student("root", 2017)

注：

1.  `count` 是一个类变量，它的值将在这个类的所有实例之间共享。你可以在内部类或外部类使用 `Student.count` 访问。  
2. 第一种方法\_\_init\_\_()方法是一种特殊的方法，被称为类的构造函数或初始化方法，当创建了这个类的实例时就会调用该方法。



__3. 访问属性__  
使用点(.)来访问对象的属性。

	#! /usr/bin/python
	# coding=utf-8

	class Student:
	    count = 0

	    def __init__(self, name, classes):
	        self.name = name
	        self.classes = classes
	        Student.count += 1

	    def displayCount(self):
	        print "Total Student: %d" % Student.count

	    def displayStudent(self):
	        print "Name: ", self.name, "; Classes: ", self.classes

	# 创建一个 Student 类
	stu = Student("root", 2017)
	stu2 = Student("aa", 2017)

	# 访问属性和方法 
	stu.displayStudent()
	print "Value of Student.count: ", stu.count
	
	#$ python test.py 
	#Name:  root ; Classes:  2017
	#Value of Student.count:  2

也可以使用以下函数的方式来访问属性：

* getattr(obj, name[, default]) : 访问对象的属性，返回属性的值。
* hasattr(obj,name) : 检查是否存在一个属性，若存在，则返回ture。
* setattr(obj,name,value) : 设置一个属性。如果属性不存在，会创建一个新属性。
* delattr(obj, name) : 删除属性。  

添加一个属性还可以通过这种方式：  

	stu.age = 20	#若不存在，则添加 age 属性
	del stu.age	#删除 age 属性

	

__4. 类的访问控制权限__  
Python中没有访问控制的关键字，例如private、protected等等。但是，在Python编码中，有一些约定来进行访问控制。

__单下划线”\_”__

在Python中，通过单下划线”\_”来实现模块级别的私有化，一般约定以单下划线”\_”开头的变量、函数为模块私有的，也就是说”from moduleName import *”将不会引入以单下划线”\_”开头的变量、函数。

__双下划线”\_\_”__

对于Python中的类属性，可以通过双下划线”\_\_”来实现一定程度的私有化，因为双下划线开头的属性在运行时会被”混淆”（mangling）。

在Student类中，加入了一个”__address”属性：

	class Student(object):
	    def __init__(self, name, age):
	        self.name = name
	        self.age = age
	        self.__address = "Shanghai"

	wilber = Student("Wilber", 28)
	print wilber.__address
	
当通过实例wilber访问这个属性的时候，就会得到一个异常，提示属性”\_\_address”不存在。其实，通过内建函数dir()就可以看到其中的一些原由，”\_\_address”属性在运行时，属性名被改为了”\_Student\_\_address”（属性名前增加了单下划线和类名）  

	class Student(object):
	    def __init__(self, name, age):
	        self.name = name
	        self.age = age
	        self.__address = "Shanghai"
	
	wilber = Student("Wilber", 28)
	print dir(wilber)
	
	#$ Python test.py
	"""
	['_Student__address', '__class__', '__delattr__', '__dict__', '__doc__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', 'age', 'name']
	"""

所以说，即使是双下划线，也没有实现属性的私有化，因为通过下面的方式还是可以直接访问”__address”属性：  

	wilber = Student("Wilber", 28)
	print wilber._Student__address
	
双下划线的另一个重要的目地是，避免子类对父类同名属性的冲突。举个例子：  

	class A(object):
	    def __init__(self):
	        self.__private()
	        self.public()

	    def __private(self):
	        print 'A.__private()'

	    def public(self):
	        print 'A.public()'

	class B(A):
	    def __private(self):
	        print 'B.__private()'
                                                            
	    def public(self):
	        print 'B.public()'

	b = B()
	
	#$ Python test.py
	#A.__private()
	#B.public()
	
当实例化B的时候，由于没有定义\_\_init\_\_函数，将调用父类的\_\_init\_\_，但是由于双下划线的”混淆”效果，”self.\_\_private()”将变成 “self.\_A\_\_private()”。

“\_”和” \_\_”的使用 更多的是一种规范/约定，不没有真正达到限制的目的：

1. “\_”：以单下划线开头的表示的是protected类型的变量，即只能允许其本身与子类进行访问；同时表示弱内部变量标示，如，当使用”from moduleNmae import *”时，不会将以一个下划线开头的对象引入。
2. “\_\_”：双下划线的表示的是私有类型的变量。只能是允许这个类本身进行访问了，连子类也不可以，这类属性在运行时属性名会加上单下划线和类名。
	



__5. Python的内置属性__  
Python 的内置属性： 

* \_\_dict\_\_ : 类的属性（包含一个字典，由类的数据属性组成）
* \_\_doc\_\_ :类的文档字符串
* \_\_name\_\_: 类名
* \_\_module\_\_: 类定义所在的模块（类的全名是'\_\_main\_\_.className'，如果类位于一个导入模块mymod中，那么className.\_\_module\_\_ 等于 mymod）
* \_\_bases\_\_ : 类的所有父类构成元素（包含了一个由所有父类组成的元组）



__6. 销毁对象(垃圾回收)__  
Python 使用了引用计数这一简单技术来跟踪和回收垃圾。  
在 Python 内部记录着所有使用中的对象各有多少引用。  
一个内部跟踪变量，称为一个引用计数器。  
当对象被创建时， 就创建了一个引用计数， 当这个对象不再需要时， 也就是说， 这个对象的引用计数变为0 时， 它被垃圾回收。但是回收不是"立即"的， 由解释器在适当的时机，将垃圾对象占用的内存空间回收。  

	a = 40      # 创建对象  <40>
	b = a       # 增加引用， <40> 的计数
	c = [b]     # 增加引用.  <40> 的计数

	del a       # 减少引用 <40> 的计数
	b = 100     # 减少引用 <40> 的计数
	c[0] = -1   # 减少引用 <40> 的计数
	
垃圾回收机制不仅针对引用计数为0的对象，同样也可以处理循环引用的情况。循环引用指的是，两个对象相互引用，但是没有其他变量引用他们。这种情况下，仅使用引用计数是不够的。Python 的垃圾收集器实际上是一个引用计数器和一个循环垃圾收集器。作为引用计数的补充， 垃圾收集器也会留心被分配的总量很大（及未通过引用计数销毁的那些）的对象。 在这种情况下， 解释器会暂停下来， 试图清理所有未引用的循环。  

举个例子：  

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-

	class Point:
	    def __init__( self, x=0, y=0):
	        self.x = x
	        self.y = y
	    def __del__(self):
	        class_name = self.__class__.__name__
	        print class_name, "销毁"

	pt1 = Point()
	pt2 = pt1
	pt3 = pt1
	print id(pt1), id(pt2), id(pt3) # 打印对象的id
	del pt1
	del pt2
	del pt3
	
	#$ python test.py 
	#4312093688 4312093688 4312093688
	#Point 销毁



__7. 类的继承__  
面向对象的编程带来的主要好处之一是代码的重用，实现这种重用的方法之一是通过继承机制。继承完全可以理解成类之间的类型和子类型关系。

在python中继承中的一些特点：

1. 在继承中基类的构造（\_\_init\_\_()方法）不会被自动调用，它需要在其派生类的构造中亲自专门调用。
2. Python总是首先查找对应类型的方法，如果它不能在派生类中找到对应的方法，它才开始到基类中逐个查找。（先在本类中查找调用的方法，找不到才去基类中找）。

如果在继承元组中列了一个以上的类，那么它就被称作"多重继承" 。

派生类的声明，与他们的父类类似，继承的基类列表跟在类名之后，如下所示：

	class SubClassName (ParentClass1[, ParentClass2, ...]):
	   'Optional class documentation string'
	   class_suite
	   
举个例子:  

	#! /usr/bin/python
	# coding=utf-8

	#define parent class
	class Person:
	    def __init__(self):
	        print "Call Person.__init__()"
	
	    def parentMethod(self):
	        print "Call Person.parentMethod()"

	#define sub class
	class Student(Person):
	    def __init__(self):
	        print "subclass Student.__init__()"

	    def childMethod(self):
	        print "subclass Student.childMethod()"
        
	obj = Student()
	obj.parentMethod()
	obj.childMethod()
	
	#$ python test.py 
	#subclass Student.__init__()
	#Call Person.parentMethod()
	#subclass Student.childMethod()

可以使用issubclass()或者isinstance()方法来检测。

1. issubclass() - 布尔函数判断一个类是另一个类的子类或者子孙类，语法：issubclass(sub,sup)
2. isinstance(obj, Class) 布尔函数如果obj是Class类的实例对象或者是一个Class子类的实例对象则返回true。




__8. 方法重写__  
如果你的父类方法的功能不能满足你的需求，你可以在子类重写你父类的方法：

	#! /usr/bin/python
	# coding=utf-8

	#define parent class
	class Person:
	    def printClass(self):
	        print "parent class: Person"

	#define sub class
	class Student(Person):
	    def printClass(self):
	        print "sub class: Student"
        
	obj = Student()
	obj.printClass()
	
	#$ python test.py 
	#sub class: Student
	


__9. Python中的重载方法__  
首先 python 不提供函数重载： 

函数重载主要是为了解决两个问题。

1. 可变参数类型。
2. 可变参数个数。

另外，一个基本的设计原则是，仅仅当两个函数除了参数类型和参数个数不同以外，其功能是完全相同的，此时才使用函数重载，如果两个函数的功能其实不同，那么不应当使用重载，而应当使用一个名字不同的函数。

那么对于情况 1 ，函数功能相同，但是参数类型不同，python 如何处理？答案是根本不需要处理，因为 python 可以接受任何类型的参数，如果函数的功能相同，那么不同的参数类型在 python 中很可能是相同的代码，没有必要做成两个不同函数。

那么对于情况 2 ，函数功能相同，但参数个数不同，python 如何处理？大家知道，答案就是缺省参数。对那些缺少的参数设定为缺省参数即可解决问题。因为你假设函数功能相同，那么那些缺少的参数终归是需要用的。  

虽然 Python 不提供函数重载，不过对一些 Python 中的特殊方法(专用方法是在特殊情况下或当使用特别语法时由 Python 替你调用的)和运算符是支持重载的： 

可以重载的方法：  

|方法|	重载|	调用|
|--------|-------|-------|
|\_\_init\_\_|	构造函数|	对象建立：X = Class(args)|
|\_\_del\_\_|	析构函数|	X对象收回|
|\_\_add\_\_|	运算符+|	如果没有\_iadd\_,X+Y,X+=Y|
|\_\_or\_\_|	运算符\|(位OR)|	如果没有\_ior\_,X\|Y,X\|=Y|
|\_\_repr\_\_,\_\_str\_\_|	打印、转换|	print（X）、repr(X),str(X)|
|\_\_call\_\_|	函数调用|	X(\*args,\*\*kargs)|
|\_\_getattr\_\_|	点号运算|	X.undefined|
|\_\_setattr\_\_| 	属性赋值语句|	X.any = value|
|\_\_delattr\_\_|	属性删除| 	del X.any|
|\_\_getattribute\_\_|	属性获取|	X.any|
|\_\_getitem\_\_|	索引运算|	X[key],X[i:j],没\_\_iter\_\_时的for循环和其他迭代器|
|\_\_setitem\_\_|	索引赋值语句|	X[key] = value,X[i:j] = sequence|
|\_\_delitem\_\_|	索引和分片删除|	del X[key],del X[i:j]|
|\_\_len\_\_|	长度|	len(X),如果没有\_\_bool\_\_,真值测试|
|\_\_bool\_\_|	布尔测试|	bool(X),真测试|
|\_\_lt\_\_,\_\_gt\_\_,|	特定的比较|	X < Y,X > Y|
|\_\_le\_\_,\_\_ge\_\_,|特定的比较|	 	X<=Y,X >= Y|
|\_\_eq\_\_,\_\_ne\_\_|	相等和不等| 	X == Y,X != Y|
|\_\_radd\_\_|	右侧加法|	Other+X|
|\_\_iadd\_\_|	实地（增强的）加法|	X += Y （or else \_\_add\_\_）|
|\_\_iter\_\_,\_\_next\_\_|	迭代环境|	I = iter(X),next(I)|
|\_\_contains\_\_|	成员关系测试|	item in X （任何可迭代的）|
|\_\_index\_\_|	整数值|	hex(X),bin(X),oct(X),O[X],O[X:]|
|\_\_enter\_\_,\_\_exit\_\_|	环境管理器|	with obj as var:|
|\_\_get\_\_,\_\_set\_\_|	描述符属性|	X.attr,X.attr = value,del X.attr|
|\_\_new\_\_|	创建|	在\_\_init\_\_之前创建对象|

举个例子： 

	# coding=utf-8

	class Number(object):  
	    def __init__(self, value):  
	        self.value = value  
	    # 加重载  
	    def __add__(self, other):  
	        return Number(self.value + other.value)  
	    # 打印重载  
	    def __str__(self):  
	        return 'The value is %d.' % self.value  
	    # 比较重载  
	    def __cmp__(self, other):  
	        return cmp(self.value, other.value)  

	x = Number(1)
	y = Number(2)
	print x + y

	print x > y
	
	
	#$ python test.py 
	#The value is 3.
	#False



</br>

-------------------------------  
References:  
菜鸟教程:  <http://www.runoob.com/python/python-tutorial.html>  
伯乐在线： <http://python.jobbole.com/82297/>  
知乎.pansz： <https://www.zhihu.com/question/20053359>
</br>
Author: xx  
Time: 2017.2.13