# -*- coding:utf-8 -*-
import time
import datetime
import random
import os
import re

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
	content = "这还用讲吗？哎哟喂，你笑死我了，你这么大一个笑话"
	return content
	
def timeFunction(SmallZ):
	content = datetime.datetime.now()
	return content
	
def fightFunction(SmallZ):
	content = ""
	win = random.randint(0,100)
	if win >= 0 and win < 2:
		content = "你被 {0} 打得连妈都不认识了"
	elif win >= 2 and win < 10:
		content = "你被 {0} 打得稀啪烂（PS:好像口音有点重）"
	elif win >= 10 and win < 30:
		content = "你被 {0} 打得粉身碎骨"
	elif win >= 30 and win < 50:
		content = "你被 {0} 打得鼻青脸肿"
	elif win >= 50 and win < 70:
		content = "你把 {0} 打得鼻青脸肿"
	elif win >= 70 and win < 90:
		content = "你把 {0} 打得粉身碎骨"
	elif win >= 90 and win < 99:
		content = "你把 {0} 打得稀啪烂（PS:好像口音有点重）"
	elif win >= 99 and win <= 100:
		content = "你把 {0} 打得连妈都不认识了"
	return content

if __name__ == "__main__":
	print "ok"
	str = "\U0001f633"
	str1 = "啊"
	rex1 = r"\U00"
	print re.search(rex1, str1)
	

	
	
	
	
	
	
	
	
	
	
	
	
	
	