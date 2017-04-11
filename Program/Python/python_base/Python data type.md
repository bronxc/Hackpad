# Python data type

------------------------------------- 
### 0x00 前言  
本文详细介绍了 Python 中的数据类型： 数字，字符串，列表，元组，字典；还有时间的处理。



### 0x01 目录  
1. 数字  
	1.1 数字函数  
	1.2 随机数函数  
	1.3 三角函数  
	1.4 数字常量  

2. 字符串  
	2.1 访问字符串的值  
	2.2 字符串更新  
	2.3 转义字符  
	2.4 字符串运算符  
	2.5 字符串格式化  
	2.6 三引号  
	2.7 Unicode字符串  
	2.8 字符串的函数   

3. 列表  
	3.1 访问列表的值  
	3.2 更新列表  
	3.3 删除列表元素  
	3.4 列表操作符  
	3.5 列表截取   
	3.6 列表的函数  

4. 元组  
	4.1 访问元组的值  
	4.2 修改元组   
	4.3 删除元组  
	4.4 元组操作符  
	4.5 元组截取  
	4.6 无关闭分隔符  
	4.7 元组的函数

5. 字典  
	5.1 访问字典的值  
	5.2 修改字典  
	5.3 删除字典元素  
	5.4 字典的特性  
	5.5 字典的函数  　

6. 日期和时间  
	6.1 时间元组  
	6.2 获取当前时间  
	6.3 格式化时间  
	6.4 获取日历  
	6.5 Time模块的函数  
	6.6 Calendar模块的函数  




### 0x02 正文  
#### 1. 数字  
Python Number 数据类型用于存储数值。  
数据类型是不允许改变的,这就意味着如果改变 Number 数据类型的值，将重新分配内存空间。  
以下实例在变量赋值时 Number 对象将被创建：  

	var1 = 1
	var2 = 10
可以使用del语句删除一些 Number 对象引用。  

	del var1[,var2[,var3[....,varN]]]]  
	
Python 支持四种不同的数值类型：  

* 整型(Int) - 通常被称为是整型或整数，是正或负整数，不带小数点。
* 长整型(long integers) - 无限大小的整数，整数最后是一个大写或小写的L。
* 浮点型(floating point real values) - 浮点型由整数部分与小数部分组成，浮点型也可以使用科学计数法表示（2.5e2 = 2.5 x 102 = 250）
* 复数( (complex numbers)) - 复数由实数部分和虚数部分构成，可以用a + bj,或者complex(a,b)表示， 复数的实部a和虚部b都是浮点型。

> 注：长整型也可以使用小写"L"，但是还是建议您使用大写"L"，避免与数字"1"混淆。Python使用"L"来显示长整型。  
Python还支持复数，复数由实数部分和虚数部分构成，可以用a + bj,或者complex(a,b)表示， 复数的实部a和虚部b都是浮点型


有时候，我们需要对数据内置的类型进行转换，数据类型的转换，你只需要将数据类型作为函数名即可。  
以下几个内置的函数可以执行数据类型之间的转换。这些函数返回一个新的对象，表示转换的值。  

|函数|描述|
|-----|-----|
|int(x [,base])|将x转换为一个整数|
|long(x [,base] )|将x转换为一个长整数|
|float(x)|将x转换到一个浮点数|
|complex(real [,imag])|创建一个复数|
|str(x)|将对象 x 转换为字符串|
|repr(x)|将对象 x 转换为表达式字符串|
|eval(str)|用来计算在字符串中的有效Python表达式,并返回一个对象|
|tuple(s)|将序列 s 转换为一个元组|
|list(s)|将序列 s 转换为一个列表|
|set(s)|转换为可变集合|
|dict(d)|创建一个字典。d 必须是一个序列 (key,value)元组。|
|frozenset(s)|转换为不可变集合|
|chr(x)|将一个整数转换为一个字符|
|unichr(x)|将一个整数转换为Unicode字符|
|ord(x)|将一个字符转换为它的整数值|
|hex(x)|将一个整数转换为一个十六进制字符串|
|oct(x)|将一个整数转换为一个八进制字符串|



__1.1 数字函数__  
部分函数需要导入 `math` 库。

|函数|	返回值 ( 描述 )|
|----|---------|
|abs(x)|	返回数字的绝对值，如abs(-10) 返回 10|
|ceil(x)|	返回数字的上入整数，如math.ceil(4.1) 返回 5|
|cmp(x, y)|	如果 x < y 返回 -1, 如果 x == y 返回 0, 如果 x > y 返回 1|
|exp(x)|	返回e的x次幂(ex),如math.exp(1) 返回2.718281828459045|
|fabs(x)|	返回数字的绝对值，如math.fabs(-10) 返回10.0|
|floor(x)|	返回数字的下舍整数，如math.floor(4.9)返回 4|
|log(x)|	如math.log(math.e)返回1.0,math.log(100,10)返回2.0|
|log10(x)|	返回以10为基数的x的对数，如math.log10(100)返回 2.0|
|max(x1, x2,...)|	返回给定参数的最大值，参数可以为序列。|
|min(x1, x2,...)|	返回给定参数的最小值，参数可以为序列。|
|modf(x)|	返回x的整数部分与小数部分，两部分的数值符号与x相同，整数部分以浮点型表示。|
|pow(x, y)|	x**y 运算后的值。|
|round(x [,n])|	返回浮点数x的四舍五入值，如给出n值，则代表舍入到小数点后的位数。|
|sqrt(x)|	返回数字x的平方根，数字可以为负数，返回类型为实数，如math.sqrt(4)返回 2+0j|


