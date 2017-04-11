# Python Regular Expression  

-----------------------------------  
### 0x00 前言  
介绍 Python 中正则表达式的用法。

### 0x01 目录  
1. re 模块    
2. Match  
3. Pattern  
4. 反斜杠的问题   
5. 正则表达式



### 0x02 正文 
__1. re 模块__    
正则表达式是一个特殊的字符序列，它能帮助你方便的检查一个字符串是否与某种模式匹配。  

Python通过re模块提供对正则表达式的支持。使用re的一般步骤是先将正则表达式的字符串形式编译为Pattern实例，然后使用Pattern实例处理文本并获得匹配结果（一个Match实例），最后使用Match实例获得信息，进行其他的操作。  

	# encoding: UTF-8
	import re
 
	# 将正则表达式编译成Pattern对象
	pattern = re.compile(r'hello')
  
	# 使用Pattern匹配文本，获得匹配结果，无法匹配时将返回None
	match = pattern.match('hello world!')
   
	if match:
	    # 使用Match获得分组信息
	    print match.group()
	    
	#$ python test.py 
	#hello

`re.compile(strPattern[, flag])`:
这个方法是Pattern类的工厂方法，用于将字符串形式的正则表达式编译为Pattern对象。 第二个参数flag是匹配模式，取值可以使用按位或运算符'|'表示同时生效，比如re.I | re.M。另外，你也可以在regex字符串中指定模式，比如re.compile('pattern', re.I | re.M)与re.compile('(?im)pattern')是等价的。 可选值：  

* re.I(re.IGNORECASE): 忽略大小写（括号内是完整写法，下同）
* M(MULTILINE): 多行模式，改变'^'和'$'的行为（参见上图）
* S(DOTALL): 点任意匹配模式，改变'.'的行为
* L(LOCALE): 使预定字符类 \w \W \b \B \s \S 取决于当前区域设定
* U(UNICODE): 使预定字符类 \w \W \b \B \s \S \d \D 取决于unicode定义的字符属性
* X(VERBOSE): 详细模式。这个模式下正则表达式可以是多行，忽略空白字符，并可以加入注释。


re提供了众多模块方法用于完成正则表达式的功能。这些方法可以使用Pattern实例的相应方法替代，唯一的好处是少写一行re.compile()代码，但同时也无法复用编译后的Pattern对象。这些方法将在Pattern类的实例方法部分一起介绍。如上面这个例子可以简写为：

	m = re.match(r'hello', 'hello world!')
	print m.group()



__2. Match__  
介绍一下比较常用的 Match 函数。  

Match对象是一次匹配的结果，包含了很多关于此次匹配的信息，可以使用Match提供的可读属性或方法来获取这些信息。

属性：

1. `string`: 匹配时使用的文本。
2. `re`: 匹配时使用的Pattern对象。
3. `pos`: 文本中正则表达式开始搜索的索引。值与Pattern.match()和Pattern.seach()方法的同名参数相同。
4. `endpos`: 文本中正则表达式结束搜索的索引。值与Pattern.match()和Pattern.seach()方法的同名参数相同。
5. `lastindex`: 最后一个被捕获的分组在文本中的索引。如果没有被捕获的分组，将为None。
6. `lastgroup`: 最后一个被捕获的分组的别名。如果这个分组没有别名或者没有被捕获的分组，将为None。

方法：

