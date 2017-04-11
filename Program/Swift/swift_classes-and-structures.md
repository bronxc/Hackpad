#Swift classes-and-structures  

###0x00 简介  
作为你程序代码的构建基础，类和结构体是一种多功能且灵活的构造体。通过使用与现存常量、变量、函数完全相同的语法来在类和结构体当中定义属性和方法以添加功能。

不像其他的程序语言，Swift不需要你为自定义类和结构体创建独立的接口和实现文件。在 Swift 中，你在一个文件中定义一个类或者结构体， 则系统将会自动生成面向其他代码的外部接口。

>一个类的实例通常被称为对象。


###0x01 目录  
1. 类与结构体的对比  
	1.1 定义语法  
	1.2 类与结构体实例  
	1.3 访问属性  
	1.4 结构体类型的成员初始化器  
2. 结构体和枚举是值类型  
3. 类是引用类型  
	3.1 特征运算符  
	3.2 指针  
4. 类和结构体之间的选择  
5. 字符串，数组和字典的赋值与拷贝行为  

###0x02 正文
####1. 类与结构体的对比  
在 Swift 中类和结构体有很多共同之处，它们都能：

* 定义属性用来存储值；
* 定义方法用于提供功能；
* 定义下标脚本用来允许使用下标语法访问值；
* 定义初始化器用于初始化状态；
* 可以被扩展来默认所没有的功能；
* 遵循协议来针对特定类型提供标准功能。

类有而结构体没有的额外功能：

* 继承允许一个类继承另一个类的特征;
* 类型转换允许你在运行检查和解释一个类实例的类型；
* 反初始化器允许一个类实例释放任何其所被分配的资源；
* 引用计数允许不止一个对类实例的引用。

>结构体在你的代码中通过复制来传递，并且并不会使用引用计数。

__1.1 定义语法__  
类与结构体有着相似的定义语法，你可以通过使用关键词 class来定义类使用 struct来定义结构体。并在一对大括号内定义它们的具体内容。

	class SomeClass {
		// class definition goes here
	}
	struct SomeStructure {
    	// structure definition goes here
	}

__1.2 类与结构体实例__  
SomeStructure结构体的定义和 SomeClass类的定义仅仅描述了什么是 SomeStructure或 SomeClass。对此，你需要创建一个结构体或类的实例。

	class SomeClass {
    	// class definition goes here
	}
	struct SomeStructure {
    	// structure definition goes here
	}
	var someClass = SomeClass()
	var someStructure = SomeStructure()

__1.3 访问属性__  
你可以用点语法来访问一个实例的属性。在点语法中，你只需在实例名后面书写属性名，用( .)来分开，无需空格：

	struct BookSize {
    	var width: Int = 0
	    var long: Int = 0
	}
	class Book {
    	var bookSize: BookSize = BookSize()
	    var price = 0
    	var page = 0
	}
	var swiftBook = Book()
	print("The swiftBook's price is \(swiftBook.price)")
	//prints "The swiftBook's price is 0"
	
可以用点语法来指定一个新值到一个变量属性中：

	struct BookSize {
    	var width: Int = 0
	    var long: Int = 0
	}
	class Book {
    	var bookSize: BookSize = BookSize()
	    var price = 0
		var page = 0
	}
	var swiftBook = Book()
	swiftBook.price = 20
	//swiftBook.price now is equal to 20
	
>Swift 还允许你直接设置一个结构体属性中的子属性。

__1.4 结构体类型的成员初始化器__  
所有的结构体都有一个自动生成的成员初始化器，你可以使用它来初始化新结构体实例的成员属性。新实例属性的初始化值可以通过属性名称传递到成员初始化器中：

	struct BookSize {
		var width: Int = 0
	    var long: Int = 0
	}
	var bookSize = BookSize(width: 100, long: 200)
	//bookSize.long = 200, bookSize.width = 100
	
>与结构体不同，类实例不会接收默认的成员初始化器。


####2. 结构体和枚举是值类型  
值类型是一种当它被指定到常量或者变量，或者被传递给函数时会被拷贝的类型。

Swift 中所有的基本类型——整数，浮点数，布尔量，字符串，数组和字典——都是值类型，并且都以结构体的形式在后台实现。

