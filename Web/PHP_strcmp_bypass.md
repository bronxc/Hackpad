##PHP_strcmp bypass  

###0x01
#####strcmp安全问题出现  

在官方的文档有这么一端说明：

>Note a difference between 5.2 and 5.3 versions

>echo (int)strcmp('pending',array());
>will output -1 in PHP 5.2.16 (probably in all versions prior 5.3)
>but will output 0 in PHP 5.3.3

>Of course, you never need to use array as a parameter in string comparisions.

大概意思就是5.3的之前和之后版本在使用strcmp比较数组和字符串时候的差异。
在5.3的版本之后使用这个函数比较会返回0.  

###0x02
#####exmaple

示例代码：
```
<?php
	error_reporting(0);
	$key = "bypass";
	//key[] = 1;
	if($key !== $_GET['key']) {
		$result = strcmp($key, $_GET['key']);
		if($result == 0) {
			echo "flag";
		}
		else {
			echo "bad key!";
		}
	}
	else {
		echo "hello";
	}
?>
```
当传入GET参数，key[]=1时， 即可绕过strcmp。  

###0x03
#####strcmp拓展

php代码：
```
<?php
	echo "Test strcmp()" . "</br>";
	echo "</br>";
	
	echo "strcmp(NULL, 0) => " . strcmp(NULL, 0) . "</br>";
	echo "strcmp(false, -1) => " . strcmp(false, -1) . "</br>";
	echo "strcmp(\"15\", NULL) => " . strcmp("15", NULL) . "</br>";
	echo "strcmp(NULL, \"foo\") => " . strcmp(NULL, "foo") . "</br>";
	echo "strcmp(\"foo\", NULL) => " . strcmp("foo", NULL) . "</br>";
	echo "strcmp(\"foo\", false) => " . strcmp("foo", false) . "</br>";
	echo "strcmp(\"foo\", 0) => " . strcmp("foo", 0) . "</br>";
	echo "strcmp(\"foo\", 5) => " . strcmp("foo", 5) . "</br>";
	echo "</br>";
	
	echo "strcmp(\"5\", 5) => " . strcmp("5", 5) . "</br>";
	echo "strcmp(\"15\", 0xf) => " . strcmp("15", 0xf) . "</br>";
	echo "strcmp(61529519452809720693702583126814, 61529519452809720000000000000000) => " . strcmp(61529519452809720693702583126814, 61529519452809720000000000000000) . "</br>";
	echo "strcmp(NULL, false) => " . strcmp(NULL, false) . "</br>";
	echo "strcmp(NULL, \"\") => " . strcmp(NULL, "") . "</br>";
	echo "</br>";
	
	echo "strcmp(\"foo\", array()) => " . strcmp("foo", array()) . "</br>";	//=>NULL + PHP Warning
	echo "strcmp(\"foo\", new stdClass) => " . strcmp("foo", new stdClass) . "</br>";	//=>NULL + PHP Warning
	/*echo "strcmp(function(){}, "") => " . strcmp(function(){}, "") . "</br>";	//=>NULL + PHP Warning */
?>
```
上面代码运行结果：

>Test strcmp()

>strcmp(NULL, 0) => -1
strcmp(false, -1) => -2
strcmp("15", NULL) => 2
strcmp(NULL, "foo") => -3
strcmp("foo", NULL) => 3
strcmp("foo", false) => 3
strcmp("foo", 0) => 1
strcmp("foo", 5) => 1

>strcmp("5", 5) => 0
strcmp("15", 0xf) => 0
strcmp(61529519452809720693702583126814, 61529519452809720000000000000000) => 0
strcmp(NULL, false) => 0
strcmp(NULL, "") => 0


</br></br>
--------------------------------------
参考文献：  
lcx blog:<http://lcx.cc/?i=4244>