__1.2 随机数函数__  
随机数可以用于数学，游戏，安全等领域中，还经常被嵌入到算法中，用以提高算法效率，并提高程序的安全性。  
需要导入 `random` 库。

|函数|	描述|
|-----|-----|
|choice(seq)|	从序列的元素中随机挑选一个元素，比如random.choice(range(10))，从0到9中随机挑选一个整数。|
|randrange ([start,] stop [,step])|	从指定范围内，按指定基数递增的集合中获取一个随机数，基数缺省值为1|
|random()|	随机生成下一个实数，它在[0,1)范围内。|
|seed([x])|	改变随机数生成器的种子seed。如果你不了解其原理，你不必特别去设定seed，Python会帮你选择seed。|
|shuffle(lst)|	将序列的所有元素随机排序|
|uniform(x, y)|	随机生成下一个实数，它在[x,y]范围内。|



__1.3 三角函数__  
需要导入 `math` 库。

|函数|	描述|
|-----|-----|
|acos(x)|	返回x的反余弦弧度值。|
|asin(x)|	返回x的反正弦弧度值。|	
|atan(x)|	返回x的反正切弧度值。|
|atan2(y, x)|	返回给定的 X 及 Y 坐标值的反正切值。|
|cos(x)|	返回x的弧度的余弦值。|
|hypot(x, y)|	返回欧几里德范数 sqrt(x\*x + y\*y)。|
|sin(x)|	返回的x弧度的正弦值。|
|tan(x)|	返回x弧度的正切值。|
|degrees(x)|	将弧度转换为角度,如degrees(math.pi/2) ， 返回90.0|
|radians(x)|	将角度转换为弧度|



__1.4 数字常量__  
需要导入 `math` 库。

|常量|	描述|
|-----|-----|
|pi|	数学常量 pi（圆周率，一般以π来表示）|
|e| 	数学常量 e，e即自然常数（自然常数）|




