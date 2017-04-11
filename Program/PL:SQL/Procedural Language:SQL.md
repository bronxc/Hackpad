# Procedural Language/SQL  

--------------------------------  

### 0x00 前言  



### 0x01 目录  

##### 1.PL/SQL 程序块结构   
1.1 PL/SQL 程序块定义
##### 2.变量与常量  
2.1 声明变量和常量  
2.2 运算符   
##### 3.数据类型  
3.1 标量数据类型  
3.2 大对象数据类型  
3.3 常用的内置函数  
##### 4.SQL语句在 PL/SQL 的使用  
4.1 select 的使用  
4.2 select, update, delete 的使用和其他
##### 5.流程控制语句  
5.1 条件判断 if  
5.2 条件判断 case  
5.3 循环语句 end loop  
5.4 循环语句 while  
5.5 循环语句 for  
5.6 Goto 语句  
5.7 嵌套  
##### 6.游标  
6.1 显示游标  
6.2 隐式游标  
6.3 动态游标  
6.4 动态SQL  
##### 7.异常处理  
7.1 异常的捕获与处理  
7.2 预定义异常    
7.3 自定义异常  
##### 8.存储过程  
8.1 创建与调用存储过程  
8.2 带参数的存储过程  
##### 9.函数  
9.1 创建与调用函数
##### 10.包  
10.1 创建包与调用  
10.2 重载  
##### 11.触发器  
11.1 触发器的使用  
11.2 :new 和 :old  
11.3 instend of 触发器  
11.4 触发器的点火次序  
11.5 变化表和限制表  
11.6 创建用户的错误消息   


### 0x02 正文
##### 1.PL/SQL 程序块结构   
__1.1 PL/SQL 程序块定义__  
PL/SQL结构化的语言，其程序结构的基本单位是“块”(Block)。PL/SQL块有三个部分：声明部分、执行部分、异常处理部分

	[DECLARE]
	    declaration statements
	BEGIN
	    executable statements
	[EXCEPTION]
	    exception statements
	END
	
PL/SQL块中的每一条语句都必须以分号结束，SQL语句可以多行，但分号表示语句的结束。一行中可以有多条SQL语句，他们之间以分号分隔。每一个PL/SQL块由BEGIN或DECLARE开始，以END结束。

PL/SQL程序块可以是一个命名的程序块也可以是一个匿名程序块，匿名程序块可以用在服务器端也可以用在客户端。  
执行部分包含了所有的语句和表达式，执行部分以关键字BEGIN开始，将以关键字END结束。分号分隔每一条语句，使用赋值操作符:=或SELECT INTO给每个变量赋值，执行部分的错误将在异常处理部分解决，在执行部分中可以使用另一个PL/SQL程序块，这种程序块被称为嵌套块。


##### 2.变量与常量  
__2.1 声明变量和常量__   
声明变量  
	
	Variable_name datatype [(WIDTH)] [:= DEFAULT expression]
给变量赋值  
通常给变量赋值有两种方式：

1. 是直接给变量赋值；
2. 是通过SQL SELECT INTO给变量赋值。

声明常量  
常量与变量相似，但常量的值在程序内部不能改变，常量的值在定义时赋予，声明方式与变量相似，但必须包括关键字CONSTANT。

Example:  

	DECLARE
		ORDER_NO NUMBER(3);
		CUST_NAME VARCHAR2(20);
		ORDER_DATE DATE;
		EMP_NO INTEGER:=25;
		PI CONSTANT NUMBER:=3.1416;
	BEGIN
			NULL;
	END;

有效字符集：  
所有的大写和小写英文字母；  
数字：0-9  
符号：( ) + - * / < > = ! ; : . ' @ % , " # & _ { } ? [ ]  

__2.2 运算符__   

|运算符| 说明 |
|-----|-----|
|**  | 指数|
|*,/|乘，除|
|+,-,\|\| |加，减，连接|
|=|等于 |
|<>,!=|不等于  |
|>,<| 大于，小于 |
|<=,>= |  小于等于，大于等于 |
|between...and...| 检索两值之间的内容  |
|in | 检索匹配列表中的值   |
|like|  检索匹配字符样式的数据  |
|is null | 检索空数据  |
|not | 取相反的逻辑值 |
|and | 两个值为真则结果为真  |
|or |  只要有一个值为真结果就为真  |


##### 3.数据类型  
__3.1 标量数据类型__  

