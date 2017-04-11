#Swift basic 基础内容  

###0x00 简介  
本文是基于 Swift3.0 的，开发环境是 OS X，Xcode8.0  
</br>
以下内容为Swift的基础语法。  

Swift 是一门全新的用于开发 IOS，OS X，WatchOS 应用的编程语言，不过有 C 或者 Object-C 语言的开发基础的话，Swift 的许多地方都会让你感到熟悉的。  

Swift的类型包括整型值的 Int ，浮点数值的 Double 和 Float ，布尔量值的 Bool ，字符串值的 String 。 Swift 三个主要的集合类型，Array ，Set 和 Dictionary 。

Swift增加了元组，元组允许你来创建和传递一组数据。你可以利用元组在一个函数中以单个复合值的形式返回多个值。

Swift 还增加了可选项，用来处理没有值的情况。可选项意味着要么“这里有一个值，它等于 x”要么“这里根本没有值”。可选项也可以用在所有的类型上。他是 Swift 语言中许多重要功能的核心。

###0x01 目录  
1. 常量和变量  
	1.1 声明常量和变量  
	1.2 类型标注  
	1.3 命名常量和变量  
	1.4 输出常量和变量  
2. 注释  
3. 分号  
4. 整数  
	4.1 整数范围  
	4.2 Int  
	4.3 UInt  
5. 浮点数  
6. 类型安全和类型推断  
7. 数值型字面量  
8. 数值类型转换  
	8.1 整数转换  
	8.2 整数和浮点数转换  
9. 类型别名  
10. 布尔值  
11. 元组  
12. 可选项  
	12.1 nil  
	12.2 If 语句以及强制展开  
	12.3 可选项绑定  
	12.4 隐式展开可选项  
13. 错误处理  
14. 断言  
	14.1 使用断言进行调试  
	14.2 什么时候使用断言  

###0x02 正文  
####1. 常量和变量  
常量的值一旦设置好便不能再被更改，然而变量可以在将来被设置为不同的值。  
__1.1 声明常量和变量  __  
声明一个名字为a的常量，值为10
声明一个名字为b的变量，值为5
	
	let a = 10
	var b = 5

__1.2 类型标注__  
你可以在声明一个变量或常量的时候提供类型标注，来明确变量或常量能够储存值的类型。添加类型标注的方法是在变量或常量的名字后边加一个冒号，再跟一个空格，最后加上要使用的类型名称。  

下面的例子是声明一个名字为str，类型为String的变量

	var str: String
	
也可以在声明的时候赋值

	var str: String = "Hello"
	
声明时已经进行类型标注后，就不能放入其他类型的值。  

同时为多个相关的变量为相同的类型，用逗号分隔，只要在最后的变量名字后边加上类型标注。

	var red, blue, green: String

__1.3 命名常量和变量__  
swift 中常量和变量的名字几乎可以使用任何字符，甚至包括 Unicode 字符：

	let π = 3.14159
	let 你好 = "你好世界"
	let 🐶🐮 = "dogcow"	
	
但名字不能包含空白字符、数学符号、箭头、保留的（或者无效的）Unicode 码位、连线和制表符。并且数字不能用做名字开头。

__1.4 输出常量和变量__  

使用 `print(_:separator:terminator:)` 函数来打印当前常量和变量中的值。  
 separator 和 terminator 形式参数有默认值，所以你可以在调用这个函数的时候忽略它们。默认来说，函数通过在行末尾添加换行符来结束输出。要想输出不带换行符的值，那就传一个空的换行符作为结束——比如说， `print(someValue, terminator: "")`  

	var value = 10
	print(value)
	
Swift 使用字符串插值的方式来把常量名或者变量名当做占位符加入到更长的字符串中，然后让 Swift 用常量或变量的当前值替换这些占位符。将常量或变量名放入圆括号中并在括号前使用反斜杠将其转义：

	var apple = 10
	print("The current value of apple is \(apple)")


####2. 注释  
当 Swift 编译器在编译代码的时候会忽略掉你的注释。

单行注释

	//this is annotation
	
多行注释

	/* this is also a comment,
	but written over multiple lines */
	
内嵌注释

	/* 这是第一个多行注释的开头
	/* 这是第二个嵌套在内的注释块 */
	这是第一个注释块的结尾*/