1. `group([group1, …])`: 
获得一个或多个分组截获的字符串；指定多个参数时将以元组形式返回。group1可以使用编号也可以使用别名；编号0代表整个匹配的子串；不填写参数时，返回group(0)；没有截获字符串的组返回None；截获了多次的组返回最后一次截获的子串。
2. `groups([default])`: 
以元组形式返回全部分组截获的字符串。相当于调用group(1,2,…last)。default表示没有截获字符串的组以这个值替代，默认为None。
3. `groupdict([default])`: 
返回以有别名的组的别名为键、以该组截获的子串为值的字典，没有别名的组不包含在内。default含义同上。
4. `start([group])`: 
返回指定的组截获的子串在string中的起始索引（子串第一个字符的索引）。group默认值为0。
5. `end([group])`: 
返回指定的组截获的子串在string中的结束索引（子串最后一个字符的索引+1）。group默认值为0。
6. `span([group])`: 
返回(start(group), end(group))。
7. `expand(template)`: 
将匹配到的分组代入template中然后返回。template中可以使用\id或\g<id>、\g<name>引用分组，但不能使用编号0。\id与\g<id>是等价的；但\10将被认为是第10个分组，如果你想表达\1之后是字符'0'，只能使用\g<1>0。

	
		import re
		m = re.match(r'(\w+) (\w+)(?P<sign>.*)', 'hello world!')
 
		print "m.string:", m.string
		print "m.re:", m.re
		print "m.pos:", m.pos
		print "m.endpos:", m.endpos
		print "m.lastindex:", m.lastindex
		print "m.lastgroup:", m.lastgroup
  
		print "m.group(1,2):", m.group(1, 2)
		print "m.groups():", m.groups()
		print "m.groupdict():", m.groupdict()
		print "m.start(2):", m.start(2)
		print "m.end(2):", m.end(2)
		print "m.span(2):", m.span(2)
		print r"m.expand(r'\2 \1\3'):", m.expand(r'\2 \1\3')
		
		#$ python test.py 
		"""
		m.string: hello world!
		m.re: <_sre.SRE_Pattern object at 0x10fd129c0>
		m.pos: 0
		m.endpos: 12
		m.lastindex: 3
		m.lastgroup: sign
		m.group(1,2): ('hello', 'world')
		m.groups(): ('hello', 'world', '!')
		m.groupdict(): {'sign': '!'}
		m.start(2): 6
		m.end(2): 11
		m.span(2): (6, 11)
		m.expand(r'\2 \1\3'): world hello!
		"""

>除了 match 函数，还有 search 函数。  
match 函数只匹配字符串的开始，如果字符串开始不符合正则表达式，则匹配失败，函数返回None；而 search 匹配整个字符串，直到找到一个匹配。



__3. Pattern__  
Pattern对象是一个编译好的正则表达式，通过Pattern提供的一系列方法可以对文本进行匹配查找。

Pattern不能直接实例化，必须使用re.compile()进行构造。

Pattern提供了几个可读属性用于获取表达式的相关信息：

* pattern: 编译时用的表达式字符串。
* flags: 编译时用的匹配模式。数字形式。
* groups: 表达式中分组的数量。
* groupindex: 以表达式中有别名的组的别名为键、以该组对应的编号为值的字典，没有别名的组不包含在内。

举个例子： 
		
	import re
		
	p = re.compile(r'(\w+)(\w+)(?P<sign>.*)', re.DOTALL)

	print "p.pattern: ", p.pattern
	print "p.flags:", p.flags
	print "p.groups:", p.groups
	print "p.groupindex:", p.groupindex
	
Pattern提供的匹配方法：  

1. `match(string[, pos[, endpos]]) | re.match(pattern, string[, flags])`: 
这个方法将从string的pos下标处起尝试匹配pattern；如果pattern结束时仍可匹配，则返回一个Match对象；如果匹配过程中pattern无法匹配，或者匹配未结束就已到达endpos，则返回None。 
pos和endpos的默认值分别为0和len(string)；re.match()无法指定这两个参数，参数flags用于编译pattern时指定匹配模式。 
2. `search(string[, pos[, endpos]]) | re.search(pattern, string[, flags])`: 
这个方法用于查找字符串中可以匹配成功的子串。从string的pos下标处起尝试匹配pattern，如果pattern结束时仍可匹配，则返回一个Match对象；若无法匹配，则将pos加1后重新尝试匹配；直到pos=endpos时仍无法匹配则返回None。 
pos和endpos的默认值分别为0和len(string))；re.search()无法指定这两个参数，参数flags用于编译pattern时指定匹配模式。 
3. `split(string[, maxsplit]) | re.split(pattern, string[, maxsplit])`: 
按照能够匹配的子串将string分割后返回列表。maxsplit用于指定最大分割次数，不指定将全部分割。 
4. `findall(string[, pos[, endpos]]) | re.findall(pattern, string[, flags])`: 
搜索string，以列表形式返回全部能匹配的子串。 
5. `finditer(string[, pos[, endpos]]) | re.finditer(pattern, string[, flags])`: 
搜索string，返回一个顺序访问每一个匹配结果（Match对象）的迭代器。 
6. `sub(repl, string[, count]) | re.sub(pattern, repl, string[, count])`: 
使用repl替换string中每一个匹配的子串后返回替换后的字符串。 
当repl是一个字符串时，可以使用\id或\g<id>、\g<name>引用分组，但不能使用编号0。 
当repl是一个方法时，这个方法应当只接受一个参数（Match对象），并返回一个字符串用于替换（返回的字符串中不能再引用分组）。 
count用于指定最多替换次数，不指定时全部替换。 
7. `subn(repl, string[, count]) |re.sub(pattern, repl, string[, count])`: 
返回 (sub(repl, string[, count]), 替换次数)。 