|名称|类型|说明|
|----|----|----|
|number| 数字型|能存放整数值和实数值，并且可以定义精度和取值范围|
|binary_integer|数字型|可以存储带符号整数，为正数计算优化性能|
|dec|数字型| number的子类型，小数 |
|double precision|数字型| number的子类型，高精度实数 |
|integer|数字型| number的子类型，整数 |
|int| 数字型| number的子类型，整数 |
|numberic|数字型| number的子类型，与number等价 |
|real| 数字型| number的子类型，与number等价 |
|smallint| 数字型| number的子类型，取值范围比integer小 |
|varchar2|字符型| 存放可变长字符串，有最大长度 |
|char|  字符型| 定长字符串 |
|long| 字符型|  变长字符串，最大长度可达32767 |
|date| 日期型|   以数据库相同的格式存放日期值 |
|boolean| 布尔型| true or false |
|rowid|  rowid| 存放数据库的行号  |


__3.2 大对象数据类型__  

1. 使用 `%type` 定义简单变量  
当使用 `%type` 属性定义变量时，它会按照数据库列或者其他变量来确定新变量的类型和长度。  
使用 `%type` 定义简单变量的格式： 

		variable_name [schema.]table_name.column_name%type; --使用表中字段的类型来定义变量  
		variable_name old_variable%type;  --使用已有变量的类型来定义新变量
		

2. 使用 `%rowtype` 定义记录变量  
`%rowtype` 属性可用于定义记录变量的数据类型，使得该记录变量的结构和已有的某张表结构完全一致，这样记录变量就可以存储从该表中检索出的一行记录。但有时需要的记录变量的结构和已有的任何一张表结构都不相同，这种情况只能使用自定义的记录类型定义记录变量。  
使用 `%rowtype` 定义记录变量的格式：  

		record_variable [schema.]table_name%rowtype;  --使用表结构定义记录变量
		record_variable [schema.]view_name%rowtype;   --使用视图结构定义记录变量
		record_variable old_record_variable%rowtype;  --使用已有的记录变量定义新纪录变量



##### 4.SQL语句在 PL/SQL 的使用  
__4.1 select 的使用__  
在 PL/SQL 中使用select 语句，需要与 into 子句一起使用，这样做的目的是将查询的结构存储到一个变量中。  
select into 语句的语法：  

	select [All | Distinct] select_list
	into variable_list | record
	from [schema.]table_name | [schema.]view_name | (sub-query)
	[where search_condition]


__4.2 insert, update, delete 的使用和其他__  

1. 在 PL\SQL 程序块中可以直接使用 inset， update， delete 这些 DML语句。
2. 在 PL\SQL 程序块中可以直接使用 DCL 语句（commit， rollback, saveback）。
3. 而在 PL\SQl 程序块不能直接使用 DDL 语句，需要使用动态SQL执行。



##### 5.流程控制语句  
__5.1 条件判断 if__   
IF条件判断逻辑结构： 

	IF condition THEN
		statement;
	END IF;
	
	IF condition1 THEN
		statements_1;
	ELSIF condition2 THEN
		statements_2;
	ELSE
		statements_3;
	END IF;


__5.2 条件判断 case__  

	CASE 表达式（或变量）
	     WHEN 表达式1 THEN 语句1;
	     WHEN 表达式2 THEN 语句2;
	     WHEN 表达式3 THEN 语句3;
	     WHEN 表达式4 THEN 语句4;
	     ELSE 语句5;
	END CASE;
	
Example1：  
	declare 	  v1 integer := 2;	begin	  case v1	    when 1 then	      dbms_output.put_line('111');      when 2 then        dbms_output.put_line('222');        --print "222"      else        dbms_output.put_line('333');      end case;	end;
	
Example2:  

	declare 	  v1 integer := 0;	begin	  case	    when v1<1 then	      dbms_output.put_line('<1');
	      --print "<1"      when v1>2 then        dbms_output.put_line('>2');      else        dbms_output.put_line('1 or 2');      end case;
    end;
	


__5.3 循环语句 end loop__  
LOOP循环通过判断 EXIT 的语句，来确定是否循环。

	LOOP
	   [statement1]
	   [statement2]
	   …………
	   EXIT WHEN (condition);
	END LOOP;

__5.4 循环语句 while__  
WHILE … LOOP有一个条件与循环相联系，如果条件为TRUE，则执行循环体内的语句，如果结果为FALSE，则结束循环。

	WHILE (condition) LOOP
	   [statement1]
	   [statement2]
	   …………
	END LOOP;

