#Python Json  

------------------------------  

### 0x00 前言  
介绍在 Python 对 Json 数据的处理。


### 0x01 正文  
编码：把一个Python对象编码转换成Json字符串   `json.dumps()`  
解码：把Json格式字符串解码转换成Python对象   `json.loads()`  

Python原始类型和Json数据类型的转化：  

|Python|Json|
|--------|--------|
|dict|object|
|list, tuple| array|
|str, unicode| string|
|int, long, float|number|
|True|true|
|False|false|
|None|null|

举个例子：  

	#! /usr/bin/python
	# coding=utf-8

	import json

	#将字符串转化为Json 对象，这里只能是字符串类型
	jsonObj = json.loads('{"name": "test", "type": {"name": "sub", "parameter": ["1", "2"]}}')
	print type(jsonObj)
	print jsonObj["type"]

	#将Json对象转化为字符串
	strObj = json.dumps(jsonObj)
	print type(strObj)
	print strObj
	
	#$ python test.py 
	"""
	<type 'dict'>
	{u'parameter': [u'1', u'2'], u'name': u'sub'}
	<type 'str'>
	{"type": {"parameter": ["1", "2"], "name": "sub"}, "name": "test"}
	"""




</br>

----------------------------
References:  
菜鸟教程:  <http://www.runoob.com/python/python-tutorial.html>  
cnblogs.jihite:  <http://www.cnblogs.com/kaituorensheng/p/3877382.html>   
</br>
Author: xx  
Time: 2017.2.20