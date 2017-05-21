# Caesar Code  

---------------------------------------------  

### 0x00 前言  
一个 `Python` 写的解码 凯撒密码 的脚本。

### 0x01 正文
凯撒密码作为一种最为古老的对称加密体制，在古罗马的时候都已经很流行，他的基本思想是：通过把字母移动一定的位数来实现加密和解密。明文中的所有字母都在字母表上向后（或向前）按照一个固定数目进行偏移后被替换成密文。例如，当偏移量是3的时候，所有的字母A将被替换成D，B变成E，以此类推X将变成A，Y变成B，Z变成C。由此可见，位数就是凯撒密码加密和解密的密钥。

__For Example:__  
明文：  `This is apple`   

通过凯撒密码的方式移位13位(Rot13):    
`Guvf vf nccyr`

解密时，移位等于 `26 - 13 = 13`，再通过凯撒移位的方式移动13位就得到了明文。


### 0x02 脚本  

	#! /usr/bin/python
	#! coding=utf-8

	"""
	@Description: Caesar code decode program.
	@Author: xx
	@Time: 2017.5.21
	"""

	def decodeCaesarCode():
	    encodeStr = raw_input("Input string you want to decode:\n")
	    length = len(encodeStr)

	    for i in range(26):
	        s = ""
	        for j in range(length):
	            ch = ord(encodeStr[j])
	            if (ord(encodeStr[j]) >= 65) and (ord(encodeStr[j]) <= 90) or (ord(encodeStr[j]) >= 97) and (ord(encodeStr[j]) <= 122):
	                ch = ord(encodeStr[j]) + i
	                if(ord(encodeStr[j]) <= 90 and ch > 90) or (ord(encodeStr[j]) >= 97 and ch > 122):
	                    ch = ch - 26

	            #merge
	            s = s + chr(ch)

	        print "Rot " + str(i) + ":\t" + s

	if __name__ == "__main__":
	    decodeCaesarCode()


---------------------------------------------
Author: xx  
Time: 2017.5.21