__5.5 循环语句 for__  
FOR … LOOP循环控制语句
	
	FOR counter IN [REVERSE] start_range .. end_range LOOP
	  statements;
	END LOOP;
	
counter是一个隐式声明的变量，初始值是start\_range，第二个值是start\_range+1(步长)，直到end\_range。如果使用了REVERSE关键字，那么范围将是一个降序。
	
__5.6 Goto 语句__  

__5.7 嵌套__  
程序块的内部可以有另一个程序块这种情况称为嵌套。嵌套要注意的是变量，定义在最外部程序块中的变量可以在所有子块中使用，如果在子块中定义了与外部程序块变量相同的变量名，在执行子块时将使用子块中定义的变量。子块中定义的变量不能被父块引用（局部变量）。同样GOTO语句不能由父块跳转到子块中，反之则是合法的。



	
##### 6.游标  
一个游标就是一个指向保存有多行SQL查询结果集的工作区的句柄。Oracle打开一个工作区来保存多行查询的结果集。游标就是给这个工作区命的名称，并能用于处理由多行查询而返回的记录行。  

当服务器上执行了一个查询后，查询返回的记录集存放在上下文相关区，通过游标上的操作可以把这些记录检索到客户端的应用程序。
游标分显式游标和隐式游标 

__6.1 显示游标__  

1. 声明游标  
声明游标的语句格式如下：

		Cursor cursor_name IS SELECT statement
声明游标完成了下面两个目的：  
（1）给游标命名；  
（2）将一个查询与游标关联起来。  

2. 打开和关闭游标  
打开游标的语句格式如下：  
		
		OPEN cursor_name;
打开游标将激活查询并识别活动集，可是在执行游标取回命令之前，并没有真正取回记录。OPEN命令初始化了游标指针，但没有使其指向活动集的第一条记录。   

	CLOSE语句关闭以前打开的游标，使得活动集不确定。
CLOSE语句的格式：
    
    	CLOSE cursor_name;

3. 遍历游标   
游标被打开后，直到关闭之前，取回到活动集的所有数据都是静态的。换句话说，游标忽略所有在游标打开之后，对数据执行SQL的 DML命令(INSERT、UPDATE、DELETE)，因此只有在需要时才打开它，要刷新活动集，只需关闭并重新打开游标即可。不要打开已经打开的游标，否则回产生异常。  

	游标的属性：  
	
	|属性|含意|
	|----|---|
	|%FOUND|布尔型属性，当最近一次该记录成功返回，则值为TRUE|
	|%NOTFOUND|布尔型属性，它的值与%FOUND相反|
	|%ISOPEN|布尔型属性，当光标是打开时返回TRUE|
	|%ROWCOUNT|数字型属性，返回已从光标中读取的记录数|

	FETCH命令以每次一条记录的方式取回活动集中的记录。FETCH命令每执行一次，游标前进到活动集的下一条记录。
FETCH命令的语句格式如下：

		FETCH cursor_name INTO record_list;
执行FETCH命令后，活动集中的结果被取回到PL/SQL变量中，以便在PL/SQL块中使用。每取回一条记录，游标的指针就移向活动集的下一条记录。  

	使用 while 循环遍历游标(注意：在进入 while 前先 fetch 一下，这样%found 才是 true)：  

		declare 		  cursor c1 is select * from student;		  v_stu student%rowtype;		begin		  open c1;  			  fetch c1 into v_stu;		  while c1%found loop		    dbms_output.put_line(v_stu.sno || ' ' || v_stu.sname);		    fetch c1 into v_stu;		  end loop;			  close c1;		end;
		
	这里单独说一下使用 for 循环遍历游标：  
	
		declare 		  cursor c1 is select * from student;		begin		  for i in c1 loop		    dbms_output.put_line(i.sno || ' ' || i.sname);		  end loop;		end;
		
	在 for 循环中遍历游标：不需要打开游标，不需要 fetch， 也不需要关闭游标。  	
	FOR LOOP游标的索引不需要声明，它有PL/SQL隐式的定义为cursor%rowtype类型。当需要在一个游标中无条件的处理所有行，用FOR  LOOP语句是很好的。
		
		
