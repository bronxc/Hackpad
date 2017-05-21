#! /usr/bin/python
#! coding=utf-8

"""
@Description: Caesar code decode program.
@Author: xx
@Time: 2017.5.21
"""

def decodeCaesarCode():
    encodeStr = raw_input("Input string you want to decode:\n")
    length = len(encodeStr)

    for i in range(26):
        s = ""
        for j in range(length):
            ch = ord(encodeStr[j])
            if (ord(encodeStr[j]) >= 65) and (ord(encodeStr[j]) <= 90) or (ord(encodeStr[j]) >= 97) and (ord(encodeStr[j]) <= 122):
                ch = ord(encodeStr[j]) + i
                if(ord(encodeStr[j]) <= 90 and ch > 90) or (ord(encodeStr[j]) >= 97 and ch > 122):
                    ch = ch - 26

            #merge
            s = s + chr(ch)

        print "Rot " + str(i) + ":\t" + s

if __name__ == "__main__":
    decodeCaesarCode()
