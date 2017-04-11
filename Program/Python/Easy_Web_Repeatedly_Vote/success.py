import urllib2
import urllib
import time
import os

data = {'SelectID' : '130'}
command1 = "netsh interface set interface name=\"network\" admin=DISABLED"
command2 = "netsh interface set interface name=\"network\" admin=ENABLED"
while 1:
	for i in range(1,11):
		f = urllib2.urlopen(
				url     = 'http://flyz.votezg.com/ToupiaoSave.asp',
				data    = urllib.urlencode(data)
		)
		print f.read()
		time.sleep(35)
	os.system(command1)
	os.system(command2)