#### 2. 字符串  
字符串是 Python 中最常用的数据类型。我们可以使用引号('或")来创建字符串。  
创建字符串很简单，只要为变量分配一个值即可。

	var1 = 'Hello World!'
	var2 = "Python"


__2.1 访问字符串的值__  
Python不支持单字符类型，单字符也在Python也是作为一个字符串使用。  
Python访问子字符串，可以使用方括号来截取字符串:   

	#! /usr/bin/python

	var1 = "Hello World"

	print var1[0]
	print var1[1:5]
	
	#$ python test.py 
	#H
	#ello



__2.2 字符串更新__  
你可以对已存在的字符串进行修改，并赋值给另一个变量，如下实例：  

	#! /usr/bin/python

	var1 = "Hello World"
	var2 = var1[:4] + "xx"

	print var2
	
	#$ python test.py 
	#Hellxx



__2.3 转义字符__  
在需要在字符中使用特殊字符时，python用反斜杠(\)转义字符。

|转义字符|	描述|
|-------|------|
|\\(在行尾时)|	续行符|
|\\\\|	反斜杠符号|
|\\'|	单引号|
|\\"|	双引号|
|\\a|	响铃|
|\\b|	退格(Backspace)|
|\\e|	转义|
|\\000|	空|
|\\n|	换行|
|\\v|	纵向制表符|
|\\t|	横向制表符|
|\\r|	回车|
|\\f|	换页|
|\\oyy|	八进制数，yy代表的字符，例如：\o12代表换行|
|\\xyy|	十六进制数，yy代表的字符，例如：\x0a代表换行|
|\\other|	其它的字符以普通格式输出|



__2.4 字符串运算符__  

	a = "Hello"
	b = "Python"
	
|操作符|	描述|	实例| 结果|
|------|-----|------|-----|
|+|	字符串连接	|>>>a + b | 'HelloPython'|
|*|	重复输出字符串	|>>>a * 2| 'HelloHello'|
|[]|	通过索引获取字符串中字符|>>>a[1]| 'e'|
|[ : ]|	截取字符串中的一部分	|>>>a[1:4]|'ell'|
|in|	成员运算符 - 如果字符串中包含给定的字符返回 True|>>>"H" in a|True|
|not in|	成员运算符 - 如果字符串中不包含给定的字符返回 True|>>>"M" not in a|True|
|r/R|	原始字符串 - 原始字符串：所有的字符串都是直接按照字面的意思来使用，没有转义特殊或不能打印的字符。 原始字符串除在字符串的第一个引号前加上字母"r"（可以大小写）以外，与普通字符串有着几乎完全相同的语法。|>>>print r'\n'|\n|
|%|	格式字符串|下一章|


__2.5 字符串格式化__  
Python 支持格式化字符串的输出 。尽管这样可能会用到非常复杂的表达式，但最基本的用法是将一个值插入到一个有字符串格式符 %s 的字符串中。  

	#! /usr/bin/python

	print "My name is %s and age is %d" % ("xx", 5)
	
	#$ python test.py 
	#My name is xx and age is 5
	
python字符串格式化符号:  

|符号|	描述|
|----|------|
|%c|	 格式化字符及其ASCII码|
|%s|	 格式化字符串|
|%d|	 格式化整数|
|%u	| 格式化无符号整型|
|%o	| 格式化无符号八进制数|
|%x	| 格式化无符号十六进制数|
|%X	| 格式化无符号十六进制数（大写）|
|%f	| 格式化浮点数字，可指定小数点后的精度|
|%e	| 用科学计数法格式化浮点数|
|%E	| 作用同%e，用科学计数法格式化浮点数|
|%g	| %f和%e的简写|
|%G	| %f 和 %E 的简写|
|%p	| 用十六进制数格式化变量的地址|

格式化操作符辅助指令:  

|符号|	功能|
|---------|-------|
|*|	定义宽度或者小数点精度|
|-|	用做左对齐|
|+|	在正数前面显示加号( + )|
|\<sp\>|	在正数前面显示空格|
|#|	在八进制数前面显示零('0')，在十六进制前面显示'0x'者'0X'(取决于用的是'x'还是'X')|
|0|	显示的数字前面填充'0'而不是默认的空格|
|%|	'%%'输出一个单一的'%'|
|(var)|	映射变量(字典参数)|
|m.n.|	m 是显示的最小总宽度,n 是小数点后的位数(如果可用的话)|


__2.6 三引号__  
python中三引号可以将复杂的字符串进行复制:  
python三引号允许一个字符串跨多行，字符串中可以包含换行符、制表符以及其他特殊字符。   
三引号让程序员从引号和特殊字符串的泥潭里面解脱出来，自始至终保持一小块字符串的格式是所谓的WYSIWYG（所见即所得）格式的。  

	#! /usr/bin/python

	errHTML = '''
	<HTML><HEAD><TITLE>
	Friends CGI Demo</TITLE></HEAD>
	<BODY><H3>ERROR</H3>
	<B>%s</B><P>
	<FORM><INPUT TYPE=button VALUE=Back
	ONCLICK="window.history.back()"></FORM>
	</BODY></HTML>
	'''

	print errHTML


__2.7 Unicode字符串__  
Python 中定义一个 Unicode 字符串和定义一个普通字符串一样简单：  

	>>> u'Hello World !'
	u'Hello World !'
	
引号前小写的"u"表示这里创建的是一个 Unicode 字符串。如果你想加入一个特殊字符，可以使用 Python 的 Unicode-Escape 编码。  

	>>> u'Hello\u0020World !'
	u'Hello World !'

`\u0020` 是 Unicode 字符中的空格符。



__2.8 字符串的函数__   
字符串方法是从python1.6到2.0慢慢加进来的——它们也被加到了Jython中。  
这些方法实现了string模块的大部分方法，如下表所示列出了目前字符串内建支持的方法，所有的方法都包含了对Unicode的支持，有一些甚至是专门用于Unicode的。  

|方法|	描述|
|------|------|
|string.capitalize()|把字符串的第一个字符大写|
|string.center(width)|返回一个原字符串居中,并使用空格填充至长度 width 的新字符串|
|string.count(str, beg=0, end=len(string))|返回 str 在 string 里面出现的次数，如果 beg 或者 end 指定则返回指定范围内 str 出现的次数|
|string.decode(encoding='UTF-8', errors='strict')|以 encoding 指定的编码格式解码 string，如果出错默认报一个 ValueError 的 异 常 ， 除 非 errors 指 定 的 是 'ignore' 或 者'replace'|
|string.encode(encoding='UTF-8', errors='strict')|以 encoding 指定的编码格式编码 string，如果出错默认报一个ValueError 的异常，除非 errors 指定的是'ignore'或者'replace'|
|string.endswith(obj, beg=0, end=len(string))|检查字符串是否以 obj 结束，如果beg 或者 end 指定则检查指定的范围内是否以 obj 结束，如果是，返回 True,否则返回 False.|
|string.expandtabs(tabsize=8)|把字符串 string 中的 tab 符号转为空格，tab 符号默认的空格数是 8。|
|string.find(str, beg=0, end=len(string))|检测 str 是否包含在 string 中，如果 beg 和 end 指定范围，则检查是否包含在指定范围内，如果是返回开始的索引值，否则返回-1|
|string.index(str, beg=0, end=len(string))|跟find()方法一样，只不过如果str不在 string中会报一个异常.|
|string.isalnum()|如果 string 至少有一个字符并且所有字符都是字母或数字则返回 True,否则返回 False|
|string.isalpha()|如果 string 至少有一个字符并且所有字符都是字母则返回 True,否则返回 False|
|string.isdecimal()|如果 string 只包含十进制数字则返回 True 否则返回 False.|
|string.isdigit()|如果 string 只包含数字则返回 True 否则返回 False.|
|string.islower()|如果 string 中包含至少一个区分大小写的字符，并且所有这些(区分大小写的)字符都是小写，则返回 True，否则返回 False|
|string.isnumeric()|如果 string 中只包含数字字符，则返回 True，否则返回 False|
|string.isspace()|如果 string 中只包含空格，则返回 True，否则返回 False.|
|string.istitle()|如果 string 是标题化的(见 title())则返回 True，否则返回 False|
|string.isupper()|如果 string 中包含至少一个区分大小写的字符，并且所有这些(区分大小写的)字符都是大写，则返回 True，否则返回 False|
|string.join(seq)|以 string 作为分隔符，将 seq 中所有的元素(的字符串表示)合并为一个新的字符串|
|string.ljust(width)|返回一个原字符串左对齐,并使用空格填充至长度 width 的新字符串|
|string.lower()|转换 string 中所有大写字符为小写.|
|string.lstrip()|截掉 string 左边的空格|
|string.maketrans(intab, outtab])|maketrans() 方法用于创建字符映射的转换表，对于接受两个参数的最简单的调用方式，第一个参数是字符串，表示需要转换的字符，第二个参数也是字符串表示转换的目标。
|max(str)|返回字符串 str 中最大的字母。|
|min(str)|返回字符串 str 中最小的字母。|
|string.partition(str)|有点像 find()和 split()的结合体,从 str 出现的第一个位置起,把 字 符 串 string 分 成 一 个 3 元 素 的 元 组 (string_pre_str,str,string_post_str),如果 string 中不包含str 则 string_pre_str == string.|
|string.replace(str1, str2,  num=string.count(str1))|把 string 中的 str1 替换成 str2,如果 num 指定，则替换不超过 num 次.|
|string.rfind(str, beg=0,end=len(string) )|类似于 find()函数，不过是从右边开始查找.|
|string.rindex( str, beg=0,end=len(string))|类似于 index()，不过是从右边开始.|
|string.rjust(width)|返回一个原字符串右对齐,并使用空格填充至长度 width 的新字符串|
|string.rpartition(str)|类似于 partition()函数,不过是从右边开始查找.|
|string.rstrip()|删除 string 字符串末尾的空格.|
|string.split(str="", num=string.count(str))|以 str 为分隔符切片 string，如果 num有指定值，则仅分隔 num 个子字符串|
|string.splitlines(num=string.count('\n'))|按照行分隔，返回一个包含各行作为元素的列表，如果 num 指定则仅切片 num 个行.|
|string.startswith(obj, beg=0,end=len(string))|检查字符串是否是以 obj 开头，是则返回 True，否则返回 False。如果beg 和 end 指定值，则在指定范围内检查.|
|string.strip([obj])|在 string 上执行 lstrip()和 rstrip()|
|string.swapcase()|翻转 string 中的大小写|
|string.title()|返回"标题化"的 string,就是说所有单词都是以大写开始，其余字母均为小写(见 istitle())|
|string.translate(str, del="")|根据 str 给出的表(包含 256 个字符)转换 string 的字符,要过滤掉的字符放到 del 参数中|
|string.upper()|转换 string 中的小写字母为大写|
|string.zfill(width)|返回长度为 width 的字符串，原字符串 string 右对齐，前面填充0|
|string.isdecimal()|isdecimal()方法检查字符串是否只包含十进制字符。这种方法只存在于unicode对象。|





