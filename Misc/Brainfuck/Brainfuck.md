#Brainfuck

--------------------------------  

###0x00 简介  
Brainfuck是一种极小化的计算机语言，它是由Urban Müller在1993年创建的。Müller的目标是建立一种简单的、可以用最小的编译器来实现的、符合图灵完全思想的编程语言。这种语言由八种状态构成，为Amiga机器编写的编译器（第二版）只有240个字节大小！


###0x01 原理  
下面是这八种状态的描述，其中每个状态由一个字符标识：  

|符号|含义|C语言表达|
|---|----|------|
|>|指针加一|ptr = ptr + 1
|<|指针减一|ptr = ptr - 1
|+|指针指向的字节的值加一|(\*ptr) = (\*ptr) + 1
|-|指针指向的字节的值减一|(\*ptr) = (\*ptr) - 1
|.|输出指针指向的单元内容（ASCⅡ码）|putchar(\*ptr)
|,|输入内容到指针指向的单元（ASCⅡ码）|(*ptr) = getchar()
|[|如果指针指向的单元值为零，向后跳转到对应的]指令的次一指令处 |while (\*ptr) {
|]|如果指针指向的单元值不为零，向前跳转到对应的[指令的次一指令处 | }


###0x02 编译器  
官方brainfuck解释器： 

	#include <stdio.h>;

	int  p, r, q;
	char a[5000], f[5000], b, o, *s=f;

	void interpret(char *c)
	{
        char *d;

        r++;
        while( *c ) {
        	switch(o=1,*c++) {
        	case '<': p--;        break;
        	case '>': p++;        break;
        	case '+': a[p]++;     break;
        	case '-': a[p]--;     break;
        	case '.': putchar(a[p]); fflush(stdout); break;
        	case ',': a[p]=getchar();fflush(stdout); break;
  	    	case '[':
        		for( b=1,d=c; b && *c; c++ )
        			b+=*c=='[', b-=*c==']';
     			if(!b) {
					c[-1]=0;
					while( a[p] )
        				interpret(d);
        			c[-1]=']';
        			break;
				}
			case ']':
				puts("UNBALANCED BRACKETS"), exit(0);
			case '#':
				if(q>2)
					printf("%2d %2d %2d %2d %2d %2d %2d %2d %2d %2d/n%*s/n",*a,a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],3*p+2,"^");
				break;
			default: o=0;
			}
			if( p<0 || p>100)
				puts("RANGE ERROR"), exit(0);
		}
		r--;
	}

	int main(int argc,char *argv[]) {
        FILE *z;

        q=argc;

        if(z=fopen(argv[1],"r")) {
                while( (b=getc(z))>0 )
					*s++=b;
                *s=0;
                interpret(f);
        }

		return 0;
	}

自己用C实现了一个，见附件。

------------------------------  
Reference:  
知乎： <http://www.zhihu.com/topic/19671339/hot>  
百度百科： <http://baike.baidu.com/link?url=z4pmJaQk9r29eFa2JdgfuiGyeaNRkZh26JORPrIqPBwtjHU3ya-a11z-c70CZbGpyD29ULIX_uv8A_0TflkkE_>  
Wiki：  <https://en.wikipedia.org/wiki/Brainfuck>  

</br>
Author: xx  
Time: 2016.10.30