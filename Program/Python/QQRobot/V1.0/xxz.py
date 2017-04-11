# -*- coding:utf-8 -*-

import io
from PIL import Image, ImageTk
import Tkinter as tk
import datetime
import time
import json
import sys
import re
import ConfigParser
import codecs
from HttpClient import HttpClient
from CommandFunction import *

class SmallZ(HttpClient):
	ClientID = 53999199
	APPID = 501004106
	MiBaoCss = "m_webqq"
	JsVer = 10149
	initUrl = "https://ui.ptlogin2.qq.com/cgi-bin/login?daid=164&target=self&style=16&mibao_css=m_webqq&appid=501004106&enable_qlogin=0&no_verifyimg=1&s_url=http%3A%2F%2Fw.qq.com%2Fproxy.html&f_url=loginerroralert&strong_login=1&login_state=10&t=20131024001"
	ptwebqq = ""
	psessionID = ""
	Referer = "http://d1.web2.qq.com/proxy.html?v=20151105001&callback=1&id=2"
	StarTime = int(time.mktime(datetime.datetime.now().timetuple())) * 1000
	
	command = {}
	flag = 1 			#fisrt recevie message, and show welcome information
	execFun = {}
			   
	def __init__(self):
		self.execFun = {"-command" : commandFunction,
						"-introduce" : introduceFunction,
	                    "-rand" : randFunction,
						"-time" : timeFunction,
						"-joke" : jokeFunction,
						"-fight" : fightFunction}

	def getTwoDimension(self):
		root = tk.Tk()
		url = "https://ssl.ptlogin2.qq.com/ptqrshow?appid={0}&e=0&l=M&s=5&d=72&v=4&t=0.5462884965818375".format(self.APPID)

		image_bytes = self.Get(url)
		data_stream = io.BytesIO(image_bytes)
		pil_image = Image.open(data_stream)

		w, h = pil_image.size

		fname = url.split('/')[-1]
		sf = "{} ({}x{})".format(fname, w, h)
		root.title(sf)

		tk_image = ImageTk.PhotoImage(pil_image)

		label = tk.Label(root, image=tk_image, bg='brown')
		label.pack(padx=5, pady=5)

		root.mainloop()
		
	def preLogin(self):
		print "firstLogin Function"
		current_time = int(time.mktime(datetime.datetime.now().timetuple())) * 1000
		url = "https://ssl.ptlogin2.qq.com/ptqrlogin?webqq_type=10&remember_uin=1&login2qq=1&aid={0}&u1=http%3A%2F%2Fw.qq.com%2Fproxy.html%3Flogin2qq%3D1%26webqq_type%3D10&ptredirect=0&ptlang=2052&daid=164&from_ui=1&pttype=1&dumy=&fp=loginerroralert&action=0-0-{1}&mibao_css={2}&t=undefined&g=1&js_type=0&js_ver={3}&login_sig=&pt_randsalt=0".format(self.APPID, current_time - self.StarTime, self.MiBaoCss, self.JsVer)

		response = self.Get(url, self.initUrl)

		strbuffer = response.split("'")
		jump_url = strbuffer[5]

		print "Jump Url ->" + jump_url
		response = self.Get(jump_url)
		self.ptwebqq = self.getCookie('ptwebqq')

		print "ptwebqq->" + self.ptwebqq
		return 0
		
	def login(self):
		print "login Function"
		url = "http://s.web2.qq.com/api/getvfwebqq?ptwebqq={0}&clientid={1}&psessionid=&t={2}".format(self.ptwebqq, self.ClientID, self.StarTime)
		response = self.Get(url, self.Referer)
		print response

		url = "http://d1.web2.qq.com/channel/login2"
		data = {'r' : '{{"ptwebqq":"{0}","clientid":{1},"psessionid":"","status":"online"}}'.format(self.ptwebqq, self.ClientID)}
		response = self.Post(url, data, self.Referer)
		print "Login Result->" + response
		result = json.loads(response)
		self.psessionid = result['result']['psessionid']
		print "psessionID->" + self.psessionid
		print "\n\n*************Login Success**************\n\n"
		
	def receiveMessage(self):
		print "[+]Start Receive Message"
		
		while True:
			url = "http://d1.web2.qq.com/channel/poll2"
			data = {'r' : '{{"ptwebqq":"{0}","clientid":{1},"psessionid":"{2}","key":""}}'.format(self.ptwebqq, self.ClientID, self.psessionid)}
			response = self.Post(url, data, self.Referer)
			ret = json.loads(response)
			if response == '':
				continue
			if ret['retcode'] == 103:
				print "retcode is 103, please login at web, then run this"
				break
			
			try:
				buffer = ret['result'][0]
			except KeyError:
				continue
			groupOrPerson = buffer['poll_type']
			
			#get content
			content_temp = ""
			value = buffer['value']
			for i in value['content']:
				if type(i) == list:
					continue
				content_temp += i
			
			#may be need filter content_temp
			
			content = content_temp
			if groupOrPerson == "group_message":
				print "group_message"
				
				from_uin = value['from_uin']
				send_uin = value['send_uin']
				info = "->Time: {0} Group:{1} Person;{2} Content:{3}".format(datetime.datetime.utcnow(), from_uin, send_uin, content)
				print info
				
				#show welcome information
				if(self.flag == 0):
					content = self.command['welcome']
					self.sendMessageGroup(from_uin, content)
					self.flag = 1
				
				#retrun message
				content = self.getMessageGroup(content)
				if content != "":
					self.sendMessageGroup(from_uin, content)
				
			if groupOrPerson == "message":
				print "message"

				from_uin = value['from_uin']
				info = "->Time: {0} Person;{1} Content:{2}".format(datetime.datetime.utcnow(), from_uin, content)
				print info
				
				content = self.getMessagePerson(content)
				if content != "":
					self.sendMessagePerson(from_uin, content)
			
			time.sleep(1)
	
	def sendMessageGroup(self, group_uid, content):
		msgId = 12341234
		url = "http://d1.web2.qq.com/channel/send_qun_msg2"
		data = {'r' : '{{"group_uin":{0},"content":"[\\"{4}\\",[\\"font\\",{{\\"name\\":\\"宋体\\",\\"size\\":10,\\"style\\":[0,0,0],\\"color\\":\\"000000\\"}}]]","face":0,"clientid":{1},"msg_id":{2},"psessionid":"{3}"}}'.format(group_uid, self.ClientID,  msgId, self.psessionid, content)}
		response = self.Post(url, data, self.Referer)
		
	def sendMessagePerson(self, fuin, content):
		msgId = 12341234
		url = "http://d1.web2.qq.com/channel/send_buddy_msg2"
		data = {'r' : '{{"to":{0},"content":"[\\"{4}\\",[\\"font\\",{{\\"name\\":\\"宋体\\",\\"size\\":10,\\"style\\":[0,0,0],\\"color\\":\\"000000\\"}}]]","face":570,"clientid":{1},"msg_id":{2},"psessionid":"{3}"}}'.format(fuin, self.ClientID,  msgId, self.psessionid, content)}
		response = self.Post(url, data, self.Referer)
		
	def getMessageGroup(self, key):
		content = ""
		segment = ""
		
		if not key.startswith("-"):
			return content
		
		#split
		#Eggs
		else:
			if(key.startswith("-fight@")):
				strbuffer = key.split("@")
				key = strbuffer[0]
				segment = strbuffer[1][0:20]
			else:
				pass
		
		#segment Handle
		if segment == "":
			segment = "blank"
		
		try:
			if self.command.get(key):
				operation = self.command[key]
				if operation.startswith("&"):
					content = self.execFun.get(key)(self)		#run Function, return content
					if key == "-fight":
						content = content.format(segment)
				else:
					content = operation
			else:
				content = ""
		except TypeError:
			content = ""
		
		return content
		
	def getMessagePerson(self, key):
		content = "为什么私聊我，你是不是喜欢我呀"
		return content
		
	def Welcome(self, fuin, content):
		msgId = 12341234
		url = "http://d1.web2.qq.com/channel/send_buddy_msg2"
		data = {'r' : '{{"to":{0},"content":"[\\"{4}\\",[\\"font\\",{{\\"name\\":\\"宋体\\",\\"size\\":10,\\"style\\":[0,0,0],\\"color\\":\\"000000\\"}}]]","face":570,"clientid":{1},"msg_id":{2},"psessionid":"{3}"}}'.format(fuin, self.ClientID,  msgId, self.psessionid, content)}
		response = self.Post(url, data, self.Referer)
		
	def setCommand(self, key):
		for i in key:
			self.command[i[0]] = i[1]
		
