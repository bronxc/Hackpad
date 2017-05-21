#! /usr/bin/python
#! coding=utf-8

"""
Description: The rail fence cipher
Author: xx
Time: 2017.5.21
"""

def decodeRailFence():
    encodeStr = raw_input("Input string you want to decode:\n")
    length = len(encodeStr)
    group = []
    for i in range(2, length):
        if(length%i == 0):
            group.append(i);

    for i in group:
        num = length / i
        result = {x: "" for x in range(num)}
        for j in range(length):
            posi = j % num
            result.update({posi: result[posi]+encodeStr[j]})

        s = ""
        for j in range(num):
            s = s + result[j]
        print "split by " + str(i) + ":\t" + s

if __name__ == "__main__":
    decodeRailFence()