#### 3. 列表  
序列是Python中最基本的数据结构。序列中的每个元素都分配一个数字 - 它的位置，或索引，第一个索引是0，第二个索引是1，依此类推。  
Python有6个序列的内置类型，但最常见的是列表和元组。  
序列都可以进行的操作包括索引，切片，加，乘，检查成员。  
此外，Python已经内置确定序列的长度以及确定最大和最小的元素的方法。  
列表是最常用的Python数据类型，它可以作为一个方括号内的逗号分隔值出现。  
列表的数据项不需要具有相同的类型。  
创建一个列表，只要把逗号分隔的不同的数据项使用方括号括起来即可。如下所示：

	list1 = ['physics', 'chemistry', 1997, 2000];
	list2 = [1, 2, 3, 4, 5 ];
	list3 = ["a", "b", "c", "d"];


__3.1 访问列表的值__  
使用下标索引来访问列表中的值，同样你也可以使用方括号的形式截取字符，如下所示：  

	#!/usr/bin/python

	list1 = ['physics', 'chemistry', 1997, 2000];
	list2 = [1, 2, 3, 4, 5, 6, 7 ];

	print "list1[0]: ", list1[0]
	print "list2[1:5]: ", list2[1:5]
	
	#$ python test.py 
	#list1[0]:  physics
	#list2[1:5]:  [2, 3, 4, 5]


