#Bash Shell Syntax


###0x01 简介
因为使用linux的情况越来越多，为提高工作效率，下面是一些对Bash Shell编程的入门知识。以下内容建立在一定的脚本编程基础上，与其它脚本通用的内容不再累述。


###0x02 Bash Shell
1. 一个简单的Bash Shell程序
2. 变量声明
3. 整数运算符
4. 逻辑运算符
5. 流程语句
6. 循环语句
7. 数组  
8. 函数
9. 特殊的变量





-------------------------
###### 1.一个简单的Bash Shell程序

	#!/bin/bash
	#Hello World
	echo "Hello World"

run result:  
Hello World  
上面是一个简单的HelloWorld的输出，`#!/bin/bash`是表示在系统执行这个脚本时，使用哪一个Shell（默认的是Bash），每一个shell脚本第一句都应该声明。`#`是shell脚本中的注释  


###### 2.变量声明
变量＝值(等号两边不能有空格)  
a="Hello"  
b=9  
unset a 撤销a变量  
readonly a=2  声明静态变量a，不能unset  
export a  将一个变量提升为全局变量

<strong>Notice:</strong>  
1.在使用变量的地方必须加上$,比如`echo $a`  
2.单引号和双引号对变量的影响，单引号完全屏蔽变量(即不解析变量)，双引号可以解析变量  
3.变量可以获取命令的执行结果，比如 `a='ls'`  
4.当变量与字符串连接时，变量应该使用 ${variable}，比如 `${SAT}Day`  

<strong>Code</strong>  

	#!/bin/bash
	#Variable
	a="Hello"
	b=9
	SAT="Sunday"
	echo $a
	echo ${SAT}Day
	echo "$b"
	echo '$b'
	
run result:  
Hello  
SundayDay  
9  
$b  



###### 3.整数运算符
整数的算术运算符  
+ － * / %   
赋值运算符   
＋＝ －＝ * ＝ / ＝ ％＝   
位运算符   
<< >> & | ~ ^   
位运算赋值运算符   
<< ＝ >> ＝ & ＝ | ＝ ~ ＝ ^ ＝   
逻辑运算符：   
&& || ! > > ＝ < < ＝ !＝ ＝＝  

使用expr来计算一个表达式的值，格式 `expr arg`，比如 `expr 2 + 3`  
或者使用let来计算表达式的值，比如 `let "x=$x + 1"`  

<strong>Notice</strong>  
1.运算符号和参数之间要有空格分开  


<strong>Code</strong>  

	#!/bin/bash
	#Operation
	a=`expr 2 + 3`
	b=2
	let "b=$b + 2"
	c=6
	d=2
	let "d=$c * $d"
	echo $a 
	echo $b
	echo $d
	
run result:  
5  
4  
12  



###### 4.逻辑运算符  
相同 -eq =   
不同 -ne !=   
大于 -gt >   
小于 -lt <   
大于或等于 -ge   
小于或等于 -le   
为空 -z   
不为空 -n  
逻辑运算连接符 &&与，||或

文件操作逻辑运算符：  
-d file ----当file是一个目录时,返回 True   
-f file ----当file是一个普通文件时,返回 True   
-r file ----当file是一个只读文件时,返回 True   
-s file ----当file文件长度大于0时,返回 True   
-w file ----当file是一个可写文件时,返回 True   
-x "/bin/ls" ----当/bin/ls是一个可执行文件时,返回 True，目录是否可访问  
-e file ----当file存在时,返回True   
-o file ----当file文件的所有者是当前用户时,返回True   
-z file ----当file长度为0时,返回True   
-u -----文件的 UID 标志被设置  
-G -----文件的组 ID 和当前用户相同  
file1 -nt file2 -----文件 file1 比 file2 更新  
file1 -ot file2 -----文件 file1 比 file2 更老  


<strong>Code</strong>  
ps:下面的测试使用了if语句

	#!/bin/bash
	#Logic
	a=2
	if [ $a = 2 ]; then
		echo "= test"
	fi
	if [ $a -ne 3 ]; then
		echo "-ne test"
	fi
	
	rout="/bin/ls"
	if [ -x $rout ]; then
		echo "-x test"
	fi
	
	b=3
	c=2
	if [ $b -eq 3 ] || [$c -eq 2]; then
		echo "|| test"
	fi

run result:  
= test  
-ne test  
-x test  
|| test  



