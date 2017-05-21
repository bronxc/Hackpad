# The Rail Fence Cipher  

------------------------------------------------

### 0x00 前言  
一个 `python` 解密栅栏密码的脚本。

### 0x01 正文  
所谓栅栏密码，就是把要加密的明文分成N个一组，然后把每组的第1个字连起来，形成一段无规律的话。  

__For example：__  
`This is big apple`  

以 2栏栅栏密码为例，去掉空格后组成：  
`Thisisbigapple`  

分为两栏一组后：  
	
	Th
	is
	is
	bi
	ga
	pp
	le
	
把每组的第一个字符按顺序连接起来：  
`Tiibgplhssiape`

解密时，将密文分为两组：  

	Tiibgpl
	hssiape
	
按照每组的第一个字符按顺序连接起来就还原了。


### 0x02 Script  

	#! /usr/bin/python
	#! coding=utf-8

	"""
	Description: The rail fence cipher
	Author: xx
	Time: 2017.5.21
	"""

	def decodeRailFence():
	    encodeStr = raw_input("Input string you want to decode:\n")
	    length = len(encodeStr)
	    group = []
	    for i in range(2, length):
	        if(length%i == 0):
	            group.append(i);

	    for i in group:
	        num = length / i
	        result = {x: "" for x in range(num)}
	        for j in range(length):
	            posi = j % num
	            result.update({posi: result[posi]+encodeStr[j]})

	        s = ""
	        for j in range(num):
	            s = s + result[j]
	        print "split by " + str(i) + ":\t" + s

	if __name__ == "__main__":
	    decodeRailFence()



----------------------------------------------  
Author: xx  
Time: 2017.5.21