__3.2 更新列表__  
你可以对列表的数据项进行修改或更新，你也可以使用append()方法来添加列表项，如下所示：  

	#!/usr/bin/python

	list = ['physics', 'chemistry', 1997, 2000]

	print "Value available at index 1 : "
	print list[1]
	list[1] = 2001
	print "New value available at index 1 : "
	print list[1]
	
	#$ python test.py 
	#Value available at index 1 : 
	#chemistry
	#New value available at index 1 : 
	#2001


__3.3 删除列表元素__  
可以使用 del 语句或 remove 语句来删除列表的的元素，如下实例： 

	#!/usr/bin/python

	list1 = ['physics', 'chemistry', 1997, 2000]

	print list1
	del list1[2]
	print list1

	#$ python test.py 
	#['physics', 'chemistry', 1997, 2000]
	#['physics', 'chemistry', 2000]


__3.4 列表操作符__  
列表对 + 和 * 的操作符与字符串相似。+ 号用于组合列表，* 号用于重复列表。  

|Python 表达式|	结果|	描述|
|-----------|--------|------|
|len([1, 2, 3])|	3|	长度|
|[1, 2, 3] + [4, 5, 6]|	[1, 2, 3, 4, 5, 6]|组合|
|['Hi!'] * 4|	['Hi!', 'Hi!', 'Hi!', 'Hi!']|重复|
|3 in [1, 2, 3]|	True|	元素是否存在于列表中|
|for x in [1, 2, 3]: print x,|	1 2 3	|迭代|



__3.5 列表截取__   
Python的列表截取与字符串操作类型，如下所示：

	L = ['spam', 'Spam', 'SPAM!']
	
|Python| 表达式|	结果|	描述|
|-------|------|------|-----|
|L[2]|	'SPAM!'|	读取列表中第三个元素|
|L[-2]|	'Spam'|	读取列表中倒数第二个元素|
|L[1:]|	['Spam', 'SPAM!']|	从第二个元素开始截取列表|



__3.6 列表的函数__  
Python包含以下函数:

|函数 |描述|
|------|-------|
|cmp(list1, list2)|比较两个列表的元素|
|len(list)|列表元素个数|
|max(list)|返回列表元素最大值|
min(list)|返回列表元素最小值|
|list(seq)|将元组转换为列表|

Python包含以下方法:

|方法| 描述|
|-----|------|
|list.append(obj)|在列表末尾添加新的对象|
|list.count(obj)|统计某个元素在列表中出现的次数|
|list.extend(seq)|在列表末尾一次性追加另一个序列中的多个值（用新列表扩展原来的列表）|
|list.index(obj)|从列表中找出某个值第一个匹配项的索引位置|
|list.insert(index, obj)|将对象插入列表|
|list.pop(obj=list[-1])|移除列表中的一个元素（默认最后一个元素），并且返回该元素的值|
|list.remove(obj)|移除列表中某个值的第一个匹配项|
|list.reverse()|反向列表中元素|
|list.sort([func])|对原列表进行排序|



#### 4. 元组  
Python的元组与列表类似，不同之处在于元组的元素不能修改。  
元组使用小括号，列表使用方括号。  
元组创建很简单，只需要在括号中添加元素，并使用逗号隔开即可。  

	tup1 = ('physics', 'chemistry', 1997, 2000)
	tup2 = (1, 2, 3, 4, 5 )
	tup3 = "a", "b", "c", "d"
	
创建空元组  
	
	tup1 = ()
元组中只包含一个元素时，需要在元素后面添加逗号

	tup1 = (50,)



__4.1 访问元组的值__  
元组可以使用下标索引来访问元组中的值，如下实例:

	#!/usr/bin/python

	tup1 = ('physics', 'chemistry', 1997, 2000);
	tup2 = (1, 2, 3, 4, 5, 6, 7 );

	print "tup1[0]: ", tup1[0]
	print "tup2[1:5]: ", tup2[1:5]
	
	#$ python test.py 
	#tup1[0]:  physics
	#tup2[1:5]:  (2, 3, 4, 5)
	


__4.2 修改元组__   
元组中的元素值是不允许修改的，但我们可以对元组进行连接组合。

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-

	tup1 = (12, 34.56);
	tup2 = ('abc', 'xyz');

	# 以下修改元组元素操作是非法的。
	# tup1[0] = 100;

	# 创建一个新的元组
	tup3 = tup1 + tup2;
	print tup3;
	
	#$ python test.py 
	#(12, 34.56, 'abc', 'xyz')


__4.3 删除元组__  
元组中的元素值是不允许删除的，但我们可以使用del语句来删除整个元组。  

	#!/usr/bin/python

	tup = ('physics', 'chemistry', 1997, 2000)

	print tup
	del tup
	print "After deleting tup : "
	print tup
	
	#$ python test.py 
	#('physics', 'chemistry', 1997, 2000)
	#After deleting tup : 
	#Traceback (most recent call last):
	#  File "test.py", line 8, in <module>
	#    print tup;
	#NameError: name 'tup' is not defined


