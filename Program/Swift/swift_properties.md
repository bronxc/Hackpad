#Swift properties  

###0x00 简介  
属性可以将值与特定的类、结构体或者是枚举联系起来。存储属性会存储常量或变量作为实例的一部分，反之计算属性会计算值。计算属性可以由类、结构体和枚举定义。存储属性只能由类和结构体定义。

存储属性和计算属性通常和特定类型的实例相关联。总之，属性也可以与类型本身相关联。这种属性就是所谓的类型属性。

另外，你也可以定义属性观察器来检查属性中值的变化，这样你就可以用自定义的行为来响应。属性观察器可以被添加到你自己定义的存储属性中，也可以添加到子类从他的父类那里所继承来的属性中。


###0x01 目录   
1. 存储属性  
	1.1 常量结构体实例的存储属性  
	1.2 延迟存储属性  
	1.3 存储属性与实例变量  
2. 计算属性  
	2.1 简写设置器（setter）声明  
	2.2 只读计算属性  
3. 属性观察者  
4. 全局和局部变量  
5. 类型属性  
	5.1 类型属性语法  
	5.2 查询和设置类型属性  


###0x02 正文
####1. 存储属性  
在其最简单的形式下，存储属性是一个作为特定类和结构体实例一部分的常量或变量。存储属性要么是变量存储属性（由 var  关键字引入）要么是常量存储属性（由 let  关键字引入）。

正如默认属性值中所述，你可以为存储属性提供一个默认值作为它定义的一部分。你也可以在初始化的过程中设置和修改存储属性的初始值。正如在初始化中分配常量属性所述，这一点对于常量存储属性也成立。

	struct Range {
    	var firstValue: Int
	    let Length: Int
	}
	var range = Range(firstValue: 10, Length: 20)
	//range values 10,20
	range.firstValue = 5
	//range.firstValue = 5
	
这是由于结构体是值类型。当一个值类型的实例被标记为常量时，该实例的其他属性也均为常量。

对于类来说则不同，它是引用类型。如果你给一个常量赋值引用类型实例，你仍然可以修改那个实例的变量属性。

__1.1 常量结构体实例的存储属性__  
如果你创建了一个结构体的实例并且把这个实例赋给常量，你不能修改这个实例的属性，即使是声明为变量的属性：

	struct Range {
    	var firstValue: Int
	    let Length: Int
	}
	let range = Range(firstValue: 10, Length: 20)
	range.firstValue = 5
	// this will report an error

__1.2 延迟存储属性__  
延迟存储属性的初始值在其第一次使用时才进行计算。你可以通过在其声明前标注 lazy 修饰语来表示一个延迟存储属性。

>你必须把延迟存储属性声明为变量（使用 var 关键字），因为它的初始值可能在实例初始化完成之前无法取得。常量属性则必须在初始化完成之前有值，因此不能声明为延迟。

一个属性的初始值可能依赖于某些外部因素，当这些外部因素的值只有在实例的初始化完成后才能得到时，延迟属性就可以发挥作用了。而当属性的初始值需要执行复杂或代价高昂的配置才能获得，你又想要在需要时才执行，延迟属性就能够派上用场了。

	class DataImporter {
    	var fileName = "Data"
	}
	class DataManager {
    	lazy var importer = DataImporter()
	    var data = [String]()
	}
	let manager = DataManager()
	print(manager.importer.fileName)
	//the importer property has now been created
	//prints "Data"
	
>如果被标记为 lazy 修饰符的属性同时被多个线程访问并且属性还没有被初始化，则无法保证属性只初始化一次。

__1.3 存储属性与实例变量__  
Swift 属性没有与之相对应的实例变量，并且属性的后备存储不能被直接访问。这避免了不同环境中对值的访问的混淆并且将属性的声明简化为一条单一的、限定的语句。所有关于属性的信息——包括它的名字，类型和内存管理特征——都作为类的定义放在了同一个地方。


