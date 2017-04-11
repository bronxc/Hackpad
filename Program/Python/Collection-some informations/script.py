#! /usr/bin/python
# coding=utf-8

import requests
import re
import sys

reload(sys)
sys.setdefaultencoding('utf-8')

cookie = "v3hW_2132_saltkey=Jk809911; v3hW_2132_lastvisit=1489236949; UM_distinctid=15abda76cc05eb-0d49b6afa7ea36-1d3b6853-fa000-15abda76cc1561; v3hW_2132_visitedfid=395D389; v3hW_2132_sendmail=1; v3hW_2132_secqaa=213.5f059eb1c4ca759689; v3hW_2132_ulastactivity=1276kjURLpuPzFpVCyTcG3Kn6srzXzszZFb%2BsL%2FManI%2FjwgsgzOG; v3hW_2132_auth=1614WvWd7qu73MVasu8%2BAmu9%2BwIYkhGsvqvWtzoYNahT%2BDGZvDNebm7YISeY%2B%2BtgjPNrQZ25jSo5d0wMxso6EfSdMgY; v3hW_2132_lastcheckfeed=201834%7C1489725045; v3hW_2132_lip=222.196.193.180%2C1489724981; v3hW_2132_st_t=201834%7C1489725048%7Cd336ed6d3dc7364650ad1408845c1478; v3hW_2132_forum_lastvisit=D_389_1489369299D_395_1489725048; v3hW_2132_lastact=1489725068%09forum.php%09viewthread; v3hW_2132_st_p=201834%7C1489725068%7C98d02fff4dafdb9329ebc7d936b139d7; v3hW_2132_viewid=tid_1650823; v3hW_2132_sid=VAbkjD; CNZZDATA5360190=cnzz_eid%3D1848325456-1489240431-%26ntime%3D1489723025; v3hW_2132_smile=10D1"
headers = {"Cookie": cookie}

url = "http://bbs.uestc.edu.cn/forum.php?mod=forumdisplay&fid=395&page=2"
response = requests.get(url, headers=headers)

regular = '\<em\>\[\<a href="http://bbs\.uestc\.edu\.cn/forum\.php\?mod=forumdisplay&fid=\d{3}&amp;filter=typeid&amp;typeid=\d{4}"\>.*?\</a\>\]\</em\> \<a href=.*?\</a\>'
pattern = re.compile(regular, re.DOTALL);
filterString = re.findall(pattern, response.text)

regular = ' \<a href=.*?\</a\>'
pattern = re.compile(regular, re.DOTALL);
result = []

for item in filterString:
    result.append(re.findall(pattern, item))

regularUrl = 'http://bbs.uestc\.edu\.cn.*?3D2'
regularName = '[^\x00-\xff]'
patternUrl = re.compile(regularUrl, re.DOTALL);
patternName = re.compile(regularName, re.DOTALL);
dic = {}

for item in result:
    url = patternUrl.findall(item[0])
    nameList = patternName.findall(item[0])
    name = ""

    for j in nameList:
        name = name + j
    dic[url[0]] = name

#xxxxxxx

for key in dic:
    finalUrl = key.replace(";", "&")
    print dic[key]
    response = requests.get(finalUrl, headers=headers)
    fileObj = file(dic[key]+".html", "w+")
    fileObj.write(response.text)
    fileObj.close

