#Swift collection-types  

###0x00 简介  
Swift 提供了三种主要的集合类型，所谓的数组、合集还有字典，用来储存值的集合。数组是有序的值的集合。合集是唯一值的无序集合。字典是无序的键值对集合。

>Swift 的数组、合集和字典是以泛型集合实现的。要了解更多关于泛型类型和集合


###0x01 目录  
1. 集合的可变性  
2. 数组  
	2.1 数组类型缩写语法  
	2.2 创建一个空数组  
	2.3 使用默认值创建数组  
	2.4 通过连接两个数组来创建数组  
	2.5 使用数组字面量创建数组  
	2.6 访问和修改数组  
	2.7 遍历一个数组  
3. 集合Set 
	3.1 Set 类型的哈希值  
	3.2 集合Set类型语法  
	3.3 创建并初始化一个空集合Set  
	3.4 使用数组字面量创建集合Set  
	3.5 访问和修改集合Set  
	3.6 遍历集合Set  
4. 执行集合Set操作  
	4.1 基本集合Set操作  
	4.2 集合Set成员关系和相等性  
5. 字典  
	5.1 字典类型简写语法  
	5.2 创建一个空字典  
	5.3 用字典字面量创建字典  
	5.4 访问和修改字典  
	5.5 遍历字典  

###0x02 正文
####1. 集合的可变性  
如果你创建一个数组、合集或者一个字典，并且赋值给一个变量，那么创建的集合就是可变的。这意味着你随后可以通过添加、移除、或者改变集合中的元素来改变（或者说异变）集合。如果你把数组、合集或者字典赋值给一个常量，则集合就成了不可变的，它的大小和内容都不能被改变。

>在集合不需要改变的情况下创建不可变集合是个不错的选择。这样做可以允许 Swift 编译器优化你创建的集合的性能。


####2. 数组  
数组以有序的方式来储存相同类型的值。相同类型的值可以在数组的不同地方多次出现。

>Swift 的 Array类型被桥接到了基础框架的 NSArray类上。

__2.1 数组类型缩写语法__  
Swift 数组的类型完整写法是 Array<Element>， Element是数组允许存入的值的类型。你同样可以缩写数组的类型为 [Element]。

__2.2 创建一个空数组__   
你可以使用确定类型通过初始化器语法来创建一个空数组：

	var arr = Array<Int>()
	//var arr = [Int]()     //simplify
	print("someInts is of type [Int] with \(arr.count) items.")
	//someInts is of type [Int] with 0 items.
	
如果内容已经提供了类型信息，比如说作为函数的实际参数或者已经分类了的变量或常量，你可以通过空数组字面量来创建一个空数组，它写作[ ]（一对空方括号）：

	var arr = Array<Int>()
	arr.append(3)
	//contains 1 value of type Int
	arr = []
	//arr is now an empty array, but is still of type [Int]

__2.3 使用默认值创建数组__  
Swift 的 Array类型提供了初始化器来创建确定大小且元素都设定为相同默认值的数组。你可以传给初始化器对应类型的默认值（叫做 repeating）和新数组元素的数量（叫做 count）：

	var threeDoubles = Array<Double>(repeating: 0.0, count: 3)
	// threeDoubles is of type [Double], and equals [0.0, 0.0, 0.0]

__2.4 通过连接两个数组来创建数组__  
你可以通过把两个兼容类型的现存数组用加运算符（ +）加在一起来创建一个新数组。新数组的类型将从你相加的数组里推断出来：

	var threeDoubles = Array<Double>(repeating: 0.0, count: 3)
	var anotherThreeDoubles = Array(repeating: 2.5, count: 3)

	var sixDoubles = threeDoubles + anotherThreeDoubles
	// sixDoubles is inferred as [Double], and equals [0.0, 0.0, 0.0, 2.5, 2.5, 2.5]

__2.5 使用数组字面量创建数组__  
可以使用数组字面量来初始化一个数组，它是一种以数组集合来写一个或者多个值的简写方式。数组字面量写做一系列的值，用逗号分隔，用方括号括起来：`[value 1, value 2, value 3]`

	var someList: [String] = ["Eggs", "Milk"]
	// someList has been initialized with two initial items
	//var someList = ["Eggs", "Milk"]     //simplify, swift infer someList to be type of String

__2.6 访问和修改数组__  
可以通过数组的方法和属性来修改数组，或者使用下标脚本语法。