__4. 反斜杠的问题__   
与大多数编程语言相同，正则表达式里使用"\"作为转义字符，这就可能造成反斜杠困扰。Python里的原生字符串很好地解决了这个问题，反斜杠的表示"\\"在正则表达式可以使用r"\"表示。

同样，匹配一个数字的"\\d"可以写成r"\d"。



__5. 正则表达式__   

|元字符| 描述|
|-------|------|
|\\ | 将下一个字符标记符、或一个向后引用、或一个八进制转义符。例如，“\\\\n”匹配\\n。“\\n”匹配换行符。序列“\\\\”匹配“\\”而“\\(”则匹配“(”。即相当于多种编程语言中都有的“转义字符”的概念。|
|^|匹配输入字符串的开始位置。如果设置了RegExp对象的Multiline属性，^也匹配“\\n”或“\\r”之后的位置。|
|\$|匹配输入字符串的结束位置。如果设置了RegExp对象的Multiline属性，\$也匹配“\\n”或“\\r”之前的位置。|
|\*|匹配前面的子表达式任意次。例如，zo\*能匹配“z”，也能匹配“zo”以及“zoo”。|
|+|匹配前面的子表达式一次或多次(大于等于1次）。例如，“zo+”能匹配“zo”以及“zoo”，但不能匹配“z”。+等价于{1,}。|
|?|匹配前面的子表达式零次或一次。例如，“do(es)?”可以匹配“do”或“does”中的“do”。?等价于{0,1}。|
|{n}|n是一个非负整数。匹配确定的n次。例如，“o{2}”不能匹配“Bob”中的“o”，但是能匹配“food”中的两个o。|
|{n,}|n是一个非负整数。至少匹配n次。例如，“o{2,}”不能匹配“Bob”中的“o”，但能匹配“foooood”中的所有o。“o{1,}”等价于“o+”。“o{0,}”则等价于“o\*”。|
|{n,m}|m和n均为非负整数，其中n<=m。最少匹配n次且最多匹配m次。例如，“o{1,3}”将匹配“fooooood”中的前三个o。“o{0,1}”等价于“o?”。请注意在逗号和两个数之间不能有空格。|
|?|当该字符紧跟在任何一个其他限制符（\*,+,?，{n}，{n,}，{n,m}）后面时，匹配模式是非贪婪的。非贪婪模式尽可能少的匹配所搜索的字符串，而默认的贪婪模式则尽可能多的匹配所搜索的字符串。例如，对于字符串“oooo”，“o+”将尽可能多的匹配“o”，得到结果[“oooo”]，而“o+?”将尽可能少的匹配“o”，得到结果 ['o', 'o', 'o', 'o']|
|.点|匹配除“\r\n”之外的任何单个字符。要匹配包括“\r\n”在内的任何字符，请使用像“[\s\S]”的模式。|
|(pattern)|匹配pattern并获取这一匹配。所获取的匹配可以从产生的Matches集合得到，在VBScript中使用SubMatches集合，在JScript中则使用\$0…\$9属性。要匹配圆括号字符，请使用“\\(”或“\\)”。|
|(?:pattern)|非获取匹配，匹配pattern但不获取匹配结果，不进行存储供以后使用。这在使用或字符“(\|)”来组合一个模式的各个部分时很有用。例如“industr(?:y\|ies)”就是一个比“industry\|industries”更简略的表达式。|
|(?=pattern)|非获取匹配，正向肯定预查，在任何匹配pattern的字符串开始处匹配查找字符串，该匹配不需要获取供以后使用。例如，“Windows(?=95|98|NT|2000)”能匹配“Windows2000”中的“Windows”，但不能匹配“Windows3.1”中的“Windows”。预查不消耗字符，也就是说，在一个匹配发生后，在最后一次匹配之后立即开始下一次匹配的搜索，而不是从包含预查的字符之后开始。|
|(?!pattern)|非获取匹配，正向否定预查，在任何不匹配pattern的字符串开始处匹配查找字符串，该匹配不需要获取供以后使用。例如“Windows(?!95\|98\|NT\|2000)”能匹配“Windows3.1”中的“Windows”，但不能匹配“Windows2000”中的“Windows”。|
|(?<=pattern)|非获取匹配，反向肯定预查，与正向肯定预查类似，只是方向相反。例如，“(?<=95\|98\|NT\|2000)Windows”能匹配“2000Windows”中的“Windows”，但不能匹配“3.1Windows”中的“Windows”。|
|(?<!pattern)|非获取匹配，反向否定预查，与正向否定预查类似，只是方向相反。例如“(?<!95\|98\|NT\|2000)Windows”能匹配“3.1Windows”中的“Windows”，但不能匹配“2000Windows”中的“Windows”。这个地方不正确，有问题此处用或任意一项都不能超过2位，如“(?<!95\|98\|NT\|20)Windows正确，“(?<!95\|980\|NT\|20)Windows 报错，若是单独使用则无限制，如(?<!2000)Windows 正确匹配|
|x\|y|匹配x或y。例如，“z\|food”能匹配“z”或“food”(此处请谨慎)。"[z&brvbar;f]ood" 则匹配“zood”或“food”或"\|ood"。|
|[xyz]|字符集合。匹配所包含的任意一个字符。例如，“[abc]”可以匹配“plain”中的“a”。|
|[^xyz]|负值字符集合。匹配未包含的任意字符。例如，“[^abc]”可以匹配“plain”中的“plin”。|
|[a-z]|字符范围。匹配指定范围内的任意字符。例如，“[a-z]”可以匹配“a”到“z”范围内的任意小写字母字符。注意:只有连字符在字符组内部时,并且出现在两个字符之间时,才能表示字符的范围; 如果出字符组的开头,则只能表示连字符本身.|
|[^a-z]|负值字符范围。匹配任何不在指定范围内的任意字符。例如，“[^a-z]”可以匹配任何不在“a”到“z”范围内的任意字符。|
|\\b|匹配一个单词边界，也就是指单词和空格间的位置（即正则表达式的“匹配”有两种概念，一种是匹配字符，一种是匹配位置，这里的\\b就是匹配位置的）。例如，“er\\b”可以匹配“never”中的“er”，但不能匹配“verb”中的“er”。|
|\\B|匹配非单词边界。“er\\B”能匹配“verb”中的“er”，但不能匹配“never”中的“er”。|
|\cx|匹配由x指明的控制字符。例如，\cM匹配一个Control-M或回车符。x的值必须为A-Z或a-z之一。否则，将c视为一个原义的“c”字符。|
|\\d|匹配一个数字字符。等价于[0-9]。grep 要加上-P，perl正则支持|
|\\D|匹配一个非数字字符。等价于[^0-9]。grep要加上-P，perl正则支持|
|\\f|匹配一个换页符。等价于\\x0c和\\cL。|
|\\n|匹配一个换行符。等价于\\x0a和\\cJ。|
|\\r|匹配一个回车符。等价于\\x0d和\\cM。|
|\\s|匹配任何不可见字符，包括空格、制表符、换页符等等。等价于[ \\f\\n\\r\\t\\v]。|
|\\S|匹配任何可见字符。等价于[^ \\f\\n\\r\\t\\v]。|
|\\t|匹配一个制表符。等价于\\x09和\\cI。|
|\\v|匹配一个垂直制表符。等价于\\x0b和\\cK。|
|\\w|匹配包括下划线的任何单词字符。类似但不等价于“[A-Za-z0-9_]”，这里的"单词"字符使用Unicode字符集。|
|\\W|匹配任何非单词字符。等价于“[^A-Za-z0-9_]”。|
|\\xn|匹配n，其中n为十六进制转义值。十六进制转义值必须为确定的两个数字长。例如，“\\x41”匹配“A”。“\\x041”则等价于“\\x04&1”。正则表达式中可以使用ASCII编码。|
|\\num|匹配num，其中num是一个正整数。对所获取的匹配的引用。例如，“(.)\\1”匹配两个连续的相同字符。|
|\\n|标识一个八进制转义值或一个向后引用。如果\\n之前至少n个获取的子表达式，则n为向后引用。否则，如果n为八进制数字（0-7），则n为一个八进制转义值。|
|\\nm|标识一个八进制转义值或一个向后引用。如果\\nm之前至少有nm个获得子表达式，则nm为向后引用。如果\\nm之前至少有n个获取，则n为一个后跟文字m的向后引用。如果前面的条件都不满足，若n和m均为八进制数字（0-7），则\\nm将匹配八进制转义值nm。|
|\\nml|如果n为八进制数字（0-7），且m和l均为八进制数字（0-7），则匹配八进制转义值nml。|
|\\un|匹配n，其中n是一个用四个十六进制数字表示的Unicode字符。例如，\\u00A9匹配版权符号（&copy;）。|
|\\p{P}|小写 p 是 property 的意思，表示 Unicode 属性，用于 Unicode 正表达式的前缀。中括号内的“P”表示Unicode 字符集七个字符属性之一：标点字符。</br>其他六个属性：L：字母；</br>M：标记符号（一般不会单独出现）；</br>Z：分隔符（比如空格、换行等）；</br>S：符号（比如数学符号、货币符号等）；</br>N：数字（比如阿拉伯数字、罗马数字等）；</br>C：其他字符。</br>*注：此语法部分语言不支持，例：javascript。|
|\\< \\>|匹配词（word）的开始（\<）和结束（\>）。例如正则表达式\<the\>能够匹配字符串"for the wise"中的"the"，但是不能匹配字符串"otherwise"中的"the"。注意：这个元字符不是所有的软件都支持的。|
|( )|	将( 和 ) 之间的表达式定义为“组”（group），并且将匹配这个表达式的字符保存到一个临时区域（一个正则表达式中最多可以保存9个），它们可以用 \1 到\9 的符号来引用。|
|\||	将两个匹配条件进行逻辑“或”（Or）运算。例如正则表达式(him\|her) 匹配"it belongs to him"和"it belongs to her"，但是不能匹配"it belongs to them."。注意：这个元字符不是所有的软件都支持的。|
|+|	匹配1或多个正好在它之前的那个字符。例如正则表达式9+匹配9、99、999等。注意：这个元字符不是所有的软件都支持的。|
|?|	匹配0或1个正好在它之前的那个字符。注意：这个元字符不是所有的软件都支持的。|
|{i} {i,j}|	匹配指定数目的字符，这些字符是在它之前的表达式定义的。例如正则表达式A[0-9]{3} 能够匹配字符"A"后面跟着正好3个数字字符的串，例如A123、A348等，但是不匹配A1234。而正则表达式[0-9]{4,6} 匹配连续的任意4个、5个或者6个数字|




</br>

--------------------------------  
References:  
菜鸟教程:  <http://www.runoob.com/python/python-tutorial.html>   
CSDN.AstralWind:  <http://www.cnblogs.com/huxi/archive/2010/07/04/1771073.html>  
</br>
Author: xx  
Time: 2017.2.20  