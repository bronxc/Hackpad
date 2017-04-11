# Python Mysql 

--------------------------   
### 0x00 前言  
Python 标准数据库接口为 Python DB-API，Python DB-API为开发人员提供了数据库应用编程接口。  
Python 数据库接口支持非常多的数据库，你可以选择适合你项目的数据库：  

* GadFly
* mSQL
* MySQL
* PostgreSQL
* Microsoft SQL Server 2000
* Informix
* Interbase
* Oracle
* Sybase

你可以访问Python数据库接口及API查看详细的支持数据库列表。  
不同的数据库你需要下载不同的DB API模块，例如你需要访问Oracle数据库和Mysql数据，你需要下载Oracle和MySQL数据库模块。  
DB-API 是一个规范. 它定义了一系列必须的对象和数据库存取方式, 以便为各种各样的底层数据库系统和多种多样的数据库接口程序提供一致的访问接口 。  
Python的DB-API，为大多数的数据库实现了接口，使用它连接各数据库后，就可以用相同的方式操作各数据库。  



### 0x01 目录 

1. MySQLdb模块  
2. 连接数据库  
3. 执行语句  
4. 数据库的查询操作   


### 0x02 正文  
__1. MySQLdb模块__  
要通过 Python 使用 Mysql，需要先安装 MySQLdb模块。  

	#!/usr/bin/python
	# -*- coding: UTF-8 -*-

	import MySQLdb
	
运行后哦，若没有出现异常，则代表 MySQLdb 模块已经安装好。


__2. 连接数据库__  
先创建运行环境：  

* 创建 Test 数据库  
* 创建 table1 表，有字段 id(int), str(varchar(20))  
* 数据库用户名 root， 密码为空  
* 已经安装 MySQLdb 模块  

举个例子：  

	#!/usr/bin/python	# -*- coding: UTF-8 -*-	import MySQLdb	# 打开数据库连接	db = MySQLdb.connect("localhost","root","","Test")	# 使用cursor()方法获取操作游标 	cursor = db.cursor()	# 使用execute方法执行SQL语句	cursor.execute("SELECT VERSION()")	# 使用 fetchone() 方法获取一条数据库。	data = cursor.fetchone()	print "Database version : %s " % data	# 关闭数据库连接	db.close()
	
	#Python test.py
	#Database version : 5.7.14



__3. 执行语句__  
在 Python 中执行 SQL 语句是通过 `execute` 来执行的。  

对于支持事务的数据库， 在Python数据库编程中，当游标建立之时，就自动开始了一个隐形的数据库事务。  
commit()方法游标的所有更新操作，rollback（）方法回滚当前游标的所有操作。每一个方法都开始了一个新的事务。  

举个例子，向 Test 表插入一条记录：  

	#!/usr/bin/python	# -*- coding: UTF-8 -*-	import MySQLdb	db = MySQLdb.connect("localhost","root","","Test")	cursor = db.cursor()	sql = "insert into table1(id, str) values('%d', '%s')" % (1, "a")	try:		cursor.execute(sql)		db.commit()	except:		db.rollback()	db.close()



__4. 数据库的查询操作__   
当进行查询操作时，进行对结果集的遍历，Python查询Mysql使用 fetchone() 方法获取单条数据, 使用fetchall() 方法获取多条数据。  

* fetchone(): 该方法获取下一个查询结果集。结果集是一个对象
* fetchall():接收全部的返回结果行.
* rowcount: 这是一个只读属性，并返回执行execute()方法后影响的行数。

举个例子：  

	#!/usr/bin/python	# -*- coding: UTF-8 -*-	import MySQLdb	db = MySQLdb.connect("localhost","root","","Test")	cursor = db.cursor()	sql = "select * from table1"	try:		cursor.execute(sql)		results = cursor.fetchall()		for row in results:			id = row[0]			str = row[1]			print "id=%d, str=%s" % (id, str)		except:		print "execute error"	db.close()
	
	#Python test.py
	#id=1, str=a
	#id=2, str=b




</br>

----------------------------
References:  
菜鸟教程:  <http://www.runoob.com/python/python-tutorial.html>  
</br>
Author: xx  
Time: 2017.2.20