####2. 计算属性  
除了存储属性，类、结构体和枚举也能够定义计算属性，而它实际并不存储值。相反，他们提供一个读取器和一个可选的设置器来间接得到和设置其他的属性和值。

	struct Point {
    	var x = 0.0, y = 0.0
	}
	struct Size {
    	var width = 0.0, height = 0.0
	}
	struct Rect {
    	var origin = Point()
	    var size = Size()
    	var center: Point {
        	get {
	            let centerX = origin.x + (size.width / 2)
    	        let centerY = origin.y + (size.height / 2)
        	    return Point(x: centerX, y: centerY)
	        }
    	    set(newCenter) {
        	    origin.x = newCenter.x - (size.width / 2)
            	origin.y = newCenter.y - (size.height / 2)
	        }
    	}
	}
	var square = Rect(origin: Point(x: 0.0, y: 0.0),
                  size: Size(width: 10.0, height: 10.0))
	let initialSquareCenter = square.center
	square.center = Point(x: 15.0, y: 15.0)
	print("square.origin is now at (\(square.origin.x), \(square.origin.y))")
	// prints "square.origin is now at (10.0, 10.0)"

__2.1 简写设置器（setter）声明__  
如果一个计算属性的设置器没有为将要被设置的值定义一个名字，那么他将被默认命名为 newValue 。

	struct Point {
    	var x = 0.0, y = 0.0
	}
	struct Size {
    	var width = 0.0, height = 0.0
	}
	struct AlternativeRect {
    	var origin = Point()
	    var size = Size()
    	var center: Point {
        	get {
            	let centerX = origin.x + (size.width / 2)
	            let centerY = origin.y + (size.height / 2)
    	        return Point(x: centerX, y: centerY)
        	}
	        set {
    	        origin.x = newValue.x - (size.width / 2)
        	    origin.y = newValue.y - (size.height / 2)
	        }
    	}
	}

__2.2 只读计算属性__  
一个有读取器但是没有设置器的计算属性就是所谓的只读计算属性。只读计算属性返回一个值，也可以通过点语法访问，但是不能被修改为另一个值。

>你必须用 var 关键字定义计算属性——包括只读计算属性——为变量属性，因为它们的值不是固定的。 let 关键字只用于常量属性，用于明确那些值一旦作为实例初始化就不能更改。

可以通过去掉 get 关键字和他的大扩号来简化只读计算属性的声明：

	struct Cuboid {
    	var width = 0.0, height = 0.0, depth = 0.0
	    var volume: Double {
    	    return width * height * depth
	    }
	}
	

####3. 属性观察者  
属性观察者会观察并对属性值的变化做出回应。每当一个属性的值被设置时，属性观察者都会被调用，即使这个值与该属性当前的值相同。

你可以为你定义的任意存储属性添加属性观察者，除了延迟存储属性。你也可以通过在子类里重写属性来为任何继承属性（无论是存储属性还是计算属性）添加属性观察者。

>你不需要为非重写的计算属性定义属性观察者，因为你可以在计算属性的设置器里直接观察和相应它们值的改变。

可以选择将这些观察者或其中之一定义在属性上：  

* willSet 会在该值被存储之前被调用。  
* didSet 会在一个新值被存储后被调用。  

如果你实现了一个 willSet 观察者，新的属性值会以常量形式参数传递。你可以在你的 willSet 实现中为这个参数定义名字。如果你没有为它命名，那么它会使用默认的名字 newValue 。  

同样，如果你实现了一个 didSet观察者，一个包含旧属性值的常量形式参数将会被传递。你可以为它命名，也可以使用默认的形式参数名 oldValue 。如果你在属性自己的 didSet 观察者里给自己赋值，你赋值的新值就会取代刚刚设置的值。  

>父类属性的 willSet 和 didSet 观察者会在子类初始化器中设置时被调用。它们不会在类的父类初始化器调用中设置其自身属性时被调用。