__4.4 元组操作符__  
元组之间可以使用 + 号和 * 号进行运算。这就意味着他们可以组合和复制，运算后会生成一个新的元组。  

|Python 表达式|	结果|	描述|
|-------------|----------|--------|
|len((1, 2, 3))|	3|	计算元素个数|
|(1, 2, 3) + (4, 5, 6)|	(1, 2, 3, 4, 5, 6)|连接|
|('Hi!',) * 4	('Hi!', 'Hi!', 'Hi!', 'Hi!')|复制|
|3 in (1, 2, 3)|	True|	元素是否存在|
|for x in (1, 2, 3): print x,|	1 2 3|	迭代|



__4.5 元组截取__  
因为元组也是一个序列，所以我们可以访问元组中的指定位置的元素，也可以截取索引中的一段元素，

	L = ('spam', 'Spam', 'SPAM!')
	
|Python 表达式|	结果|	描述|
|---------|-----------|-------|
|L[2]|	'SPAM!'|	读取第三个元素|
|L[-2]|	'Spam'|	反向读取；读取倒数第二个元素|
|L[1:]|	('Spam', 'SPAM!')|	截取索引为1的后面的元素|


__4.6 无关闭分隔符__  
任意无符号的对象，以逗号隔开，默认为元组。  

	#!/usr/bin/python

	print 'abc', -4.24e93, 18+6.6j, 'xyz';

	x, y = 1, 2;
	print "Value of x , y : ", x,y;
	
	#$ python test.py 
	#abc -4.24e+93 (18+6.6j) xyz
	#Value of x , y :  1 2
	
	

__4.7 元组的函数__   
Python元组包含了以下内置函数

|方法|  描述| 
|-----|------|
|cmp(tuple1, tuple2)|比较两个元组元素。|
|len(tuple)|计算元组元素个数。|
|max(tuple)|返回元组中元素最大值。|
|min(tuple)|返回元组中元素最小值。|
|tuple(seq)|将列表转换为元组。|



#### 5. 字典  
字典是另一种可变容器模型，且可存储任意类型对象。  
字典的每个键值(key=>value)对用冒号(:)分割，每个对之间用逗号(,)分割，整个字典包括在花括号({})中 ,格式如下所示：  

	dict = {key1 : value1, key2 : value2}
	
键必须是唯一的，但值则不必。  
值可以取任何数据类型，但键必须是不可变的，如字符串，数字或元组。  

	dict = {'Alice': '2341', 'Beth': '9102', 'Cecil': '3258'}



__5.1 访问字典的值__  
使用方括号进行访问。  

	#!/usr/bin/python
 
	dict = {'Name': 'Zara', 'Age': 7, 'Class': 'First'}
  
	print "dict['Name']: ", dict['Name']
	print "dict['Age']: ", dict['Age']
	
	#$ python test.py 
	#dict['Name']:  Zara
	#dict['Age']:  7

如果用字典里没有的键访问数据，会输出错误 `KeyError`



__5.2 修改字典__  
对字典中的元素进行赋值，就可以进行增加或修改字典。

	#!/usr/bin/python
 
	dict = {'Name': 'Zara', 'Age': 7, 'Class': 'First'};
  
	dict['Age'] = 8; # update existing entry
	dict['School'] = "DPS School"; # Add new entry
    
	print "dict['Age']: ", dict['Age'];
	print "dict['School']: ", dict['School'];
	
	#$ python test.py 
	#dict['Age']:  8
	#dict['School']:  DPS School


__5.3 删除字典元素__  
能删单一的元素也能清空字典，清空只需一项操作。  
显示删除一个字典用del命令，如下实例：  

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-

	dict = {'Name': 'Zara', 'Age': 7, 'Class': 'First'};
 
	del dict['Name']; # 删除键是'Name'的条目
	dict.clear();     # 清空词典所有条目
	del dict ;        # 删除词典


__5.4 字典的特性__  
字典值可以没有限制地取任何python对象，既可以是标准的对象，也可以是用户定义的，但键不行。  

两个重要的点需要记住：

* 1.不允许同一个键出现两次。创建时如果同一个键被赋值两次，后一个值会被记住，如下实例：

		#!/usr/bin/python
 
		dict = {'Name': 'Zara', 'Age': 7, 'Name': 'Manni'};
  
		print "dict['Name']: ", dict['Name'];
		
		#$ python test.py 
		dict['Name']:  Manni
* 2.键必须不可变，所以可以用数字，字符串或元组充当，所以用列表就不行。 



__5.5 字典的函数__  　

Python字典包含了以下内置函数：  

|函数|描述|
|------|-------|
|cmp(dict1, dict2)|比较两个字典元素。|
|len(dict)|计算字典元素个数，即键的总数。|
|str(dict)|输出字典可打印的字符串表示。|
|type(variable)|返回输入的变量类型，如果变量是字典就返回字典类型。|

Python字典包含了以下内置方法：  

