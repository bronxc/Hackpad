#! /usr/bin/python
# coding=utf-8

import socket
import time

s = socket.socket()
host = "pwnable.kr"
port = 9007

s.connect((host, port))
s.recv(2048)
print "time.sleep(4)..."
time.sleep(4)
#
for k in range(0, 100):
    buf= s.recv(2048)
    spacePosition = buf.find(" ")
    N = int(buf[2: spacePosition])
    C = int(buf[spacePosition+3: len(buf)-1])
    print k, "N=", N, "C=", C

    start = 0;
    end = N-1;
    mid = (start + end)/2
    for i in range(C):
        buf = ""
        #print "start:", start, "mid:", mid, "end:",end
        for j in range(start, mid+1):
            buf += str(j)
            buf += " "
        buf += "\n"
        s.send(buf)
        buf = s.recv(2048)
        #print i, buf
        if(int(buf) == (mid - start + 1) * 10):
            start = mid + 1
            mid = (start + end)/2
        else:
            end = mid
            mid = (start + end)/2

    s.send(str(mid) + "\n")
    print s.recv(2048)

print s.recv(2048)
s.close()







