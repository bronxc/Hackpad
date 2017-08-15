from idaapi import *  
from idc import *  
import os

count = 0
eax_list = list()
ebx_list = list()

  
try:
    if debugger:
        print("Removing previous hook ...")
        debugger.unhook()
except:
    pass
AddBpt (0x403e65)
print "[*] set hook OK...\n"
StartDebugger("","","")  
for i in range(0,999):
    GetDebuggerEvent(WFNE_SUSP|WFNE_CONT, -1)
    print "[+]",i
    eax = GetRegValue("EAX")
    eax_list.append(eax)
    ebx = GetRegValue("EBX")
    ebx_list.append(ebx)
    if i == 998:
        print '[+] eax max : ',max(eax_list)
        index = eax_list.index(max(eax_list))
        a = ebx_list[index]
        #message( "[+] ebx max : %x",%(ebx_list[eax_list.index(max(eax_list))]))
        Message("%x"%a)
        print "max",GetString(a)
        del(eax_list[index])
        del(ebx_list[index])
#        
        print '[+] eax second : ',max(eax_list)
        index = eax_list.index(max(eax_list))
        a = ebx_list[index]
        #message( "[+] ebx max : %x",%(ebx_list[eax_list.index(max(eax_list))]))
        Message("%x"%a)
        print "second",GetString(a)
        del(eax_list[index])
        del(ebx_list[index])        
#        
        print '[+] eax third : ',max(eax_list)
        index = eax_list.index(max(eax_list))
        a = ebx_list[index]
        #message( "[+] ebx max : %x",%(ebx_list[eax_list.index(max(eax_list))]))
        Message("%x"%a)
        print "third",GetString(a)
        del(eax_list[index])
        del(ebx_list[index])