要得出数组中元素的数量，检查只读的 count属性：

	var someList: [String] = ["Eggs", "Milk"]
	print("The someList contains \(someList.count) items.")
	// prints "The someList contains 2 items."
	
使用布尔量 isEmpty属性来作为检查 count属性是否等于 0的快捷方式：

	var someList: [String] = ["Eggs", "Milk"]
	if !someList.isEmpty {
    	print("The someList is empty.")
	}
	
可以通过 append(_:)方法给数组末尾添加新的元素：

	var someList: [String] = ["Eggs", "Milk"]
	someList.append("Flour")

还可以使用加赋值运算符 ( +=)来在数组末尾添加一个或者多个同类型元素：

	var someList: [String] = ["Eggs", "Milk", "Flour"]
	someList += ["aa"]
	//now contains 4 items
	someList += ["bb", "cc"]
	//now contains 6 items
	
通过下标脚本语法来从数组当中取回一个值，在紧跟数组名后的方括号内传入你想要取回的值的索引：

	var someList: [String] = ["Eggs", "Milk", "Flour", "aa", "bb", "cc"]
	var firstItem = someList[0]
	//firstItem = "Eggs"
	
使用下标脚本语法来改变给定索引中已经存在的值：

	var someList: [String] = ["Eggs", "Milk", "Flour", "aa", "bb", "cc"]
	someList[0] = "newEggs"
	//now someList[0] is equal to "newEggs"
	
同样可以使用下标脚本语法来一次改变一个范围的值，就算替换与范围长度不同的值的合集也行：

	var someList: [String] = ["Eggs", "Milk", "Flour", "aa", "bb", "cc"]
	someList[3...5] = ["new", "what"]
	//now someList is ["Eggs", "Milk", "Flour", "new", "what"]
	
把元素插入到特定的索引位置，调用数组的 insert(_:at:)方法：

	var someList: [String] = ["Eggs", "Milk", "Flour"]
	someList.insert("insert", at: 0)
	//now someList is ["insert", "Eggs", "Milk", "Flour"]

>你不能用下标脚本语法来追加一个新元素到数组的末尾。

使用 remove(at:)方法来移除一个元素。这个方法移除特定索引的元素并且返回它（尽管你不需要的话可以无视返回的值）：

	var someList: [String] = ["Eggs", "Milk", "Flour"]
	someList.remove(at: 0)
	//now someList is ["Milk", "Flour"]
	
>当数组中元素被移除，任何留下的空白都会被封闭，所以上面代码中索引 0 的值再一次等于 "Milk"

如果你想要移除数组最后一个元素，使用 removeLast()方法

	var someList: [String] = ["Eggs", "Milk", "Flour"]
	someList.removeLast()
	//now someList is ["Eggs", "Milk"]

__2.7 遍历一个数组__  
用 for-in循环来遍历整个数组中值的合集：

	var someList: [String] = ["Eggs", "Milk", "Flour"]
	for item in someList {
    	print(item)
	}
	//Eggs
	//Milk
	//Flour
	
如果你需要每个元素以及值的整数索引，使用 enumerated()方法来遍历数组。 enumerated()方法返回数组中每一个元素的元组，包含了这个元素的索引和值。你可以分解元组为临时的常量或者变量作为遍历的一部分：

	var someList: [String] = ["Eggs", "Milk", "Flour"]
	for (index, value) in someList.enumerated() {
    	print("\(index+1) : \(value)")
	}
	//1 : Eggs
	//2 : Milk
	//3 : Flour


####3. 集合Set  
合集将同一类型且不重复的值无序地储存在一个集合当中。当元素的顺序不那么重要的时候你就可以使用合集来代替数组，或者你需要确保元素不会重复的时候。

>Swift 的 Set类型桥接到了基础框架的 NSSet类上。

__3.1 Set 类型的哈希值__  
为了能让类型储存在Set当中，它必须是可哈希的——就是说类型必须提供计算它自身哈希值的方法。哈希值是Int值且所有的对比起来相等的对象都相同，比如 a == b，它遵循 a.hashValue == b.hashValue。

所有 Swift 的基础类型（比如 String, Int, Double, 和 Bool）默认都是可哈希的，并且可以用于Set或者字典的键。没有关联值的枚举成员值（如同枚举当中描述的那样）同样默认可哈希。

