#C Memory Alignment

###0x00 问题引出  
(本文中的代码运行环境：Win7x64 ＋ VS2010， C语言)  
下面一段代码：

	#include <stdio.h>
	#include <windows.h>

	int main() {
		struct structA {
			char a;
			int b;
			char c;
		};
	
		struct structB {
			char a;
			char c;
			int b;
		};

		printf("structA size is %d\n", sizeof(structA));
		printf("structB size is %d\n", sizeof(structB));

		system("pause");
		return 0;
	}
	
运行结果：

	structA size is 12
    structB size is 8
    
structA 的 size 是12， structB 的 size 是8， 而不是6；  
structA 和 structB 中包含的数据类型都相同，但顺序不同， size也不同；
造成这种现象的原因是因为存在 “内存对齐”

	
###0x01 内存对齐  
__为什么需要内存对齐？__  
在现代计算机体系中，每次读写内存中数据，都是按字（word，4个字节，对于X86架构，系统是32位，数据总线和地址总线的宽度都是32位，所以最大的寻址空间为2的32次方 = 4GB，按A[31,30…2,1,0]这样排列，但是请注意为了CPU每次读写 4个字节寻址，A[0]和A[1]两位是不参与寻址计算的。）为一个块（chunks）来操作（而对于X64则是8个字节为一个块）。注意，这里说的 CPU每次读取的规则，并不是变量在内存中地址对齐规则。既然是这样的，如果变量在内存中存储的时候也按照这样的对齐规则，就可以加快CPU读写内存的速 度，当然也就提高了整个程序的性能，并且性能提升是客观，虽然当今的CPU的处理数据速度(是指逻辑运算等,不包括取址)远比内存访问的速度快，程序的执 行速度的瓶颈往往不是CPU的处理速度不够，而是内存访问的延迟，虽然当今CPU中加入了高速缓存用来掩盖内存访问的延迟，但是如果高密集的内存访问，一 种延迟是无可避免的，内存地址对齐会给程序带来了很大的性能提升。  

__一个例子__  

	struct test {
		int a;
	}
	
(假设32bit系统下，CPU读取是从0x00000000开始，4字节为一个读取块)  
假设上面整型变量的地址不是自然对齐，比如为0x00000002开始存储，那么它存储的地址为0x00000002-0x00000005，则CPU如果取它的值的话需要访问两次内存，第一次取从0x00000002-0x00000003的一个short，第二次取从0x00000004-0x00000005的一个short然后组合得到所要的数据。而如果变量在自然对齐位置上，则只要一次就可以取出数据。  

__内存对齐是编译器自动完成的__  
内存地址对齐是计算机语言自动进行的，也即是编译器所做的工作。但这不意味着我们程序员不需要做任何事情，因为如果我们能够遵循某些规则，可以让编译器做得更好，毕竟编译器不是万能的。

>以上内容是以 struct 结构体为例，实际中，无论是基本数据类型，还是数组，联合体都存在内存对齐。


###0x02 对齐规则
####1.基本数据类型  
在X86，32位系统下基于Microsoft、Borland和GNU的编译器，有如下数据对齐规则：  
a、一个char（占用1-byte）变量以1-byte对齐。  
b、一个short（占用2-byte）变量以2-byte对齐。  
c、一个int（占用4-byte）变量以4-byte对齐。  
d、一个long（占用4-byte）变量以4-byte对齐。  
e、一个float（占用4-byte）变量以4-byte对齐。  
f、一个double（占用8-byte）变量以8-byte对齐。  
g、一个long double（占用12-byte）变量以4-byte对齐。  
h、任何pointer（占用4-byte）变量以4-byte对齐。  

而在64位系统下，与上面规则对比有如下不同：  
a、一个long（占用8-byte）变量以8-byte对齐。  
b、一个double（占用8-byte）变量以8-byte对齐。  
c、一个long double（占用16-byte）变量以16-byte对齐。  
d、任何pointer（占用8-byte）变量以8-byte对齐。  


关于变量在内存中分布的简单案例。它们处在一个C模块的顶层。(x86平台下)

	char *p;
	char c;
	int x;

实际在内存中的存储方式是：
	
	char *p;      /* 4 bytes */
	char c;       /* 1 byte */
	//char pad[3];  /* 3 bytes */
	int x;        /* 4 bytes */
	
字符数组pad[3]意味着在这个结构体中，有3个字节的空间被浪费掉了。老派术语将其称之为“废液（slop）”。


####2.数组
按照基本数据类型对齐，但数组内元素类型相同，第一个对齐了后面的自然也就对齐了。   
	

####3.联合体
按其包含的长度最大的数据类型对齐。 

	#include <stdio.h>
	#include <windows.h>

	int main() {
		union unionA {
			char a;
			int b;
			char c;
		};

		union unionB {
			char a;
			int b;
			double c;
		};

		printf("unionA size is %d\n", sizeof(unionA));
		printf("unionB size is %d\n", sizeof(unionB));

		system("pause");
		return 0;
	}
	
运行结果：

	unionA size is 4
	unionB size is 8


####4.结构体
结构体数据对齐，是指结构体内的各个数据对齐。在结构体中的第一个成员的首地址等于整个结构体的变量的首地址，而后的成员的地址随着它声明的顺序和实际占用的字节数递增。为了总的结构体大小对齐，会在结构体中插入一些没有实际意思的字符来填充（padding）结构体。  

