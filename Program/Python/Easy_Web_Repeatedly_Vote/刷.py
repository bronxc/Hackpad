import urllib2
import urllib
import time

data = {'SelectID' : '130'}
for i in range(1,11):
	f = urllib2.urlopen(
			url     = 'http://flyz.votezg.com/ToupiaoSave.asp',
			data    = urllib.urlencode(data)
	)
	print f.read()
	time.sleep(35)


"""import time
for i in range(1,11):
	time.sleep(5)
	print i"""