willSet 和 didSet 的例子：

	class StepCounter {
		var totalSteps: Int = 0 {
        	willSet(newTotalSteps) {
            	print("About to set totalSteps to \(newTotalSteps)")
	        }
    	    didSet {
        	    if totalSteps > oldValue  {
            	    print("Added \(totalSteps - oldValue) steps")
	            }
    	    }
	    }
	}
	let stepCounter = StepCounter()
	stepCounter.totalSteps = 200
	// About to set totalSteps to 200
	// Added 200 steps
	stepCounter.totalSteps = 360
	// About to set totalSteps to 360
	// Added 160 steps
	stepCounter.totalSteps = 896
	// About to set totalSteps to 896
	// Added 536 steps

>如果你以输入输出形式参数传一个拥有观察者的属性给函数， willSet 和 didSet 观察者一定会被调用。这是由于输入输出形式参数的拷贝入拷贝出存储模型导致的：值一定会在函数结束后写回属性。


####4. 全局和局部变量  
上边描述的计算属性和观察属性的能力同样对全局变量和局部变量有效。全局变量是定义在任何函数、方法、闭包或者类型环境之外的变量。局部变量是定义在函数、方法或者闭包环境之中的变量。

>全局敞亮和变量永远是延迟计算的，与延迟存储属性有着相同的行为。不同于延迟存储属性，全局常量和变量不需要标记 lazy 修饰符


####5. 类型属性  
实例属性是属于特定类型实例的属性。每次你创建这个类型的新实例，它就拥有一堆属性值，与其他实例不同。

你同样可以定义属于类型本身的属性，不是这个类型的某一个实例的属性。这个属性只有一个拷贝，无论你创建了多少个类对应的实例。这样的属性叫做类型属性。

类型属性在定义那些对特定类型的所有实例都通用的值的时候很有用，比如实例要使用的常量属性（类似 C 里的静态常量），或者储存对这个类型的所有实例全局可见的值的存储属性（类似 C 里的静态变量）。

存储类型属性可以是变量或者常量。计算类型属性总要被声明为变量属性，与计算实例属性一致。

>不同于存储实例属性，你必须总是给存储类型属性一个默认值。这是因为类型本身不能拥有能够在初始化时给存储类型属性赋值的初始化器。

>存储类型属性是在它们第一次访问时延迟初始化的。它们保证只会初始化一次，就算被多个线程同时访问，他们也不需要使用 lazy 修饰符标记。

__5.1 类型属性语法__  
在 Swift 中，类型属性是写在类型的定义之中的，在类型的花括号里，并且每一个类型属性都显式地放在它支持的类型范围内。

使用 static 关键字来开一类型属性。对于类类型的计算类型属性，你可以使用 class 关键字来允许子类重写父类的实现。下面的例子展示了存储和计算类型属性的语法：

	struct SomeStructure {
    	static var storedTypeProperty = "Some value."
	    static var computedTypeProperty: Int {
    	    return 1
	    }
	}
	enum SomeEnumeration {
    	static var storedTypeProperty = "Some value."
	    static var computedTypeProperty: Int {
    	    return 6
	    }
	}
	class SomeClass {
    	static var storedTypeProperty = "Some value."
	    static var computedTypeProperty: Int {
    	    return 27
	    }
    	class var overrideableComputedTypeProperty: Int {
	        return 107
    	}
	}
	
>上边的计算类型属性示例时对于只读计算类型属性的，但你还是可以使用与计算实例属性相同的语法定义可读写计算类型属性。

__5.2 查询和设置类型属性__  
类型属性使用点语法来查询和设置，与类型属性一致。总之，类型属性在类里查询和设置，而不是这个类型的实例。

	class Fruit {
    	var apple: String = "Apple"
	    var orange: String = "Orange"
	}
	var fruit = Fruit()
	print(fruit.apple)
	fruit.apple = "Banana"
	print(fruit.apple)


</br></br>

-------------------------------------	
参考资料：  
Swift 3 编程语言： <https://www.cnswift.org>  
</br>
Time: 2016.10.11