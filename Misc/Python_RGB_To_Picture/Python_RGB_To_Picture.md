#Python RGB to picture

-------------------------

###0x00 简介  
在一次 CTF 的 MISC 中，遇到的一道题。


###0x01 正文  
题目给的是一个数据包.pacpng 的文件，通过 wiresharke 导出 HTTP对象 后得到一个压缩文件：   

<img src='./Images/Image1.png' width='500'>

解压文件得到 txt 文件，打开一看，应该是 RGB 了：
<img src='./Images/Image2.png' width='500'>

利用 python image 模块解一下：  

	from PIL import Image


Result:  
<img src='./Images/Image3.png' width='500'>

</br>


-----------------------
References:  

</br>
Author: xx  
Time: 2016.11.9