4. 带参数的游标  
可以在游标名称后面 ，用括号括起参数的名称和类型来定义游标的参数。这些参数叫形参。实参由OPEN语句传递到形参中。

		cursor c1(v_sno varchar) is select * from student where sno=v_sno;
		
	Example：  

		declare 		  cursor c1(v_sno varchar) is select * from student where sno=v_sno;	    v_stu student%rowtype;		begin		  open c1('001');		  fetch c1 into v_stu;		  dbms_output.put_line(v_stu.sno || ' ' || v_stu.sname);		  close c1;		end;
	

5. SELECT FOR UPDATE游标  
可以用SELECT FOR UPDATE游标来更新由游标检索到的那些记录行。这在仅仅需要修改检索到的那些记录行，而不需要取出这些行值的情况下是非常有用的。  

	SELECT FOR UPDATE游标的工作机制：  
	
	* 首先为游标检索到的行家锁。
	* 对游标标识的每一行，游标会更改该行的特定列。（无需再次扫描表格—与UPDATE语句对比）

	SELECT FOR UPDATE游标的优势：  
	
	* 在打开游标并标识要更新的结果集中的行之后就立即加锁。
	* 不必为更新操作而对表格进行第二次取值。

	注： 在游标的循环外部必须进行COMMIT操作。否则不会释放锁。  
	
	Example：  

		declare		  cursor csr_1 is		    select * from student FOR UPDATE OF sex;		  v_sex VARCHAR2(20);		begin		  for i in csr_1 loop		    v_sex := LOWER(i.sex);		    update student set sex = v_sex where current of csr_1;		  end loop;		  commit;		end;


__6.2 隐式游标__  
隐式游标又叫作SQL游标。  
在作DML语句时，会自动的打开一个SQL游标指向相应的工作区。
隐式游标在DML语句操作完毕后自动关闭，所以不需要，也不能用OPEN，FETCH，CLOSE语句操作隐式游标。  

Example:  

	declare	begin	  update student set age = 100 where sno='001';	  if sql%found then	    dbms_output.put_line('update row');	  else	        dbms_output.put_line('no update');	  end if;	  commit;	end;
	
使用隐式游标的 for 循环遍历：  

	declare	begin	  for i in (select * from student) loop	    dbms_output.put_line(i.sno || ' ' || i.sname);	  end loop;	end;


__6.3 动态游标__  
使用动态游标变量可以在存储过程之间传递结果集。在运行时，一个游标变量能与多个查询相关联。  

游标变量的定义有两步：定义一个REF CURSOR类型的指针和该类型的变量名。  

	Type rc is ref cursor;
	V_rc rc;
其中REF关键字表示定义了一个CURSOR类型的指针。  
REF TYPE 表示定义了指向TYPE类型的指针。  

强 ref cursor 类型与弱 ref cursor 类型：   
没有指明游标返回类型的游标变量称为弱REF CURSOR类型。它能指向任何一个具有任意多列的SELECT查询。  
也可以为游标指明返回类型，这样的游标变量称为强REF CURSOR。   
	
	Type rc is ref cursor return sc%rowtype   
	
使用 动态游标：  

	declare	  type rc is ref cursor;	  v_rc rc;	  v_stu student%rowtype;	begin	  open v_rc for select * from student;	  	    loop	      fetch v_rc into v_stu;	      dbms_output.put_line(v_stu.sno || ' ' || v_stu.sname);	    exit when(v_rc%notfound);	    end loop;	  	  close v_rc;	end;


__6.4 动态SQL__  
（动态SQL 不属于游标这一类的内容，不过还是暂且放这吧）  

静态SQL与动态SQL　　 

1. 静态SQL  
    Oracle编译PL/SQL程序块为前期联编（early binding），即SQL语句在程序编译期间就已经确定  
2. 动态SQL  
    Oracle编译PL/SQL程序块为后期联编（late binding），即SQL语句只有在运行阶段才能建立  
    
为什么使用动态SQL：  
当查询条件为用户输入时，那么Oracle的SQL引擎就无法在编译期对该程序语句进行确定，只能在用户输入一定的查询条件后才能提交给SQL引擎进行处理。   

 Oracle中提供了 `Execute immediate` 语句来执行动态SQL，语法如下：    

	Excute immediate 动态SQL语句 
	into 输出参数列表
	using 绑定参数列表 

Example(创建该表并输入相应的数据)：  

	declare	  v_id int := 2;	begin	  execute immediate	  'create table t(id int, value varchar(20))';	  execute immediate	  'insert into t values(1, ''a'')';  --''a''，这里 ' 是转义符号，在这里相当于是 'a'	  execute immediate	  'insert into t values(:1, ''b'')' --:1 是占位符，替换参数 v_id	  using v_id;                       --使用参数 v_id	  commit;	end;