#end class SmallZ		

def loadConfig(SmallZ):
	conf = ConfigParser.ConfigParser()
	conf.readfp(codecs.open(".\conf\Info.conf", "r", "utf-8-sig"))
	
	#sections [Welcome]
	welcome_key = conf.get("Welcome", "welcome1") + "\n"
	key  = conf.items("Key")
	for i in key:
		welcome_key = welcome_key + "[+]" + i[0] + "	" + i[1] + "\n"
	welcome_key += conf.get("Welcome", "welcome2")
	temp = [("welcome", welcome_key)]
	SmallZ.setCommand(temp)
	
	temp = [("content", conf.get("Welcome", "content"))]
	SmallZ.setCommand(temp)
	
	#sections [Key]
	key  = conf.items("Key")
	SmallZ.setCommand(key)
	
	#sections [.Key]
	key  = conf.items(".Key")
	SmallZ.setCommand(key)
	



if __name__ == "__main__":
	reload(sys)
	sys.setdefaultencoding('utf-8')
	
	smallZ = SmallZ()
	
	print "[+]Load Config...\n"
	loadConfig(smallZ)
	
	print "\n[+]Login...\n"
	smallZ.getTwoDimension()
	smallZ.preLogin()
	smallZ.login()
	smallZ.receiveMessage()
		
	
	
	
	
	
	
	
	
	
	