>你可以使用你自己自定义的类型作为合集的值类型或者字典的键类型，只要让它们遵循 Swift 基础库的 Hashable协议即可。遵循 Hashable协议的类型必须提供可获取的叫做 hashValue的 Int属性。通过 hashValue属性返回的值不需要在同一个程序的不同的执行当中都相同，或者不同程序。  

>因为 Hashable协议遵循 Equatable，遵循的类型必须同时一个“等于”运算符 ( ==)的实现。 Equatable协议需要任何遵循 ==的实现都具有等价关系。就是说， ==的实现必须满足以下三个条件，其中 a, b, 和 c是任意值：  

>a == a  (自反性)  
>a == b 意味着 b == a  (对称性)  
>a == b && b == c 意味着 a == c  (传递性)  

__3.2 集合Set类型语法__  
Swift 的集合Set类型写做 Set<Element>，这里的 Element是合集要储存的类型。不同与数组，集合Set没有等价的简写。

__3.3 创建并初始化一个空集合Set__  
你可以使用初始化器语法来创建一个确定类型的空集合Set：

	var letters: Set = Set<String>()
	print("letters is of type Set<Character> with \(letters.count) items.")
	// prints "letters is of type Set<Character> with 0 items."
	
如果内容已经提供了类型信息，比如函数的实际参数或者已经分类的变量常量，你就可以用空的数组字面量来创建一个空集合Set：

	var letters: Set<String> = Set<String>()
	//or var letters: Set<String> = []
	letters.insert("a")
	// letters now contains 1 value of type Character
	letters = []
	// letters is now an empty set, but is still of type Set<Character>

__3.4 使用数组字面量创建集合Set__  
可以使用数组字面量来初始化一个集合Set，算是一种写一个或者多个集合Set值的快捷方式。

	var someSet: Set<String> = ["Rock", "Classical", "Hip hop"]

__3.5 访问和修改集合Set__  
你可以通过合集的方法和属性来访问和修改集合Set。

要得出集合Set当中元素的数量，检查它的只读 count属性：

	var someSet: Set<String> = ["Rock", "Classical", "Hip hop"]
	print("I have \(someSet.count) Items.")
	// prints "I have 3 Items."
	
使用布尔量 isEmpty 属性作为检查 count 属性是否等于的快捷方式：

	var someSet: Set<String> = ["Rock", "Classical", "Hip hop"]
	if !someSet.isEmpty {
    	print("This Set is not empty")
	}
	//prints "This Set is not empty"
	
你可通过调用 insert(_:)方法来添加一个新的元素到集合Set：

	var someSet: Set<String> = ["Rock", "Classical", "Hip hop"]
	someSet.insert("Jazz")
	//someSet now contains 4 items

你可以通过调用集合Set的 remove(_:)方法来从集合Set当中移除一个元素，如果元素是几何的成员就移除它，并且返回移除的值，如果集合Set没有这个成员就返回 nil。另外，集合Set当中所有的元素可以用 removeAll()一次移除。

	var someSet: Set<String> = ["Rock", "Classical", "Hip hop"]
	if let removedGenre = someSet.remove("Rock") {
    	print("\(removedGenre)? I'm over it.")
	}
	// prints "Rock? I'm over it."
	
要检查合集是否包含了特定的元素，使用 contains(_:)方法。

	var someSet: Set<String> = ["Rock", "Classical", "Hip hop"]
	if someSet.contains("Rock") {
    	print("I get it.")
	}
	//prints "I get it."

__3.6 遍历集合Set__  
可以在 for-in循环里遍历集合Set的值。

	var someSet: Set<String> = ["Rock", "Classical", "Hip hop"]
	for item in someSet {
    	print(item)
	}
	//Hip hop
	//Rock
	//Classical
	
Swift 的 Set类型是无序的。要以特定的顺序遍历合集的值，使用 sorted()方法，它把合集的元素作为使用 < 运算符排序了的数组返回。

	var someSet: Set<String> = ["Rock", "Classical", "Hip hop"]
	for item in someSet.sorted() {
    	print(item)
	}
	//Classical
	//Hip hop
	//Rock


####4. 执行集合Set操作  
你可以高效地执行基本地合集操作，比如合并两个合集，确定两个合集共有哪个值，或者确定两个合集是否包含所有、某些或没有相同的值。

