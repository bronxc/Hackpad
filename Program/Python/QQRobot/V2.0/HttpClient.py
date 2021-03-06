# -*- coding: utf-8 -*-

import cookielib
import urllib
import urllib2
import socket

class HttpClient:
	__cookie = cookielib.CookieJar()
	__req = urllib2.build_opener(urllib2.HTTPCookieProcessor(__cookie))
	__req.addheaders = [
		('Accept', 'application/javascript, */*;q=0.8'),
		('User-Agent', 'Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0)')
	]
	urllib2.install_opener(__req)

	def Get(self, url, refer=None):
		try:
			req = urllib2.Request(url)
			if not (refer is None):
				req.add_header('Referer', refer)
			return urllib2.urlopen(req, timeout=120).read()
			return e.read()
		except socket.timeout, e:
			return ''
		except socket.error, e:
			return ''

	def Post(self, url, data, refer=None):
		try:
			req = urllib2.Request(url, urllib.urlencode(data))
			if not (refer is None):
				req.add_header('Referer', refer)
			return urllib2.urlopen(req, timeout=120).read()
		except urllib2.HTTPError, e:
			return e.read()
		except socket.timeout, e:
			return ''
		except socket.error, e:
			return ''

	def getCookie(self, key):
		for c in self.__cookie:
			if c.name == key:
				return c.value
		return ''

	def setCookie(self, key, val, domain):
		ck = cookielib.Cookie(version=0, name=key, value=val, port=None, port_specified=False, domain=domain, domain_specified=False, domain_initial_dot=False, path='/', path_specified=True, secure=False, expires=None, discard=True, comment=None, comment_url=None, rest={'HttpOnly': None}, rfc2109=False)
		self.__cookie.set_cookie(ck)

	
	
	
	
	
	
	
