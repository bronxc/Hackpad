##Nmap


>nmap < target ip address >

nmap 192.168.0.1

>nmap -vv < target ip >

返回出详细描述

>nmap -p(range) < target ip >

nmap -p1-50 192.168.0.1  
指定端口范围扫描

>nmap -p(port1,port2,.....) < target ip >

nmap -p80,8080,8081 192.168.0.1  
指定端口扫描

>nmap -sP < target ip >

设置扫描方式为ping扫描

>nmap -traceroute < target ip >

路由跟踪

>nmap -sP < target ip > < /CIDR >

nmap -sP 192.168.0.1/24  
扫描一个网段下的ip

>nmap -O < target ip >

操作系统检测

>nmap -A < target ip >

万能开关：次选项设置包含了1-10000的端口ping扫描，操作系统扫描，脚本扫描，路由跟踪，服务探测

>