__4.1 基本集合Set操作__   

* 使用 intersection(_:)方法来创建一个只包含两个合集共有值的新合集；  
* 使用 symmetricDifference(_:)方法来创建一个只包含两个合集各自有的非共有值的新合集；  
* 使用 union(_:)方法来创建一个包含两个合集所有值的新合集；  
* 使用 subtracting(_:)方法来创建一个两个合集当中不包含某个合集值的新合集。  

例子：

	let oddDigits: Set = [1, 3, 5, 7, 9]
	let evenDigits: Set = [0, 2, 4, 6, 8]
	let singleDigitPrimeNumbers: Set = [2, 3, 5, 7]

	oddDigits.union(evenDigits).sorted()
	// [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
	oddDigits.intersection(evenDigits).sorted()
	// []
	oddDigits.subtracting(singleDigitPrimeNumbers).sorted()
	// [1, 9]
	oddDigits.symmetricDifference(singleDigitPrimeNumbers).sorted()
	// [1, 2, 9]
	
__4.2 集合Set成员关系和相等性__  

* 使用“相等”运算符 ( == )来判断两个合集是否包含有相同的值；
* 使用 isSubset(of:) 方法来确定一个合集的所有值是被某合集包含；
* 使用 isSuperset(of:)方法来确定一个合集是否包含某个合集的所有值；
* 使用 isStrictSubset(of:) 或者 isStrictSuperset(of:)方法来确定是个合集是否为某一个合集的子集或者超集，但并不相等；
* 使用 isDisjoint(with:)方法来判断两个合集是否 不拥有相同的值。

例子：

	let testSet1: Set = ["a", "b"]
	let testSet2: Set = ["a", "b", "c", "d", "e"]
	let testSet3: Set = ["f", "g"]

	testSet1.isSubset(of: testSet2)
	// true
	testSet2.isSuperset(of: testSet1)
	// true
	testSet2.isDisjoint(with: testSet3)
	// true


####5. 字典  
字典储存无序的互相关联的同一类型的键和同一类型的值的集合。每一个值都与唯一的键相关联，它就好像这个值的身份标记一样。不同于数组中的元素，字典中的元素没有特定的顺序。

__5.1 字典类型简写语法__  
Swift 的字典类型写全了是这样的： Dictionary<Key, Value>，其中的 Key是用来作为字典键的值类型， Value就是字典为这些键储存的值的类型。

>字典的 Key类型必须遵循 Hashable协议

__5.2 创建一个空字典__  
可以用初始化器语法来创建一个空 Dictionary：

	let testDictionary: Dictionary<Int, String> = Dictionary<Int, String>()
	//simplify let testDictionary = Dictionary<Int, String>()
	
上面例子创建了类型为 [Int: String]的空字典来储存整数的可读名称。它的键是 Int类型，值是 String类型。  

如果内容已经提供了信息，你就可以用字典字面量创建空字典了，它写做 [:]（在一对方括号里写一个冒号）：

	var testDictionary: Dictionary<Int, String> = Dictionary<Int, String>()
	testDictionary[2] = "string"
	//testDictionary now contains 1 key-value pair
	testDictionary = [:]
	//testDictionary is empty of type [Int: String]

__5.3 用字典字面量创建字典__  
你同样可以使用字典字面量来初始化一个字典，它与数组字面量看起来差不多。字典字面量是写一个或者多个键值对为 Dictionary集合的快捷方式。

	var localTem: Dictionary<String, String> = ["Beijing" : "20", "Chengdu" : "27"]
	//simplify var localTem = ["Beijing" : "20", "Chengdu" : "27"]

__5.4 访问和修改字典__  
你可以通过字典自身的方法和属性来访问和修改它，或者通过使用下标脚本语法。

如同数组，你可以使用 count只读属性来找出 Dictionary拥有多少元素：

	var localTem: Dictionary<String, String> = ["Beijing" : "20", "Chengdu" : "27"]
	print("The localTem dictionary contains \(localTem.count) items.")
	//prints "The localTem dictionary contains \(localTem.count) items."
	
使用布尔量 isEmpty属性作为检查 count属性是否等于 0的快捷方式：

	var localTem: Dictionary<String, String> = ["Beijing" : "20", "Chengdu" : "27"]
	if !localTem.isEmpty {
    	print("localTem is not Empty")
	}
	//prints "localTem is not Empty"
	
