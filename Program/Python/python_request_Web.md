#Python 访问网页方式  

----------------------------------------------
  
###0x00 简介
下面总结了python两种访问网页的方式，一种是使用urllib2包，另一种是使用request包  
  
###0x01 正文  
用于测试的网页，搭建在wamp上的一个php网页，功能是提交一个参数，返回参数的值，并在header中返回cookie值和token。  
__SourceCode__：  

1. index.php

		<html>			<head>				<title>Test For Py</title>			</head>			<body>				<form name="form1" action="response.php" method="GET">					<input type="text" name="value">					<input type="submit" value="Submit">				</form>			</body>		</html>
	
2. response.php  

		<?php			error_reporting(0);			header("Content-type: text/html; charset=utf-8");			header('token:JxRaZezavm3HXM3d9pWnYiqqQC1SJbsU');				setcookie("user", "Alex Porter", time()+3600);					$getValue = $_GET['value'];			$postValue = $_POST['post_value'];			echo "Get Value: ".$getValue."</br>";			echo "Post Value: ".$postValue."</br>";			echo "Cookie: ".$_COOKIE["user"]."</br>";					$arr = array('a' => 1, 'b' => 2, 'c' => 3, 'd' => 4, 'e' => 5);			echo "Json: ".json_encode($arr)."</br>";					echo "</br></br></br>Request Header: </br>";			foreach (getallheaders() as $name => $value) { 				echo "$name: $value"."</br>"; 			}				?>
	
###0x02 urllib2 类型  
1. 基本访问   

		import urllib2
		
		url = "http://10.211.55.11/"
		response = urllib2.urlopen(url)
		print response.read()


2. 获取header内容   

		import urllib2

		url = "http://10.211.55.11/"
		response = urllib2.urlopen(url)
		print response.info()

	>提取`header`某一项：  
	
		import urllib2

		url = "http://10.211.55.11/"
		response = urllib2.urlopen(url)
		print response.info().getheader("Server")

3. 传递参数  
>Get 型  

	在`url`中构造参数：  
	
		import urllib2

		url = "http://10.211.55.11/response.php?value=aa"
		response = urllib2.urlopen(url)
		print response.read()

	>Post 型  
	
		import urllib
		import urllib2

		url = "http://10.211.55.11/response.php"
		values = {"post_value" : "This Post"}
		data = urllib.urlencode(values)
		request = urllib2.Request(url, data)
		response = urllib2.urlopen(request)
		print response.read()


4. 自定义header值访问    

		import urllib
		import urllib2

		url = "http://10.211.55.11/response.php"
		values = {"post_value" : "This Post"}
		data = urllib.urlencode(values)
		header = {"Cookie" : "This is new Cookie"}
		request = urllib2.Request(url, data, header)
		response = urllib2.urlopen(request)
		print response.read()

	或者：  
	
		import urllib
		import urllib2

		url = "http://10.211.55.11/response.php"
		request = urllib2.Request(url)
		request.add_header("Cookie", "This is new Cookie")
		response = urllib2.urlopen(request)
		print response.read()


###0x03 request 类型
1. 基本访问   

		import requests

		url = "http://10.211.55.11/index.php"
		response = requests.get(url)
		print response.text

	>还有一些其他请求方式，分别对应不同的请求方式，请看下文档  
	>requests.post(url)  
	>r = requests.put(url)  
	>r = requests.delete(url)  
	>r = requests.head(url)  
	>r = requests.options(url)  

2. 获取header内容   

		import requests

		url = "http://10.211.55.11/response.php"
		response = requests.get(url)
		print response.headers

	>返回的`header`信息是字典形式，直接取出来：  
	
		import requests

		url = "http://10.211.55.11/response.php"
		response = requests.get(url)
		print response.headers["token"]

3. 传递参数  

	>Get 型
	
		import requests

		url = "http://10.211.55.11/response.php"
		payload = {"value" : "Get test"}
		response = requests.get(url, params=payload)
		print response.text
	
	>Post 型
	
		import requests

		url = "http://10.211.55.11/response.php"
		payload = {"post_value" : "Post test"}
		response = requests.post(url, data=payload)
		#print response.url
		print response.text

4. 自定义header值访问

		import requests

		url = "http://10.211.55.11/response.php"
		headers = {"User-Agent" : "I am test"}
		response = requests.get(url, headers=headers)
		print response.text








</br>

---------------------------------  
参考资料：  
python中文开发者社区：  <http://www.pythontab.com/html/2014/pythonhexinbiancheng_1128/928.html>
CSDN.Alpha5的专栏： <http://blog.csdn.net/alpha5/article/details/24964009> 

</br>
Author: xx  
Time: 2016.10.25


