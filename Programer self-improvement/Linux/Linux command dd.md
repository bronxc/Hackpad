#Linux DD命令  
--------------------------------  

###0x00 前言  
dd命令的解释。

dd：用指定大小的块拷贝一个文件，并在拷贝的同时进行指定的转换。

PS：指定数字的地方若以下列字符结尾则乘以相应的数字：b=512；c=1；k=1024；w=2



###0x01 正文
dd 参数：

1. if=文件名：输入文件名，缺省为标准输入。即指定源文件。< if=input file >

2. of=文件名：输出文件名，缺省为标准输出。即指定目的文件。< of=output file >

3. ibs=bytes：一次读入bytes个字节，即指定一个块大小为bytes个字节。

    obs=bytes：一次输出bytes个字节，即指定一个块大小为bytes个字节。

    bs=bytes：同时设置读入/输出的块大小为bytes个字节。

4. cbs=bytes：一次转换bytes个字节，即指定转换缓冲区大小。

5. skip=blocks：从输入文件开头跳过blocks个块后再开始复制。

6. seek=blocks：从输出文件开头跳过blocks个块后再开始复制。

	注意：通常只用当输出文件是磁盘或磁带时才有效，即备份到磁盘或磁带时才有效。

7. count=blocks：仅拷贝blocks个块，块大小等于ibs指定的字节数。

8. conv=[conversion]：用指定的参数转换文件。

    ascii：转换ebcdic为ascii

     ebcdic：转换ascii为ebcdic

    ibm：转换ascii为alternate ebcdic

    block：把每一行转换为长度为cbs，不足部分用空格填充

    unblock：使每一行的长度都为cbs，不足部分用空格填充

    lcase：把大写字符转换为小写字符

    ucase：把小写字符转换为大写字符

    swab：交换输入的每对字节

     noerror：出错时不停止

     notrunc：不截短输出文件

    sync：将每个输入块填充到ibs个字节，不足部分用空（NUL）字符补齐。


###0x02 Linux 下的两个特殊的文件  
`/dev/null`  ： 在类Unix系统中，/dev/null，或称空设备，是一个特殊的设备文件，它丢弃一切写入其中的数据（但报告写入操作成功），读取它则会立即得到一个EOF。
在程序员行话，尤其是Unix行话中，/dev/null 被称为位桶(bit bucket)或者黑洞(black hole)。空设备通常被用于丢弃不需要的输出流，或作为用于输入流的空文件。这些操作通常由重定向完成。


`/dev/zero`  ： 在类Unix 操作系统中, /dev/zero 是一个特殊的文件，当你读它的时候，它会提供无限的空字符(NULL, ASCII NUL, 0x00)。
其中的一个典型用法是用它提供的字符流来覆盖信息，另一个常见用法是产生一个特定大小的空白文件。BSD就是通过mmap把/dev/zero映射到虚地址空间实现共享内存的。可以使用mmap将/dev/zero映射到一个虚拟的内存空间，这个操作的效果等同于使用一段匿名的内存（没有和任何文件相关）。



</br>

-------------------------------  
References:  
cnblogs.VinoZhu:  <http://www.cnblogs.com/vinozly/p/5687413.html>    
360doc.钿畑的博客:  <http://www.360doc.com/content/15/0906/17/8737500_497292503.shtml>  
CSDN.pi9nc的专栏:  <http://blog.csdn.net/pi9nc/article/details/18257593>  

</br>
Author: xx  
Time: 2017.1.9  