你可以用下标脚本给字典添加新元素。使用正确类型的新键作为下标脚本的索引，然后赋值一个正确类型的值：

	var localTem: Dictionary<String, String> = ["Beijing" : "20", "Chengdu" : "27"]
	localTem["London"] = "18"
	//localTem now contains 3 items

可以使用下标脚本语法来改变特定键关联的值：

	var localTem: Dictionary<String, String> = ["Beijing" : "20", "Chengdu" : "27"]
	localTem["London"] = "18"
	localTem["London"] = "17"
	//localTem["London"] = 17


作为下标脚本的代替，使用字典的 updateValue(\_:forKey:)方法来设置或者更新特点键的值。就像上边下标脚本的栗子， updateValue(\_:forKey:)方法会在键没有值的时候设置一个值，或者在键已经存在的时候更新它。总之，不同于下标脚本， updateValue(\_:forKey:)方法在执行更新之后返回旧的值。这允许你检查更新是否成功。  

updateValue(\_:forKey:)方法返回一个字典值类型的可选项值。比如对于储存 String值的字典来说，方法会返回 String?类型的值，或者说“可选的 String”。这个可选项包含了键的旧值如果更新前存在的话，否则就是 nil：

	var localTem: Dictionary<String, String> = ["Beijing" : "20", "Chengdu" : "27"]
	if let oldValue = localTem.updateValue("18", forKey: "Beijing") {
		print("The old value for Beijing is \(oldValue)")
	}
	//prints "The old value for Beijing is 20"
	
可以使用下标脚本语法来从字典的特点键中取回值。由于可能请求的键没有值，字典的下标脚本返回可选的字典值类型。如果字典包含了请求的键的值，下标脚本就返回一个包含这个键的值的可选项。否则，下标脚本返回 nil ：

	var localTem: Dictionary<String, String> = ["Beijing" : "20", "Chengdu" : "27"]
	if let item = localTem["Chengdu"] {
    	print("The tem of Chengdu is \(item)")
	}
	//prints "The tem of Chengdu is 27"	

使用下标脚本语法给一个键赋值 nil来从字典当中移除一个键值对：

	var localTem: Dictionary<String, String> = ["Beijing" : "20", "Chengdu" : "27"]
	localTem["Beijing"] = nil
	//localTem now contains 1 item
	
另外，使用 removeValueForKey(_:)来从字典里移除键值对。这个方法移除键值对如果他们存在的话，并且返回移除的值，如果值不存在则返回 nil：

	var localTem: Dictionary<String, String> = ["Beijing" : "20", "Chengdu" : "27"]
	if let removeItem = localTem.removeValue(forKey: "Beijing") {
    	print("The remove city's tem is \(removeItem)")
	}
	//prints "The remove city's tem is 20"

__5.5 遍历字典__  
用 for-in循环来遍历字典的键值对。字典中的每一个元素返回为 (key, value)元组，你可以解开元组成员到临时的常量或者变量作为遍历的一部分：

	var localTem: Dictionary<String, String> = ["Beijing" : "20", "Chengdu" : "27"]
	for (city, tem) in localTem {
    	print("\(city) is \(tem)")
	}
	//Chengdu is 27
	//Beijing is 20
	
同样可以通过访问字典的 keys和 values属性来取回可遍历的字典的键或值的集合：

	var localTem: Dictionary<String, String> = ["Beijing" : "20", "Chengdu" : "27"]
	for localTemCode in localTem.keys {
    	print("\(localTemCode)")
	}
	//Chengdu
	//Beijing
	for localTemValue in localTem.values {
    	print("\(localTemValue)")
	}
	//27
	//20

如果需要和接收 Array实例的 API 一起使用字典的键或值，就用 keys或 values属性来初始化一个新数组：
	
	var localTem: Dictionary<String, String> = ["Beijing" : "20", "Chengdu" : "27"]
	let localTemCode = [String](localTem.keys)
	//localTemCode = ["Chengdu", "Beijing"]
	let localTemValue = [String](localTem.values)
	//localTemValue = ["27", "20"]

Swift 的 Dictionary类型是无序的。要以特定的顺序遍历字典的键或值，使用键或值的 sorted()方法。


</br></br>

--------------------------------------
参考资料：  
Swift 3 编程语言： <https://www.cnswift.org>  
</br>
Time: 2016.10.10






