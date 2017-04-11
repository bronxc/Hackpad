#Python unzip  

----------------------------------  

###0x00  
用 python 解压的一个小样例。

###0x01  

	#coding=utf-8

	#Using: unzip
	#Author: xx
	#Time: 2016.11.1

	import os
	import sys
	import time
	import zipfile
	
	filename = '1.zip'
	filedir = 'data/'
	
	r = zipfile.is_zipfile(filename)
	if r:	
	    startTime = time.time()
	    fz = zipfile.ZipFile(filename, 'r')
	    for file in fz.namelist():
	        print(file)
	        fz.extract(file, filedir)   #unzip name is 'file' file to 'filedir' 
	        endTime = time.time()
	        times = endTime - startTime
	else:
	   	 print('This file is not zip file')
	print('times:' + str(times))








----------------------------------
References:  

Author: xx  
Time: 2016.11.1