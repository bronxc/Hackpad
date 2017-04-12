#Assembly Int 10 Function  
--------------------------------   

###0x00 前言  
对汇编中  int 10 的详细介绍。  

INT 10H 是由 BIOS 对屏幕及显示器所提供的服务程序，使用int 10h服务程序时，必须先指定ah寄存器为以下显示服务编号之一，以指定需要调用的功用。当一切设定好之后再调用 INT 10H。


###0x01 功能  
AH值的设置：  
00H：设置显示器模式  
01H：设置光标形状  
02H：设置光标位置  
03H：读取光标信息  
04H：读取光笔位置  
05H：设置显示页  
06H、07H：初始化或滚屏  
08H：读光标处的字符及其属性  
09H：在光标处按指定属性显示字符  
0AH：在当前光标处显示字符  
0BH：设置调色板、背景色或边框  
0CH：写图形象素  
0DH：读图形象素  
0EH：在Teletype模式下显示字符  
0FH：读取显示器模式  
10H：颜色  
11H：字体  
12H：显示器的配置  
13H：在Teletype模式下显示字符串  
1AH：读取/设置显示组合编码  
1BH： 读取功能/状态信息  
1CH：保存/恢复显示器状态  


###0x02 功能详细说明
__1、功能00H__  
功能描述：设置显示器模式  
入口参数：AH＝00H  
AL＝ 显示器模式，见下表所示   
出口参数：无   
可用的显示模式如下所列：  
00H：40×25 16色 文本  
01H：40×25 16色 文本  
02H：80×25 16色 文本   
03H: 80×25 16色 文本   
04H：320×200 4色  
05H：320×200 4色   
06H：640×200 2色  
07H：80×25 2色 文本  
08H：160×200 16色  
09H：320×200 16色  
0AH：640×200 4色  
0BH：保留  
0CH：保留  
0DH：320×200 16色  
0EH：640×200 16色  
0FH：640×350 2(单色)  
10H：640×350 4色  
10H：640×350 16色   
11H：640×480 2色  
12H：640×480 16色  
13H：640×480 256色  
对于超级VGA显示卡，我们可用AX＝4F02H和下列BX 的值来设置其显示模式。  

BX显示模式属性  
100H：640×400 256色  
101H：640×480 256色  
102H：800×600 16色  
103H：800×600 256色  
104H：1024×768 16色  
105H：1024×768 256色   
106H：1280×1024 16色  
107H：1280×1024 256色  
108H：80×60 文本模式  
109H：132×25 文本模式  
10AH：132×43 文本模式    
10BH：132×50 文本模式  
10CH：132×60 文本模式  

__2、功能01H__  
功能描述：设置 光标形状  
入口参数：AH＝01H  
CH低四位＝光标的起始行  
CL低四位＝光标的终止行  
出口参数：无  

__3、 功能02H__  
功能描述：用文本坐标下设置光标位置  
入口参数：AH＝02H   
BH＝显示页码  
DH＝行(Y坐标)  
DL＝ 列(X坐标)  
出口参数：无  

__4、功能03H__  
功能描述：在文本坐标下，读取光标各种信息  
入口参 数：AH＝03H  
BH＝显示页码  
出口参数：CH＝光标的起始行  
CL＝光标的终止行  
DH＝行(Y坐标)  
DL＝列 (X坐标)  

__5、功能04H__  
功能描述：获取当前状态和光笔位置  
入口参数：AH＝04H  
出口参数：AH＝00h——光笔未按下/未触发，01h——光笔已按下/已触发  
BX＝象素列(图形X坐标)  
CH＝象素行(图形Y坐标，显示模 式：04H~06H)  
CX＝象素行(图形Y坐标，显示模式：0DH~10H)  
DH＝字符行(文本Y坐标)  
DL＝字符列(文本X坐 标)  

__6、功能05H__  
功能描述：设置显示页，即选择活动的显示页  
入口参数：AH＝05H  
AL＝显示页  

对于CGA、EGA、MCGA和VGA，其显示页如下表所列： 模式页数显示器类型  
00H、01H0~7CGA、EGA、MCGA、VGA  
02H、 03H0~3CGA   
02H、03H0~7EGA、MCGA、VGA  
07H0~7EGA、VGA   
0DH0~7EGA、VGA  
0EH0~3EGA、VGA  
0FH0~1EGA、VGA    
10H0~1EGA、VGA  

对于PCjr：
AL＝80H——读取CRT/CPU页寄存器  
81H——设置CPU页寄存器  
82H——设置CRT页寄存器   
83H——设置CRT/CPU页寄存器  
BH＝CRT页(子 功能号82H和83H)  
BL＝CPU页(子功能号81H和83H)  
出口参数：对于前者，无出口参数，但对PCjr在子功能80H~83H 调用下，  有：BH＝CRT页寄存器，BL＝CPU页寄存器  

__7、功能06H和07H__  
功能描述：初始化屏幕或滚屏  
入口 参数：AH＝06H——向上滚屏，07H——向下滚屏  
AL＝滚动行数(0——清窗口)  
BH＝空白区域的缺省属性  
(CH、CL)＝ 窗口的左上角位置(Y坐标，X坐标)  
(DH、DL)＝窗口的右下角位置(Y坐标，X坐标)  
出口参数：无  