|函数|描述|
|------|-------|
|radiansdict.clear()|删除字典内所有元素|
|radiansdict.copy()|返回一个字典的浅复制|
|radiansdict.fromkeys(seq[, value]))|创建一个新字典，以序列seq中元素做字典的键，val为字典所有键对应的初始值|
|radiansdict.get(key, default=None)|返回指定键的值，如果值不在字典中返回default值|
|radiansdict.has_key(key)|如果键在字典dict里返回true，否则返回false|
|radiansdict.items()|以列表返回可遍历的(键, 值) 元组数组|
|radiansdict.keys()|以列表返回一个字典所有的键|
|radiansdict.setdefault(key, default=None)|和get()类似, 但如果键不存在于字典中，将会添加键并将值设为default|
|radiansdict.update(dict2)|把字典dict2的键/值对更新到radiansdict里|
|radiansdict.values()|以列表返回字典中的所有值|



#### 6. 日期和时间  
Python 程序能用很多方式处理日期和时间，转换日期格式是一个常见的功能。  
Python 提供了一个 time 和 calendar 模块可以用于格式化日期和时间。  
时间间隔是以秒为单位的浮点小数。  
每个时间戳都以自从1970年1月1日午夜（历元）经过了多长时间来表示。  
Python 的 time 模块下有很多函数可以转换常见日期格式。如函数time.time()用于获取当前时间戳, 如下实例:  

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-

	import time;  # 引入time模块

	ticks = time.time()
	print "当前时间戳为:", ticks
	
	#$ python test.py 
	#当前时间戳为: 1485591957.97

>时间戳单位最适于做日期运算。但是1970年之前的日期就无法以此表示了。太遥远的日期也不行，UNIX和Windows只支持到2038年。


__6.1 时间元组__  
Python 中的 struct_time 元组, 很多Python函数用这个元组进行数字处理时间。  

|序号|    属性|	字段|	样例值或者范围|
|-----|------|------|------|
|0|tm_year |	4位数年|	2008|
|1 tm_mon |	月 |	1 到 12|
|2| tm_mday |	日 |	1到31|
|3| tm_hour |	小时 |	0到23|
|4|	 tm_min |分钟 |	0到59|
|5| tm_sec |	秒 |	0到61 (60或61 是闰秒)|
|6| tm_wday |	一周的第几日 |	0到6 (0是周一)|
|7| tm_yday |	一年的第几日 |	1到366 (儒略历)|
|8|	 tm_isdst |夏令时 |	-1, 0, 1, -1是决定是否为夏令时的旗帜|


__6.2 获取当前时间__  
从返回浮点数的时间戳方式向时间元组转换，只要将浮点数传递给如localtime之类的函数。  

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-

	import time
	
	localtime = time.localtime(time.time())
	print "本地时间为 :", localtime
	
	#$ python test.py 
	#本地时间为 : time.struct_time(tm_year=2017, tm_mon=1, tm_mday=28, tm_hour=16, tm_min=35, tm_sec=1, tm_wday=5, tm_yday=28, tm_isdst=0)



__6.3 格式化时间__  
你可以根据需求选取各种格式，但是最简单的获取可读的时间模式的函数是asctime():  

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-

	import time

	localtime = 	time.asctime( time.localtime(time.time()) )
	print "本地时间为 :", localtime
	
	#$ python test.py 
	#本地时间为 : Sat Jan 28 16:48:22 2017
	
使用 time 模块的 strftime 方法来格式化日期:  

	time.strftime(format[, t])

例子：  

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-

	import time

	# 格式化成2016-03-20 11:45:39形式
	print time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()) 

	# 格式化成Sat Mar 28 22:24:24 2016形式
	print time.strftime("%a %b %d %H:%M:%S %Y", time.localtime()) 
  
	# 将格式字符串转换为时间戳
	a = "Sat Mar 28 22:24:24 2016"
	print time.mktime(time.strptime(a,"%a %b %d %H:%M:%S %Y"))
	
	#$ python test.py 
	#2017-01-28 16:50:50
	#Sat Jan 28 16:50:50 2017
	#1459175064.0
	
python中时间日期格式化符号：

|符号|描述|
|------|-------|
|%y| 两位数的年份表示（00-99）|
|%Y| 四位数的年份表示（000-9999）|
|%m| 月份（01-12）|
|%d| 月内中的一天（0-31）|
|%H| 24小时制小时数（0-23）|
|%I| 12小时制小时数（01-12）|
|%M| 分钟数（00=59）|
|%S| 秒（00-59）|
|%a| 本地简化星期名称|
|%A| 本地完整星期名称|
|%b| 本地简化的月份名称|
|%B| 本地完整的月份名称|
|%c| 本地相应的日期表示和时间表示|
|%j| 年内的一天（001-366）|
|%p| 本地A.M.或P.M.的等价符|
|%U| 一年中的星期数（00-53）星期天为星期的开始|
|%w| 星期（0-6），星期天为星期的开始|
|%W| 一年中的星期数（00-53）星期一为星期的开始|
|%x| 本地相应的日期表示|
|%X| 本地相应的时间表示|
|%Z| 当前时区的名称|
|%%| %号本身|