##### 7.异常处理  
__7.1 异常的捕获与处理__   

1. PL/SQL的异常
异常处理块中包含了与异常相关的错误发生以及当错误发生时要进行执行和处理的代码。
异常部分的语法一般如下：

		BEGIN
		   EXCEPTION
		     WHEN excep_name1 THEN
		     ……
		     WHEN excep_name2 THEN
		     ……
		     WHEN OTHERS THEN
		     ……
		END; 
	
2. 预定义异常
预定义异常是由运行系统产生的。例如，出现被0除时，PL/SQL就会产生一个预定义的ZERO_DIVIDE异常。
3. 自定义异常
异常不一定必须是Oracle返回的系统错误，用户可以在自己的应用程序中创建可触发及可处理的自定义异常，调用异常处理需要使用Raise语句。
异常情态的传播指的是当在程序块的声明、执行、异常部分分别出现异常情态时，或在本块中没有相应的异常处理器时会将这个异常情态传播到哪里，会去激发那个块中的处理器。

__7.2 预定义异常__    
__7.3 自定义异常__  


##### 8.存储过程  
前面编写执行的PL/SQL程序，共同的特点是没有名称，只能存储为文件，然后通过执行文件的方式执行，因此称为无名块。与此对应的是在PL/SQL中也引入了高级程序设计的一些概念，其中最重要的就是过程。   

过程就是高级程序设计语言中的模块的概念，将一些内部联系的命令组成一个个过程，通过参数在过程之间传递数据是模块化设计思想的重要内容。  

__8.1 创建与调用存储过程__   
过程的语法结构:  

	CREATE OR REPLACE PROCEDURE 过程名	IS	声明语句段; 	BEGIN 	执行语句段; 	EXCEPTION 	异常处理语句段; 	END; 
注： 过程是有名称的程序块，is关键词代替了无名块的Declare。因此在过程中不能使用Declare子句  

创建存储过程：  
	
	create or replace procedure p2	is	  number int := 1;	begin	  dbms_output.put_line(number);	end p2;
创建过程并不会直接输出结果，只是和创建其他数据库对象一样，是一个数据定义命令。 	
	
调用存储过程：  

1. 在命令窗口中调用：  
	
		set serveroutput on;  		-- 打开命令行输出  
		execute p2;	
	或
	
		call p2();

2. 在测试窗口中调用：  

		declare		begin		  p2;		end;

 
__8.2 带参数的存储过程__   
在PL/SQL过程中，可以有3种类型的参数。 

* in参数：读入参数，主程序向过程传递参数值。 
* out参数：读出参数，过程向主程序传递参数值。 
* in out 参数：双向参数，过程与主程序双向交流数据。  

Example:  

	create or replace procedure p1(a in int, b in int, sum out int)	is	begin	  sum := a + b;	end p1;
调用过程：  

	declare	  v_sum int := 0;	begin	  p1(3, 5, v_sum);	  dbms_output.put_line(v_sum);	end;

带默认参数值的存储过程：  

	create or replace procedure p3(num in int := 10, v_value in varchar := '*')	is	begin	  for i in 1..num loop	    dbms_output.put_line(v_value);	  end loop;	end p3;
调用过程：  

	declare	begin	  p3();                --使用默认值 num := 10, v_value := '*' ，也可以不带括号	  p3(2, '=');          --不使用默认值	  p3(2);               --只使用默认值 v_value := '*'	  p3(v_value => '=');  --只使用默认值 num := 10 	end;


##### 9.函数  
函数的定义与过程的定义主要的不同就在于签名。函数的签名比过程的签名多了一个Return子句，该子句指定了函数的返回值的类型。  
定义函数时必须指定其返回类型。函数中的任何一个出口都必须要有 return 语句。  

__9.1 创建与调用函数__  

	create or replace function f1	(length in number,	 v_value in varchar)	return varchar	is	  line varchar(100);	begin	  for i in 1..length loop	    line := line || v_value;	  end loop;	  return line;	exception	  when others then	    return null;	end f1;
调用函数： 

	declare	begin	  dbms_output.put_line(f1(10, '*'));	end;
	


##### 10.包  
包是一个可以将相关对象存储在一起的PL/SQL结构。包包含了两个分离的部件——规范和主体。每个部件都单独被存储在数据字典中。除了可以将相关对象作为一组存在一起以外，包也是十分有用的，因为它们在依赖性方面的限制是比较小的。它们也有许多性能上的优点。  