####3. 分号  
Swift 并不要求你在每一句代码结尾写分号（ ; ），当然如果你想写的话也没问题。如果你想在一行里写多句代码，分号还是需要的。

	let cat = "cat"; print(cat)


####4. 整数 
Swift 提供了 8，16，32 和 64 位编码的有符号和无符号整数，这些整数类型的命名方式和 C 相似，例如 8 位无符号整数的类型是 UInt8 ，32 位有符号整数的类型是 Int32 。与 Swift 中的其他类型相同，这些整数类型也用开头大写命名法。
 
__4.1 整数范围__ 
通过 min 和 max 属性来访问每个整数类型的最小值和最大值：

	let minValue = Int8.min
	let maxValue = Int8.max
 
__4.2 Int__  
在32位平台上， Int 的长度和 Int32 相同。  
在64位平台上， Int 的长度和 Int64 相同。

__4.3 UInt__  
在32位平台上， UInt 长度和 UInt32 长度相同。  
在64位平台上， UInt 长度和 UInt64 长度相同。



####5. 浮点数  
Double代表 64 位的浮点数。  
Float 代表 32 位的浮点数。
>注意：Double 有至少 15 位数字的精度，而 Float 的精度只有 6 位。具体使用哪种浮点类型取决于你代码需要处理的值范围。在两种类型都可以的情况下，推荐使用 Double 类型。


####6. 类型安全和类型推断  
Swift 是一门类型安全的语言。类型安全的语言可以让你清楚地知道代码可以处理的值的类型。 
 
当你操作不同类型的值时，类型检查能帮助你避免错误。当然，这并不意味着你得为每一个常量或变量声明一个特定的类型。如果你没有为所需要的值进行类型声明，Swift 会使用类型推断的功能推断出合适的类型。通过检查你给变量赋的值，类型推断能够在编译阶段自动的推断出值的类型。  

如果你给一个新的常量设定一个 42 的字面量，Swift 会推断这个常量的类型是 Int 

	let value = 42
	//value is type Int

如果你没有为一个浮点值的字面量设定类型，Swift 会推断你想创建一个 Double 。(Swift 在推断浮点值的时候始终会选择 Double ,而不是 Float )  

	let pi = 3.14159
	//pi is type Double
	
	
如果你在一个表达式中将整数和浮点数结合起来， Double 会从内容中被推断出来。

	let anotherPi = 3 + 0.14159
	//anotherPi is type Double


####7. 数值型字面量  
整数型字面量可以写作：

一个十进制数，没有前缀  
一个二进制数，前缀是 0b  
一个八进制数，前缀是 0o  
一个十六进制数，前缀是 0x  

下面的这些所有整数字面量的十进制值都是 10 :
	
	let decimal = 10
	let binary = 0b1010
	let octal = 0o12
	let hex = 0xA
	
十进制数与 exp  的指数，结果就等于基数乘以 10exp：

	let a = 1.25e2
	//a = 125
	
十六进制数与 exp 指数，结果就等于基数乘以2exp：

	let b = 0xFp2
	//b = 60
	
整数和浮点数都可以添加额外的零或者添加下划线来增加代码的可读性。下面的这些格式都不会影响字面量的值。

	let a = 1_000_000.000_000_1
	//a = 1000000.0000001


####8. 数值类型转换  
__8.1 整数转换__  
不同整数的类型在变量和常量中存储的数字范围是不同的。 Int8 类型的常量或变量可以存储的数字范围是 -128~127，而 UInt8 类型的常量或者变量能存储的数字范围是 0~255 。如果数字超出了常量或者变量可存储的范围，编译的时候就会报错，因为每个数值类型可存储的值的范围不同，你必须根据不同的情况进行数值类型的转换。

	let tooBig: Int8 = Int8.max + 1
	// Int8 cannot store a number larger than its maximum value
	
类型转换的一个例子，常量 two 的类型是 UInt16 ，而常量 one 的类型是 UInt8 。他们不能直接被相加在一起，因为他们的类型不同。所以，这里让 UInt16 (one) 创建一个新的 UInt16 类型并用 one 的值初始化，这样就可以在原来的地方使用了。

	let two: UInt16 = 2
	let one: UInt8 = 1
	let twoAndOne = two + UInt16(one)

__8.2 整数和浮点数转换__  
整数转化为浮点数必须显示指定类型：

	let one = 1
	let pointOne = 0.14159
	let pi = Double(one) + pointOne