Swift 中所有的结构体和枚举都是值类型，这意味着你所创建的任何结构体和枚举实例——和实例作为属性所包含的任意值类型——在代码传递中总是被拷贝的。

举个例子：

	struct BookSize {
    	var width: Int = 0
	    var long: Int = 0
	}
	var bookSize = BookSize(width: 100, long: 200)
	var newBook  = bookSize
	print("bookSize's long is \(bookSize.long)")
	//prints "bookSize's long is 200"
	print("newBook's long is \(newBook.long)")
	prints "newBook's long is 200"

	newBook.long = 400
	print("bookSize's long is \(bookSize.long)")
	prints "bookSize's long is 200"
	print("newBook's long is \(newBook.long)")
	prints "newBook's long is 400"


####3. 类是引用类型  
不同于值类型，在引用类型被赋值到一个常量，变量或者本身被传递到一个函数的时候它是不会被拷贝的。

举个例子：

	class Book {
	    var price = 0
    	var page = 0
	}
	var book = Book()
	book.price = 30
	var newBook = book
	print("book's price is \(book.price)")
	//prints "book's price is 30"
	print("newBook's price is \(newBook.price)")
	//prints "newBook's price is 30"

	newBook.price = 40
	print("book's price is \(book.price)")
	//prints "book's price is 40"
	print("newBook's price is \(newBook.price)")
	//prints "newBook's price is 40"

__3.1 特征运算符__  
因为类是引用类型，在后台有可能有很多常量和变量都是引用到了同一个类的实例。

有时候找出两个常量或者变量是否引用自同一个类实例非常有用，为了允许这样，Swift提供了两个特点运算符：

* 相同于 ( ===)
* 不相同于( !==)

利用这两个恒等运算符来检查两个常量或者变量是否引用相同的实例：

	class Book {
	    var price = 0
    	var page = 0
	}
	var book = Book()
	var newBook = book
	if book === newBook {
    	print("equal")
	}
	//prints "equal"

__3.2 指针__  
一个 Swift 的常量或者变量指向某个实例的引用类型和 C 中的指针类似，但是这并不是直接指向内存地址的指针，也不需要你书写星号(*)来明确你建立了一个引用。相反，这些引用被定义得就像 Swift 中其他常量或者变量一样。


####4. 类和结构体之间的选择  
类和结构体都可以用来定义自定义的数据类型，作为你的程序代码构建块。

总之，结构体实例总是通过值来传递，而类实例总是通过引用来传递。这意味着他们分别适用于不同类型的任务。当你考虑你的工程项目中数据结构和功能的时候，你需要决定把每个数据结构定义成类还是结构体。

按照通用准则，当符合以下一条或多条情形时应考虑创建一个结构体：

* 结构体的主要目的是为了封装一些相关的简单数据值；
* 当你在赋予或者传递结构实例时，有理由需要封装的数据值被拷贝而不是引用；
* 任何存储在结构体中的属性是值类型，也将被拷贝而不是被引用；
* 结构体不需要从一个已存在类型继承属性或者行为。

在其他的情况下，定义一个类，并创建这个类的实例通过引用来管理和传递。事实上，大部分的自定义的数据结构应该是类，而不是结构体。


####5. 字符串，数组和字典的赋值与拷贝行为  
Swift 的 String , Array 和 Dictionary类型是作为结构体来实现的，这意味着字符串，数组和字典在它们被赋值到一个新的常量或者变量，亦或者它们本身被传递到一个函数或方法中的时候，其实是传递了拷贝。

这种行为不同于基础库中的 NSString, NSArray和 NSDictionary，它们是作为类来实现的，而不是结构体。 NSString , NSArray 和 NSDictionary实例总是作为一个已存在实例的引用而不是拷贝来赋值和传递。

>在上述有关字符串，数组和字典“拷贝”的描述中。你在代码中所见到的行为好像总是拷贝。然而在后台 Swift 只有在需要这么做时才会实际去拷贝。Swift 能够管理所有的值的拷贝来确保最佳的性能，所有你也没必要为了保证最佳性能来避免赋值。


</br></br>

-------------------------------------
参考资料：  
Swift 3 编程语言： <https://www.cnswift.org>  
</br>
Time: 2016.10.11
 



















