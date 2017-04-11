# -*- coding:utf-8 -*-
import time
import datetime
import random
import os
import ConfigParser
import codecs
import json
from HttpClient import HttpClient

def commandFunction(SmallZ):
	content = SmallZ.command["welcome"]
	return content
	
def randFunction(SmallZ):
	content = ""
	num = random.randint(0,100)
	if num == 0:
		content += "你的人品为 " + str(num) + "（0-100）, \n我擦嘞，，，我竟无言以对，你让我说什么好。。"
	elif num >0 and num < 10:
		content += "你的人品为 " + str(num) + "（0-100）, \n我的天，这么低？你上辈子都干了什么。。。。。"
	elif num >= 10 and num < 40:
		content += "你的人品为 " + str(num) + "（0-100）, \n好低啊，估计你买个方便面，里面都没有面"
	elif num >= 40 and num < 60:
		content += "你的人品为 " + str(num) + "（0-100）, \n哟，要及格了呢，然后呢？然后呢？还是那么低"
	elif num >= 60 and num < 80:
		content += "你的人品为 " + str(num) + "（0-100）, \n哇，好高呀，不过比我起，还是低了那么一丢丢"
	elif num >= 80 and num < 90:
		content += "你的人品为 " + str(num) + "（0-100）, \n纳尼，大仙啊，人品这么高，肯定做了什么见不得人的事"
	elif num >= 90 and num <= 100:
		content += "你的人品为 " + str(num) + "（0-100）, \n你妹，分数有问题，不好意思啊，系统出了点问题"
	return content
	
def introduceFunction(SmallZ):
	content = SmallZ.command["content"]
	return content
	
def jokeFunction(SmallZ):
	content = ""
	conf = ConfigParser.ConfigParser()
	conf.readfp(codecs.open(".\conf\joke.conf", "r", "utf-8-sig"))
	length = len(conf.options("joke"))
	key = random.randint(1,length)
	content = conf.get("joke", str(key))
	
	return content
	
def timeFunction(SmallZ):
	content = datetime.datetime.now()
	return content
	
def fightFunction(SmallZ):
	content = ""
	win = random.randint(0,100)
	if win >= 0 and win < 2:
		content = "你被 " + SmallZ.parameter + " 打得连妈都不认识了"
	elif win >= 2 and win < 10:
		content = "你被 " + SmallZ.parameter + " 打得稀啪烂（PS:好像口音有点重）"
	elif win >= 10 and win < 30:
		content = "你被 " + SmallZ.parameter + " 打得粉身碎骨"
	elif win >= 30 and win < 50:
		content = "你被 " + SmallZ.parameter + " 打得鼻青脸肿"
	elif win >= 50 and win < 70:
		content = "你把 " + SmallZ.parameter + " 打得鼻青脸肿"
	elif win >= 70 and win < 90:
		content = "你把 " + SmallZ.parameter + " 打得粉身碎骨"
	elif win >= 90 and win < 99:
		content = "你把 " + SmallZ.parameter + " 打得稀啪烂（PS:好像口音有点重）"
	elif win >= 99 and win <= 100:
		content = "你把 " + SmallZ.parameter + " 打得连妈都不认识了"
	return content
	
def quesFunction(SmallZ):
	content = ""
	
	if SmallZ.parameter == "blank":
		return content
	
	content = "未开放该功能 -ques"
	return content
	
def apiFunction(SmallZ):
	#在此感谢图灵机器人的API
	content = ""
	httpclient = HttpClient()

	if SmallZ.parameter == "blank":
		return content
	
	url = "http://www.tuling123.com/openapi/api"
        #....my key in www.tuling123.com, if you want to use, sign up a new key better.
	data = {"key" : "9423edccf74e4a5792a62fc9cc13f97f",
			"info" : SmallZ.parameter}
	
	strbuffer = json.loads(httpclient.Post(url, data))
	if strbuffer["code"] == 40001:
		content = "-api " + "xx" + "未找到响应结果~试试其他的吧~"
		print "apiFunction() -> 40001"
	elif strbuffer["code"] == 40002:
		content = "-api " + "xx" + "未找到响应结果~试试其他的吧~"
	elif strbuffer["code"] == 40004:
		content = "-api " + "xx" + "小z今天累了呢，，明天再来吧~~"
	elif strbuffer["code"] == 40007:
		content = "-api " + "xx" + "未找到响应结果~试试其他的吧~"
		print "apiFunction() -> 40007"
	else:
		content_temp = strbuffer["text"]
	
	#Handle content_temp
	flag = 0
	for i in content_temp:
		if i == "<":
			flag = 1
		if flag == 0:
			content += i
		if i == ">":
			flag = 0
	
	return content

if __name__ == "__main__":
	print "ok"
	
	

	
	
	
	
	
	
	
	
	
	
	
	
	
	