__6.4 获取日历__  
Calendar模块有很广泛的方法用来处理年历和月历，例如打印某月的月历：

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-

	import calendar

	cal = calendar.month(2016, 1)
	print "以下输出2016年1月份的日历:"
	print cal
	
	#$ python test.py 
	#以下输出2016年1月份的日历:
	#    January 2016
	#Mo Tu We Th Fr Sa Su
	#             1  2  3
	# 4  5  6  7  8  9 10
	#11 12 13 14 15 16 17
	#18 19 20 21 22 23 24
	#25 26 27 28 29 30 31


__6.5 Time模块的函数__  
Time 模块包含了以下内置函数，既有时间处理相的，也有转换时间格式的： 

|函数|描述|
|------|------|
|time.altzone|返回格林威治西部的夏令时地区的偏移秒数。如果该地区在格林威治东部会返回负值（如西欧，包括英国）。对夏令时启用地区才能使用。|
|time.asctime([tupletime])|接受时间元组并返回一个可读的形式为"Tue Dec 11 18:07:14 2008"（2008年12月11日 周二18时07分14秒）的24个字符的字符串。|
|time.clock( )|用以浮点数计算的秒数返回当前的CPU时间。用来衡量不同程序的耗时，比time.time()更有用。|
|time.ctime([secs])|作用相当于asctime(localtime(secs))，未给参数相当于asctime()|
|time.gmtime([secs])|接收时间辍（1970纪元后经过的浮点秒数）并返回格林威治天文时间下的时间元组t。注：t.tm_isdst始终为0|
|time.localtime([secs])|接收时间辍（1970纪元后经过的浮点秒数）并返回当地时间下的时间元组t（t.tm_isdst可取0或1，取决于当地当时是不是夏令时）。|
|time.mktime(tupletime)|接受时间元组并返回时间辍（1970纪元后经过的浮点秒数）。|
|time.sleep(secs)|推迟调用线程的运行，secs指秒数。|
|time.strftime(fmt[,tupletime])|接收以时间元组，并返回以可读字符串表示的当地时间，格式由fmt决定。|
|time.strptime(str,fmt='%a %b %d %H:%M:%S %Y')|根据fmt的格式把一个时间字符串解析为时间元组。|
|time.time( )|返回当前时间的时间戳（1970纪元后经过的浮点秒数）。|
|time.tzset()|根据环境变量TZ重新初始化时间相关设置。|
|time.timezone|属性time.timezone是当地时区（未启动夏令时）距离格林威治的偏移秒数（>0，美洲;<=0大部分欧洲，亚洲，非洲）。|
|time.tzname|属性time.tzname包含一对根据情况的不同而不同的字符串，分别是带夏令时的本地时区名称，和不带的。|


__6.6 Calendar模块的函数__  
此模块的函数都是日历相关的，例如打印某月的字符月历。  模块包含了以下内置函数：  

|函数|描述|
|-------|------|
|calendar.calendar(year,w=2,l=1,c=6)|返回一个多行字符串格式的year年年历，3个月一行，间隔距离为c。 每日宽度间隔为w字符。每行长度为21* W+18+2* C。l是每星期行数。|
|calendar.firstweekday( )|返回当前每周起始日期的设置。默认情况下，首次载入caendar模块时返回0，即星期一。|
|calendar.isleap(year)|是闰年返回True，否则为false。|
|calendar.leapdays(y1,y2)|返回在Y1，Y2两年之间的闰年总数。|
|calendar.month(year,month,w=2,l=1)|返回一个多行字符串格式的year年month月日历，两行标题，一周一行。每日宽度间隔为w字符。每行的长度为7* w+6。l是每星期的行数。|
|calendar.monthcalendar(year,month)|返回一个整数的单层嵌套列表。每个子列表装载代表一个星期的整数。Year年month月外的日期都设为0;范围内的日子都由该月第几日表示，从1开始。|
|calendar.monthrange(year,month)|返回两个整数。第一个是该月的星期几的日期码，第二个是该月的日期码。日从0（星期一）到6（星期日）;月从1到12。|
|calendar.prcal(year,w=2,l=1,c=6)|相当于 print calendar.calendar(year,w,l,c).|
|calendar.prmonth(year,month,w=2,l=1)|相当于 print calendar.calendar（year，w，l，c）。|
|calendar.setfirstweekday(weekday)|设置每周的起始日期码。0（星期一）到6（星期日）。|
|calendar.timegm(tupletime)|和time.gmtime相反：接受一个时间元组形式，返回该时刻的时间辍（1970纪元后经过的浮点秒数）。|
|calendar.weekday(year,month,day)|返回给定日期的日期码。0（星期一）到6（星期日）。月份为 1（一月） 到 12（12月）。|



</br>

-------------------------------  
References:  
菜鸟教程:  <http://www.runoob.com/python/python-tutorial.html>  
</br>
Author: xx  
Time: 2017.1.28