__8、功能 08H__  
功能描述：读光标处的字符及其属性  
入口参数：AH＝08H  
BH＝显示页码  
出口参数：AH＝属性  
AL＝字符  

__9、功能09H__  
功能描述：在当前光标处按指定属性显示字符  
入口参数：AH＝09H  
AL＝字符   
BH＝ 显示页码  
BL＝属性(文本模式)或颜色(图形模式)  
CX＝重复输出字符的次数  
出口参数：无  

__10、功能 0AH__  
功能描述：在当前光标处按原有属性显示字符  
入口参数：AH＝0AH  
AL＝字符  
BH＝显示页码  
BL＝颜色 (图形模式，仅适用于PCjr)  
CX＝重复输出字符的次数  
出口参数：无  

__11、功能0BH__  
功能描述：设置调 色板、背景色或边框  
入口参数：AH＝0BH  
设置颜色：BH＝00H，01＝颜色  
选择调色板：BH＝01H，BL＝调色板 (320×200、4种颜色的图形模式)   
出口参数：无  

__12、功能0CH__  
功能描述：写图形象素  
入口参 数：AH＝0CH  
AL＝象素值  
BH＝页码  
(CX、DX)＝图形坐标列(X)、行(Y)  
出口参数：无  

__13、功能0DH__  
功能描述：读图形象素  
入口参数：AH＝0DH  
BH＝页码  
(CX、DX)＝图形坐标列(X)、行(Y)  
出口参数：AL＝象素值  

__14、功能0EH__  
功能描述：在Teletype模式下显示字符  
入口参数：AH＝0EH  
AL＝ 字符   
BH＝页码  
BL＝前景色(图形模式)  
出口参数：无  

__15、功能0FH__  
功能描述：读取显示器模式  
入口参数：AH＝0FH  
出口参数：AH＝屏幕字符的列数  
AL＝显示模式(参见功能00H中的说明)  
BH＝页码  

__16、功能10H__  
功能描述：颜色中断。
  
其子功能说明如下：  
00H — 设置调色板寄存器  
01H — 设置边框颜色  
02H — 设置调色板和边框  
03H — 触发闪烁/亮显位  
07H — 读取调色板寄存器  
08H — 读取边框颜色  
09H — 读取调色板和边框  
10H — 设置颜色寄存器  
12H — 设置颜色寄存器块  
13H — 设置颜色页状态  
15H — 读取颜色寄存器  
17H — 读取颜色寄存器块  
1AH — 读取颜色页状态  
1BH — 设置灰度值  

__17、功能11H__  
功能描述：字体中断。
  
其子功能说明如下：  
00H装入用户字体和可编程控制器  
10H装入用户字体和可编程控制器  
01H装入 8×14 ROM字体和可编程控制器  
11H装入8×14 ROM字体和可编程控制器  
02H装入8×8 ROM字体和可编程控制器  
12H 装入8×8 ROM字体和可编程控制器  
03H设置块指示器  
04H装入8×16 ROM字体和可编程控制器  
14H装入 8×16 ROM字体和可编程控制器  
20H设置INT 1Fh字体指针  
21H为用户字体设置INT 43h  
22H为 8×14 ROM字体设置INT 43H  
23H为8×8 ROM字体设置INT 43H   
24H为8×16 ROM字体设置INT 43H  
30H 读取字体信息  

__18、功能12H__  
功能描述：显示器的配置中断。  

其子功能说明如下：  
10H — 读取配置信息  
20H — 选择屏幕打印  
30H — 设置扫描行  
31H — 允许/禁止装入缺省调色板  
32H — 允许/禁止显示  
33H — 允许/ 禁止灰度求和  
34H — 允许/禁止光标模拟  
35H — 切换活动显示  
36H — 允许/禁止屏幕刷新  

__19、功能 13H__   
功能描述：在Teletype模式下显示字符串  
入口参数：AH＝13H  
BH＝页码  
BL＝属性(若AL=00H或 01H)  
CX＝显示字符串长度  
(DH、DL)＝坐标(行、列)  
ES:BP＝显示字符串的地址 AL＝显示输出方式  
0——字符串中只含显示字符，其显示属性在BL中。显示后，光标位置不变  
1——字符串中只含显示字符，其显示属性在BL中。显示后，光标位置改变  
2——字符串中含显示字符和显示属性。显示后，光标位置不变  
3——字符串中含显示字符和显示属性。显示后，光标位置改变  
出口参数：无  

__20、 功能1AH__  
功能描述：读取/设置显示组合编码，仅PS/2有效，在此从略  

__21、功能1BH__  
功能描述：读取功能/ 状态信息，仅PS/2有效，在此从略

__22、功能1CH__  
功能描述：保存/恢复显示器状态，仅PS/2有效，在此从略



</br>

------------------------------  
Refereces:  
cnblogs.飞翔的翅膀 :  <http://www.cnblogs.com/magic-cube/archive/2011/10/19/2217676.html>  
CSDN.hua19880705的专栏:  <http://blog.csdn.net/hua19880705/article/details/8125706>  
</br>
Author: xx  
Time: 2016.1.9  