__在结构体中，成员数据对齐满足以下规则：__  
PS:每个特定平台上的编译器都有自己的默认“对齐系数”(也叫对齐模数)。程序员可以通过预编译命令#pragma pack(n)，n=1,2,4,8,16来改变这一系数，其中的n就是你要指定的“对齐系数”。  

1. 结构体中的第一个成员的首地址也即是结构体变量的首地址。  
2. 结构体中的每一个成员的首地址相对于结构体的首地址的偏移量（offset）是该成员数据类型大小和#prama pack指定的数值，比较小的那一个的整数倍。  
3. 结构体的总大小是对齐模数（对齐模数等于#pragma pack(n)所指定的n与结构体中最大数据类型的成员大小的最小值）的整数倍。  

>当#pragma pack的n值等于或超过所有数据成员长度的时候，这个n值的大小将不产生任何效果。  

举个例子:  

	#include <stdio.h>
	#include <windows.h>

	int main() {
		struct structA {
			char a;			//1bytes, All:1bytes
			//char pad[3]	//3bytes, All:4bytes
			int b;			//4bytes, All:8bytes
			char c;			//1bytes, All:9bytes
			//char pad[7]	//7bytes, All:16bytes
			double d;		//8bytes, All:24bytes
			int e;			//4bytes, All:28bytes
			//char pad[4]	//4bytes, Max type is double: 8bytes, All:32bytes
		};
		printf("The structA size is %d\n", sizeof(structA));
		//prints "The structA size is 32"

		system("pause");
		return 0;
	}


若一个结构体中包含数组：

* 数组中在存储时，按照每一个元素对齐来进行储存。  
* 结构体总大小对齐时，数组的大小以每一个元素的类型大小来计算。  

举个例子：

	#include <stdio.h>
	#include <windows.h>

	int main() {
		struct structA {
			char a;			//1bytes, All:1bytes
			//char pad[3];	//3bytes, All:4bytes
			int b[3];		//4+4+4=12bytes, All:16bytes
			short c;		//2bytes, All: 18bytes
			//char pad[2]	//2bytes, Max type is int: 4bytes, All: 20bytes
		};
		printf("The structA size is %d\n", sizeof(structA));
		//prints "The structA size is 20"

		system("pause");
		return 0;
	}
	
	
若一个结构体中还包含另一个结构体：

* 被包含的结构体进行存储时，偏移量（offset）是被包含结构体中最大数据类型和#prama pack指定的数值，比较小的那一个的整数倍。    
* 结构体总大小对齐时，找出结构体中的最大数据类型和#prama pack进行比较，选择最小值作为对齐模数。  

举个例子：

	#include <stdio.h>
	#include <windows.h>

	int main() {
		struct structA {
			int a;				//4bytes, All:4bytes
			char b;				//1bytes, All:5bytes
			//char pad[3];		//3bytes, All:8bytes
			double c;			//8bytes, All:16bytes
								//Max type is double: 8bytes, All:16bytes
		};
		struct structB {
			char d;				//1bytes, All:1bytes
			//char pad[7];		//7bytes, All:8bytes
			struct structA e;	//In structA, Max type is double: 8bytes, total size is 16bytes; 16bytes, All:24bytes
			short f;			//2bytes, 26bytes
			//char pad[6];		//6bytes, Max type is double from structA: 8bytes, All:32bytes
		};
		printf("The structB size is %d\n", sizeof(structB));
		//prints "The structB size is 32"

		system("pause");
		return 0;
	}



####5.枚举
（这里和内存对齐没有什么关系，不过都提到了，顺便说说枚举）  
无论是x86平台还是x64，枚举类型的大小都是4个byte  

	#include <stdio.h>
	#include <windows.h>

	int main() {
		enum fruit {
			apple,
			banana,
			orange
		};
		printf("The fruit size is %d\n", sizeof(fruit));
		//prints "The fruit size is 4"

		system("pause");
		return 0;
	}

之所以是4个字节是因为enum类型是作为一个int来存储的。

下面展示了一个存储方式：  
（这是一个12个值的枚举类型的储存，12个值仅会使用到4位，为了方便演示，前面的0就省略了）

	0000	January
	0001	February
	0010	March
	0011	April
	0100	May
	0101	June
	0110	July
	0111	August
	1000	Septemper
	1001	October
	1010	November
	1011	December
	1100	** unused **
	1101	** unused **
	1110	** unused **
	1111	** unused **



</br></br>

-------------------------------
参考资料：  
百度百科.内存对齐： <http://baike.baidu.com/link?url=-BOJT47Tk6m4c5o21Lf2l7FaCDtZWUNmJn9JRjImkwlxsT6oHprR4JyR1SOKl0CxfmVM-Z6eLLrYWW4PgxmxQAqWTPlCGo-36563x_oc7WaGi4fahePcBoZfCNdT2JT2>  

新浪博客.人世间的金某人的博客：<http://blog.sina.com.cn/s/blog_6cd90f6901013tek.html>  

百度经验.enum的内存大小：<http://jingyan.baidu.com/article/1e5468f92bef09484961b782.html>  

Github.The Lost Art of C Structure Packing中文翻译：<https://github.com/ludx/The-Lost-Art-of-C-Structure-Packing>  

CSDN.蛋蛋强的专栏：<http://blog.csdn.net/sdwuyulunbi/article/details/8510401>
  
CSDN.beachboyy：<http://blog.csdn.net/hbuxiaofei/article/details/9491953>

</br>
Time: 2016.10.11