浮点转换为整数也必须显式地指定类型，用浮点数初始化一个新的整数类型的时候，数值会被截断。也就是说 4.75 会变成 4 ， -3.9 会变为 -3 。

	let pi = 3.1415
	let integerPi = Int(pi)
	//integerPi equals 3, and is inferred to be of type Int


####9. 类型别名  
类型别名可以为已经存在的类型定义了一个新的可选名字。用 typealias 关键字定义类型别名。

	typealias abc = Int8
	var number1: abc = 3

	var number2 = abc.min


####10. 布尔值  
Swift 有一个基础的布尔量类型，就是 Bool ，布尔量被作为逻辑值来引用，因为他的值只能是真或者假。Swift为布尔量提供了两个常量值， true 和 false 。

	let oranges = true
	let turnips = false

在 if 判断语句中只能是布尔型的值，布尔类型在这里就很有用了。


####11. 元组  
元组把多个值合并成单一的复合型的值。元组内的值可以是任何类型，而且可以不必是同一类型。  

在下面的示例中，(404, "Not Found") 是一个描述了 HTTP 状态代码的元组。  

	let http404Error = (404, "Not Found")
	// http404Error is of type (Int, String)
	
任何类型的排列都可以被用来创建一个元组，他可以包含任意多的类型。例如 (Int, Int, Int) 或者 (String, Bool) ，实际上，任何类型的组合都是可以的。

可以将一个元组的内容分解成单独的常量或变量，这样你就可以正常的使用它们了：

	let http404Error = (404, "Not Found")
	let (statusCode, statusMessage) = http404Error
	print("The status code is \(statusCode)")
	// prints "The status code is 404"
	print("The status message is \(statusMessage)")
	// prints "The status message is Not Found"
	
当你分解元组的时候，如果只需要使用其中的一部分数据，不需要的数据可以用下滑线（ _ ）代替：

	let http404Error = (404, "Not Found")
	let (statusCode, _) = http404Error
	print("The status code is \(statusCode)")
	// prints "The status code is 404"
	
另外一种方法就是利用从零开始的索引数字访问元组中的单独元素：

	let http404Error = (404, "Not Found")
	print("The status code is \(http404Error.0)")
	// prints "The status code is 404"
	print("The status message is \(http404Error.1)")
	// prints "The status message is Not Found"
	
你可以在定义元组的时候给其中的单个元素命名，在命名之后，你就可以通过访问名字来获取元素的值了：

	let http404Error = (statusCode: 404, statusMessage: "Not Found")
	print("The status code is \(http404Error.statusCode)")
	// prints "The status code is 404"
	print("The status message is \(http404Error.statusMessage)")
	// prints "The status message is Not Found"	

####12. 可选项  
可以利用可选项来处理值可能缺失的情况。可选项意味着：  
这里有一个值，他等于x  
或者 这里根本没有值

__12.1 nil__  
你可以通过给可选变量赋值一个 nil 来将之设置为没有值：

	var errorCode: Int? = 404
	// errorCode contains an actual Int value of 404
	errorCode = nil
	// errorCode now contains no value
	
>nil 不能用于非可选的常量或者变量。  
>在 Swift中， nil 不是指针，他是值缺失的一种特殊类型，任何类型的可选项都可以设置成 nil 而不仅仅是对象类型。

__12.2 If 语句以及强制展开__  
可以利用 if 语句通过比较 nil 来判断一个可选中是否包含值。利用相等运算符 （ == ）和不等运算符（ != ）。

	let number: Int? = 10
	if number != nil {
    	print("number contains some integer value.")
	}
	// prints "number contains some integer value."
	
强制展开：一旦你确定可选中包含值，你可以在可选的名字后面加一个感叹号（!）来获取值，感叹号的意思就是说“我知道这个可选项里边有值，展开吧。”这就是所谓的可选值的强制展开。

	let number: Int? = 10
	if number != nil {
    	print("number contains some integer value of \(number!).")
	}
	// prints "number contains some integer value of 10."
	
>使用 ! 来获取一个不存在的可选值会导致运行错误，在使用!强制展开之前必须确保可选项中包含一个非 nil 的值。

