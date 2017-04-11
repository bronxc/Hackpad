#Windows Registry  

----------------------------------  

###0x00 简介  
注册表（Registry）是Microsoft Windows中的一个重要的数据库，用于存储系统和应用程序的设置信息。早在Windows 3.0推出OLE技术的时候，注册表就已经出现。随后推出的Windows NT是第一个从系统级别广泛使用注册表的操作系统。但是，从Windows 95开始，注册表才真正成为Windows用户经常接触的内容，并在其后的操作系统中继续沿用至今。

Microsoft Windows 98、Windows CE、Windows NT 和 Windows 2000 中使用的中央分层数据库，用于存储为一个或多个用户、应用程序和硬件设备配置系统所必需的信息。 

注册表包含 Windows 在运行期间不断引用的信息，例如，每个用户的配置文件、计算机上安装的应用程序以及每个应用程序可以创建的文档类型、文件夹和应用程序图标的属性表设置、系统上存在哪些硬件以及正在使用哪些端口。 

注册表取代了 Windows 3.x 和 MS-DOS 配置文件（例如，Autoexec.bat 和 Config.sys）中使用的绝大多数基于文本的 .ini 文件。虽然多个 Windows 操作系统都有注册表，但这些操作系统的注册表存在一些差异。


###0x01 目录  
1. 数据结构
2. 注册表的分支结构
3. 注册表的存储方式

###0x02 数据结构  
注册表由键（key，或称“项”）、子键（subkey，子项）和值项（value）构成。一个键就是树状数据结构中的一个节点，而子键就是这个节点的子节点，子键也是键。一个值项则是一个键的一条属性，由名称（name）、数据类型（datatype）以及数据（data）组成。一个键可以有一个或多个值，每个值的名称各不相同，如果一个值的名称为空，则该值为该键的默认值。

注册表的数据类型主要有以下五种：

|显示类型（在编辑器中）|	数据类型|	说明|
|------|---------|--------|
|REG\_SZ|	字符串|	文本字串|
|REG\_BINARY|	二进制数|	不定长度的二进制值，以十六进制显示|
|REG\_DWORD|	双字|	一个 32 位的二进制值，显示为 8 位的十六进制值|
|REG\_MULTI\_SZ|	多字符串|	含有多个文本值的字符串，此名来源于字符串间用 nul 分隔、结尾两个 nul|
|REG\_EXPAND\_SZ|	可扩充字符串|	含有环境变量的字符串|  

此外，注册表还有其他的数据类型，但是均不常用：  

* REG\_DWORD\_BIG\_ENDIAN - DWORD 的大头版本，下面同理  
* REG\_DWORD\_LITTLE\_ENDIAN  
* REG\_FULL\_RESOURCE\_DESCRIPTOR  
* REG\_QWORD - DWORD 的四字（64 位）版本  
* REG\_FILE\_NAME  


###0x03 注册表的分支结构  
注册表有五个一级分支，下面是这五个分支的名称及作用：  

|名称|	作用|
|----|----|
|HKEY\_CLASSES\_ROOT|	存储Windows可识别的文件类型的详细列表，以及相关联的程序。存储在这里的信息可确保使用 Windows 资源管理器打开文件时能打开正确的程序。|
|HKEY\_CURRENT\_USER|	包含当前登录的用户的配置信息的根目录。该用户的文件夹、屏幕颜色和“控制面板”设置都存储在这里。这些信息与用户的配置文件相关联。|
|HKEY\_LOCAL\_MACHINE|	包括安装在计算机上的硬件和软件的信息。|
|HKEY\_USERS|	包含使用计算机的用户的信息。|
|HKEY\_CURRENT\_CONFIG|	包含有关本地计算机在系统启动时使用的硬件配置文件的信息。|


###0x04 注册表的存储方式  
Windows NT家族的配置单元文件：  

|名称|	注册表分支|	作用|
|------|-------|-----|
|SYSTEM|	HKEY\_LOCAL\_MACHINE\SYSTEM|	存储计算机硬件和系统的信息|
|NTUSER.DAT|	HKEY\_CURRENT\_USER|存储用户参数选择的信息（此文件放置于用户个人目录，和其他注册表文件是分开的）|
|SAM|	HKEY\_LOCAL\_MACHINE\SAM|	用户及密码的数据库|
|SECURITY|	HKEY\_LOCAL\_MACHINE\SECURITY|安全性设置信息|
|SOFTWARE|	HKEY\_LOCAL\_MACHINE\SOFTWARE|安装的软件信息|
|DEFAULT|	HKEY\_USERS\DEFAULT|	缺省启动用户的信息|
|USERDIFF|	HKEY\_USERS|	管理员对用户强行进行的设置|  

 



</br>

-----------------------------------
References:  
MSDN:  <https://msdn.microsoft.com/en-us/library/ms724836(v=vs.85).aspx>   
support.microsoft:  <https://support.microsoft.com/zh-cn/kb/256986>  
维基百科:  <https://zh.wikipedia.org/zh-hans/注册表>  

</br>
Author: xx  
Time: 2016.11.23