###### 5.流程语句  
<strong>5.1if语句</strong>  
	
	if [ 逻辑表达式 ]; then   //这里需要注意：if和[之间必须有空格，[和逻辑表达式之间也必须有空格，表达式和]必须有空格 
		#command code  
	elif [ 逻辑表达式 ]; then  
		#commandcode  
	else  
		#commandcode  
	fi  
  
<strong>5.2case语句</strong>  
	
	case string1 in   
		str1) commands1;;   
		str2) commands2;;   
		*) commands3;;   
	esac  
  
<strong>5.3select语句</strong>  

	select var in ... ; do  
		break  
	done  



<strong>Code</strong>  

	#!/bin/bash
	#if case select
	a=2
	b=3
	c=4
	d=3
	#if
	if [ $a -eq 2 ]; then
		echo "a is 2"
	elif [ $b -eq 3 ]; then
		echo "b is 3"
	else
		echo "else code"
	fi
	#case
	case $d in 
		$a) echo "d equal a";;
		$b) echo "d equal b";;
		*) echo "other code";;
	esac
	#select
	select yourse in "Linux" "CentOS"; do
		break;
	done
	echo "your select is $yourse"

run result:  
a is 2  
d equal b  
1) Linux  
2) CentOS  
 #? 1  
your select is Linux  




###### 循环语句
**6.1for语句**  
	
	for var in 数组列表; do
		#command bolock
	done

**6.1while语句**

	while [ express ]; do
		#command
	Done
	
**Code**

	#!/bin/bash
	#loop
	for i in A B C; do
		echo $i
	done

	i=0
	while [ $i -lt 5 ]; do
		echo $i
		let "i=$i + 1"
	done

run result:  
A  
B  
C  
0  
1  
2  
3  
4  


**6.3break语句和continue语句**  
关键字"break" 用来跳出循环。而关键字”continue”用来不执行余下的部分而直接跳到下一个循环。  

**6.4shift语句**  
将存放在位置变量中的命令行参数,依次向左传递  
比如：位置变量当前值为: $1=file1 $2=file2 $3=file3 执行一次shift命令后,位置量的值为: $1=file2 $2=file3   
格式 `shift n`  



######7.数组
数组的定义：  
array=("Tom" "Mary" "John")  //注意两个元素之间的空格
或  
array[0]="Tom"
array[1]="Mary"  

数组的遍历：  

	for i in 0 1 2; do
		echo $i:${array[$i]}


**Code**

	#!/bin/bash
	#array
	array=("Tom" "Mary" "John")
	#array[0]="Tom"
	#array[1]="Mary"
	#array[2]="John"
	
	for i in 0 1 2; do
		echo ${array[$i]}
	done
	
	for i in ${array[@]}; do
		echo $i
	done
	
run result:  
Tom  
Mary  
John  
Tom  
Mary  
John  



###### 8.函数
函数的定义和调用

	help() {
		echo "show help function"
	}
	help



..E,这个就不演示了哈。－ －  
可以使用函数和case，实现脚本参数运行




###### 9.特殊的变量  
$0:脚本名字。此变量包含地址，可以使用basename $0获得脚本名称。  
$1:第一个参数  
$2,$3,$4,$5,...一次类推。  
$# 传递到脚本的参数个数  
$* 以一个单字符串显示所有向脚本传递的参数，,以("$1 $2...")   
$$ 脚本运行的ID号  
$! 后台运行的最后一个进程的ID号  
$@ 与$*相同，但是使用时加引号，并在引号中返回每个参数。("$1""$2"...)   
$- 显示shell使用的当前选项。  
$? 显示最后命令的推出状况。0表示没有错误。  




###### 10.字符串处理  
${#string} $string的长度  
${string:position} 在$string中，从位置$position开始提取子串  
${string:position:length} 在$string中，从位置$position开始提取长度为$length的子串  
${string#\*substring} 从变量$string的开头，删除第一个匹配$substring的子串的左边    
${string##\*substring} 从变量$string的开头，删除最后一个匹配$substring的子串的左边  
${string%\*substring} 从变量$string的结尾，删除第一个匹配$substring的子串的右边  
${string%%\*substring} 从变量$string的结尾，删除最后一个匹配$substring的子串的右边  
${string/old/new} 使用$new,来代替第一个匹配的$old  
${string//old/new} 使用$new,代替所有匹配的$old  
${string/#old/new} 替换开头．如果$string以$old开头，那么就用$new替换  
${string/%old/new} 替换结尾．如果$string以$old结尾，那么就用$new替换  



</br>

-------------------------------------  
Author: xx  
Time: 2016.8