从本质上说，包是一个带名声明部分。在块的声明部分可以出现的任何内容都可以在包中出现，其中包括过程、函数、游标和变量。将这些对象放入一个包中的一个好处就是可以从其他的PL/SQL块中引用它们，这样包也提供了用于PL/SQL的全局变量。  

__10.1 创建包与调用__   

* 包规范  
包规范(也就是“包头”，package header)包含了有关包的内容的信息（包括定义变量，常量，游标，函数，过程等）。但是，它不包含任何过程的代码。  

	创建包头的语句格式如下：  
	
		CREATE OR REPLACE PACKAGE＜包名>
		AS
		变量、常量及数据类型定义；
		游标定义；
		函数、过程定义和参数列表及返回类型；
		END＜包名＞；

* 包体  
包主体(package body)和包头存储在不同的数据字典中。如果没有对包头进行成功地编译，就不可能编译包主体成功。主体中包含了在包头中声明的子程序和函数相应的实现代码。

	创建包主体部分的语句格式如下：
	
		CREATE OR REPLACE PACKAGE BODY＜包名＞
		AS
		游标、函数、过程的具体定义；
		[BEGIN]
		  --初始化数据
		END＜包名＞；

	包主体是可选的。如果包头不包含任何过程或函数(仅包含变量声明、游标、类型等)，那么包主体可以没有。这个技术对于声明全局变量是很有用的，因为包中的所有对象在包的外面是可见的（全局的）。

	过程或函数的规范在包头和包主体中必须是相同的。这个规范包括子程序的名字、参数的名字以及参数的模式（传入，传出）。
	
	在包头中声明的所有对象在包的外面都是位于其作用域中并且都是可见的，只要指定该包的名字就可以访问该对象了。
	
	而未在包头中声明，却在包体中声明使用了的变量，过程或函数，在包的外面是不可见的，它是仅在包内可以见的（类似于私有变量）。

* 调用   
包头的创建：  

		create or replace package pk1		as		  num number := 0;		  procedure outNum;		end pk1;
包体的创建：  

		create or replace package body pk1		as		  procedure outNum		    is		    begin		      num := num + 1;		      dbms_output.put_line(num);		    end outNum;		end pk1;
在测试窗口中调用：  

		declare		begin		  pk1.outNum;		end;
		
	这里写一个包含私有函数的包：  
包头的创建：  
 
		create or replace package pk3
		as
		  function calc(num1 in number, num2 in number) return number;
		end pk3;

	包体的创建：  

		create or replace package body pk3
		as
		  --declare function run, only called by procedure or funciton in pk3
		  function run(num1 in number, num2 in number) return number;
  
		  --achieve funciton calc
		  function calc(num1 in number, num2 in number) return number
		  as
		    result number := 0;
		  begin
		    dbms_output.put_line('call funciton calc');
		    result := run(num1, num2);
		    return result;
		  end calc;
  
		  --achieve private function run
		  function run(num1 in number, num2 in number) return number
		  as
		    result number := 0;
		  begin
		    result := num1 + num2;
		    dbms_output.put_line('call function run');
		    return result;
		  end run;
  
		begin
		  dbms_output.put_line('body first called');
		end pk3;



__10.2 重载__   
在包的内部，过程和函数是可以被“重载”(overload)的。这就意味着对于同一个名字会有多个过程或函数，但是它们的参数是不同的。这是个非常有用的特性，因为它允许将同一个操作引用于不同类型的对象上。例如，假设我们想要添加一个学生的选课信息，那么我们可以通过指定学生学号或指定学生的姓名来实现。  

当要对不同类型的参数执行相同的操作的时候，重载就是一个非常有用的技术。但是重载也要受一些限制。  

1. 如果两个子程序的参数仅仅在名字或模式上是不同的。下面两个过程就不能被重载：  
`procedure p1(v1 in number);`  
`procedure p1(v2 out number);`  
2. 不能仅仅根据返回类型的不同来重载两个函数。  
3. 重载函数或过程的参数必须是属不同类型族的—不能对来自同一个类型族的参数进行重载。例如，CHAR和VARCHAR属于同一个类型族．所以不能重载下面的过程：  
`procedure p1(v1 char);`  
`procedure p1(v2 varchar);`

Example:  
包头的创建：  

	create or replace package pk2
	as
	procedure print(para in number);
	procedure print(para1 in number, para2 in number);
	end pk2;