__12.3 可选项绑定__  
可以使用可选项绑定来判断可选项是否包含值，如果包含就把值赋给一个临时的常量或者变量。可选绑定可以与 if 和 while 的语句使用来检查可选项内部的值，并赋值给一个变量或常量。 

	var someOptional: Int? = 10
	if let constantName = someOptional {
    	//statements
	}
若constantName没有从someOptional获取到值，也就是说someOptional为nil，则不会进入语句

__12.4 隐式展开可选项__  
有时在一些程序结构中可选项一旦被设定值之后，就会一直拥有值。在这种情况下，就可以去掉检查的需求，也不必每次访问的时候都进行展开，因为它可以安全的确认每次访问的时候都有一个值。  

这种类型的可选项被定义为隐式展开可选项。通过在声明的类型后边添加一个叹号（ String! ）而非问号（ String? ） 来书写隐式展开可选项。  

	let possibleString: String? = "An optional string."
	let forcedString: String = possibleString! // requires an exclamation mark

	let assumedString: String! = "An implicitly unwrapped optional string."
	let implicitString: String = assumedString // no need for an exclamation mark

你可以像对待普通可选一样对待隐式展开可选项来检查里边是否包含一个值：

	let assumedString: String! = "An implicitly unwrapped optional string."
	if assumedString != nil {
    	print(assumedString)
	}
	// prints "An implicitly unwrapped optional string."
	
你也可以使用隐式展开可选项通过可选项绑定在一句话中检查和展开值：
	
	let assumedString: String! = "An implicitly unwrapped optional string."
	if let definiteString = assumedString {
		print(definiteString)
	}
	// prints "An implicitly unwrapped optional string."
	
>如果你在隐式展开可选项没有值的时候还尝试获取值，会导致运行错误。  
>	

####13. 错误处理  
在程序执行阶段，你可以使用错误处理机制来为错误状况负责。  
当一个函数遇到错误情况，他会抛出一个错误，这个函数的访问者会捕捉到这个错误，并作出合适的反应。  

	func throwAnError() throws {
    	// this function may or may not throw an error
	}
	
通过在函数声明过程当中加入 throws 关键字来表明这个函数会抛出一个错误。当你调用了一个可以抛出错误的函数时，需要在表达式前预置 try 关键字。


####14. 断言  
在某些情况下，如果一些条件无法满足，你的代码很显然就不能再继续执行下去。在这种情况下，你可以通过触发你代码中的断言来结束代码的执行，以提供调试值缺失或者不可用的机会。

__14.1 使用断言进行调试__  
断言会在运行的时候检查一个逻辑条件是否为 true 。顾名思义，断言可以“断言”一个条件是否为真。你可以使用断言确保在运行其他代码之前必要的条件已经被满足。如果条件判断为 true，代码运行会继续进行；如果条件判断为 false，代码运行结束，你的应用也就中止了。  

如果你的代码在调试环境下触发了一个断言，例如你在 Xcode 中创建并运行一个应用，你可以明确的知道不可用的状态发生在什么地方，还能检查断言被触发时你的应用的状态。另外，断言还允许你附加一条调试的信息。  

你可以使用全局函数 assert(\_:\_:)  函数来写断言。向 assert(\_:\_:) 函数传入一个结果为 true 或者 false 的表达式以及一条会在结果为 false 的时候显式的信息：  

	let age = -3
	assert(age >= 0, "A person's age cannot be less than zero")
	// this causes the assertion to trigger, because age is not >= 0
	
以上例子，代码执行只要在 if age >= 0 评定为 true 时才会继续。如果 age 的值是负数，在上文的代码当中， age >= 0 评定为 false ，断言就会被触发，终止应用。

>当你的代码使用最优化编译时断言是失效的，比如在 Xcode 中以默认发布配置编译到app的时候。

__14.2 什么时候使用断言__   
在任何判断条件可能为假但是一定要绝对地为真才能让代码继续执行的时候才使用断言。使用断言的恰当情况包括：  

1.一个整数下标脚本被传入了一个自定义的下标脚本实现，但是下标脚本列表值可能过高或者过低。  
2.给函数传入了一个值，但是一个不合法的值将意味着函数不能完成它的任务。  
3.一个可选值当前为 nil ，但随后的代码就需要非空的值才能成功执行。  


</br></br>

------------------------------------------
参考资料：  
Swift 3 编程语言： <https://www.cnswift.org>  
</br>
Time: 2016.10.9














