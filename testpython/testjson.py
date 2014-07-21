import json
print json.dumps(['foo', {'bar': ('baz', None, 1.0, 2)}])
print json.dumps("\"foo\bar")
print json.dumps(u'\u1234')
print json.dumps('\\')
print json.dumps({"c": 0, "b": 0, "a": 0}, sort_keys=True)
{"a": 0, "b": 0, "c": 0}
from StringIO import StringIO
io = StringIO()
json.dump(['streaming API'], io)
print "hello world"
print json.JSONEncoder().encode({"foo": ["bar", "baz"]})

print io.getvalue()
print("----------")
io = StringIO('["streaming API"]')
print json.load(io)


import types
import urllib2
import json



duan = "--------------------------"

def registerUrl():
	try:
		url ="http://m.weather.com.cn/data/101010100.html"
		data = urllib2.urlopen(url).read()
		return data
	except Exception,e:
		print e
		
def jsonFile(fileData):
	file = open("d:\json.txt","w")
	file.write(fileData)
	file.close()

def praserJsonFile(jsonData):
	value = json.loads(jsonData)
	rootlist = value.keys()
	print rootlist
	print duan
	for rootkey in rootlist:
		print rootkey
	print duan
	subvalue = value[rootkey]
	print subvalue
	print duan
	for subkey in subvalue:
		print subkey,subvalue[subkey]
	
if __name__ == "__main__":
	# xinput = raw_input()
	# x = 130
	# xvalue = cmp(x,xinput)
	# print xvalue
	# print x/100.0
	# data = open('test.json', 'r')
	# print json.load(data)
	with open("test.json") as json_file:
	   	json_data = json.load(json_file)
   		print(json_data)

	# data = []
	# with open('test.json') as f:
	# 	for line in f:
 #    		data.append(json.loads(line))

	# from pprint import pprint
	# json_data=open('./test.json')
	# print json_data

	# data = json.load(json_data)
	# pprint(data)
	# json_data.close()
	# print data
	# data = registerUrl()
	# jsonFile(data)
	
	# praserJsonFile(data)
	