包体的创建：  

	create or replace package body pk2
	as
	  --achieve procedure print with one parameter
	  procedure print(para in number)
	  as
	    begin
	      dbms_output.put_line('one parameter, the value is ' || para);
	    end print;
  
	  --achieve procedure print with tow parameter
	  procedure print(para1 in number, para2 in number)
	  as
	    begin
	      dbms_output.put_line('tow parameter, the one value is ' || para1 || ', the tow value is ' || para2);
	    end print;
	    
	end pk2;


##### 11.触发器  
触发器类似于过程或函数，因为它们都是拥有声明、执行和异常处理过程的带名PL/SQL块。与包类似，触发器必须存储在数据库中并且不能被块进行本地化声明。但是，对于过程而言．可以从另一个块中通过过程调用显式地执行一个过程。同时在调用时可以传递参数。对于触发器而言，当触发事件发生时就会显式地执行该触发器。并且触发器不接受参数。执行触发器的操作就是“点火”  (firing)触发器。触发器事件是在数据库表上执行的DML(INSERT、UPDATE或DELETE)操作。

可以使用触发器做许多事情，包括

1. 维护不可能在表创建时刻通过声明性约束进行的复杂的完整性约束限制。
2. 通过记录所进行的修改以及谁进行了修改来审计表中的信息。
3. 当表被修改的时候，自动给其他需要执行操作的程序发信号。

__11.1 触发器的使用__   
触发器不可缺少的部件是触发器名、触发事件和触发器主体。  
 1．触发器名  
    触发器名的名字空间不同于其他子程序的名字空间。“名字空间” 是可以用作对象名字的合法标识符的集合。过程、包和表的名字空间相同。这就是说，为过程和包赋予相同的名字将是非法的。
    但是，触发器却使用的是单独的名字空间。这意味着触发器可以使用和表或过程相同的名字。但是，在一个数据模式中，一个名字仅能用于一个触发器。  
2. 触发器事件   
触发器事件决定了触发器的类型。触发器可以按照INSERT、UPDATE或DELETE操作进行定义，并且它们也可以点火进行行操作或语句操作。触发器也可以对多种类型的触发语句点火。  
3. 触发器的语法结构

	CREATE OR REPLACE TRIGGER trigger_name
	{before|after|instead of} 
	{Insert [or delete] [or update [of col1,…coln]}
    on {table_name|view_name}
	[for each row[when(condition)]]
	[DECLARE]
	BEGIN 
	    执行语句段; 
	    EXCEPTION 
	        异常处理语句段; 
	END; 
	
Example:  

	CREATE OR REPLACE
	TRIGGER TR_INSERT_UPDATE_GRADE_SC AFTER INSERT OR UPDATE OF grade ON SC 
	FOR EACH ROW 
	BEGIN
	  if inserting then  --插入时触发
	    dbms_output.put_line('Insert');
	  end if;
	  if updating then  --修改Grade时触发
	     dbms_output.put_line('Update');   
	  end if;
	END;

注意事项：  

1. 一个 FOR EACH ROW 执行指定操作的触发器为操作修改的每一行都调用一次（行级触发器）。若不带该参数则表示该触发器为语句级触发器，语句级触发器只在插入，修改或删除时执行一次，无论插入，修改，删除影响的是单行还是多行。
2. SELECT 并不更改任何行，因此不能创建 SELECT 触发器。
3. 触发器和某一指定的表格有关，当该表格被删除时，任何与该表有关的触发器同样会被删除。
4. 在一个表上的每一个动作只能有一个触发器与之关联。


__11.2 :new 和 :old__  
 触发语句所处理的每一行都点火一次行级触发器。在触发器的内部，可以访问当前正在被处理的行。这是通过“伪记录”— :old和:new实现的。:old和:new不是真实的记录。尽管从语法上讲，它们的处理方式和记录是一样的，但实际上它们不是，所以它们就被称为伪记录。  
它们的类型是：  
`Triggering_table%rowtype`

INSERT语句没有对:old进行定义，DELETE语句没有对:new进行定义。如果在INSERT中使用了:old或者在DELETE中使用:new，PL/SQL编译器将不会产生错误。但是它们的取值都将是NULL。

注意：   
尽管:new和:old在语法上被作为R0WTYPE的记录进行处理，但是实际上它们并不是记录。结果，许多通常对记录是有效的操作对于:new和:old是无效的。


__11.3 instend of 触发器__  
PL／SQL 提供了另外一种触发器。Instead-of触发器仅可以定义在视图上，并且它们可以替代点火它们的DML语句进行点火。Instead-of触发器必须是行级的。Instead-of触发器是必要的，因为定义触发器的视图可能基于联结(join)并且并非所有的联结都是可更新的。该触发器便可以按照所需的方式执行更新。  

Example:    
定义下面的视图：  
	
	create or replace view stu_avg as 
	select sno,avg(grade) stu_avg from sc group by sno;
若执行下面语句：  
`delete from stu_avg where sno='001';`  

则报错： ORA-01732: 此视图的数据操纵操作非法。   

创建触发器：  

	create or replace trigger stu_avg_delete
	    instead of delete on stu_avg
	    for each row
	    begin
		    delete from sc where sno=:old.sno;
	    end;
再执行删除语句，则删除成功。


__11.4 触发器的点火次序__   
当DML语句被执行时就会点火触发器。下面给出了执行DML语句的顺序：  

1)执行BEFORE语句级触发器(如果有的话)  

