#Python crc32  

------------------


###0x00 简介  
做 CTF 题的时候遇到一个 MISC，需要爆破一个8位数字的 zip 密码，zip 上面又有 CRC32，于是想用 CRC32 试试：  

###0x01 正文  
python代码：

	import zlib

	for i in xrange(0, 100000000):
		buf = str(i).rjust(3, '0')

    	if zlib.crc32(buf) & 0xffffffff == 0x4c61e280:
        	print '[*]',buf
	   if i % 1000000 == 0:
      		print i



</br>

------------------
References:  

</br>
Author: xx  
Time: 2016.11.9