2)对于受语句影响的每一行：  
a. 执行BEFORE行级触发器(如果有的话)  
b. 执行DML语句。  
c. 执行AFTER行级触发器(如果有的话)  

3)执行AFTER语句级触发器(如果有的话)  


__11.5 变化表和限制表__  
触发器主体可以访问的表和列上有一些限制。在定义这些限制以前，必须先要认识变化表和限制表。  

“变化表”是被DML语句正在修改的表。对于触发器而言，它就是定义触发器的表。需要作为DELETE CASCADE参考完整性限制的结果进行更新的表也是变化的。  

“限制表”是可能需要对参考完整性限制执行读操作的表。  
比如，对于SC表上的操作进行触发器定义时，SC为变化表，Student和Course表为限制表。（假设SC表上定义了两个外建）

* 行级触发器主体中的SQL语句不允许进行：  

1. 读取或修改触发语句的任何变化表。这些表也包括触发表自己。  
2. 读取或修改触发表的限制表中的主键、唯一值列或外键列。但是如果需要的话，可以修改其他的列。  

这些限制法则适用于所有的行级触发器。仅当在执行DELETE  CASCADE操作时启动语句触发器时，它们才适用于语句触发器。

如果INSERT语句仅影响一个行，那么该行的BEFORE行触发器将不会将触发表作为变化表进行处理。这是行级触发器可以从触发表中执行读或修改操作的唯一可能的情况。象下面这样的语句：
INSERT INTO T1 SELECT…
会始终将触发表作为变化表处理，甚至尽管子查询仅返回一行。

* 消除变化表限制：   
      
触发表仅仅对于行级触发器是变化的。这就是说，我们不能在行级触发器中查询它，但是可以在语句级触发器中查询它。但是，我们不能简单地将行级触发器转换为语句触发器．因为我们需要在触发器主体中使用:new, :old的取值。解这个问题的方法是创建两个触发器：一个行级触发器，另一个是语句级触发器。在行级触发器中，我们记录 :new, :old的取值，但是不对该表进行查询。在语句级触发器中执行查询并使用行级触发器记录下的数值。



__11.6 创建用户的错误消息__   
可以使用内置函数RAISE\_APPLICATlON\_ERROR创建自己的错误消息，这可能要比已命名的异常情态更具说明性。用户定义消息从块中传递到调用环境中的方式和Oracle错误是一样的。  
RAISE\_APPLICATlON\_ERROR的语法如下：

	RAISE\_APPLICATlON\_ERROR
	  (ErrorNumber,ErrorMessage,[keep_errors])
这里ErrNumber是从-20,000到-20,999之间的参数，ErrorMessage是与此错误相关的正文，而keep\_errors是一个布尔值。ErrorMessage必须是不多于512个字节。布尔值参数keep\_errors是可选曲。如果keep\_errors是TRUE，那么新的错误将被添加到已经引发的错误列表中(如果有的话)。如果它是FALSE(这是缺省的设置)，那么新的错误将替换错误的当前列表。

Example:  

	create or replace trigger tri_student_update
	before update of sdept on student
	for each row
	when (old.sdept=‘CS’) --在when这里的old前没有“:”
	begin
	  raise_application_error(-20000,'不能修改CS系学生的系别！');
	end;



</br>

--------------------------------  
References:  
《Oracle数据库应用与开发》   机械工业出版社  


</br>
Author: xx  
Time: 2016.12.19