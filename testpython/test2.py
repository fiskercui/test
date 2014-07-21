# import json 
# with open("test.json") as json_file:
# 	json_data = json.load(json_file)
# 	print(json_data)
# print json_data["91android"]
# print json_data["91android"]["app_value"]

# print "=========="
# for item in json_data:
# 	print item

# print json_data
# print json.dumps(json_data)

# with open('out.txt', 'w') as outfile:
#   json.dump(json_data, outfile)

# test outfile read
import json 
with open("out.txt") as json_file:
	json_data = json.load(json_file)
	print(json_data)
print json_data["91android"]
print json_data["91android"]["app_value"]


print "user.json start"
with open("user.json") as json_file:
	json_data2 = json.load(json_file)
	print(json_data2)

print "user.json end"

if not json_data2["channels"]["91assist_android"].has_key("package"):
	print "Ok"

print "Users connected: %s:%s" % ("hello", "world") 

# with open("ant.test.property", 'w') as outfile

#init sub channel text
def initChannelConfig(jsondata):
	writetext = ""
	writetext = writetext + ("%s=%s\n"%( "key.store",jsondata["key.store"],))
	writetext = writetext + ("%s=%s\n"%( "key.alias",jsondata["key.alias"],))
	writetext = writetext + ("%s=%s\n"%( "key.store.password",jsondata["key.store.password"],))
	writetext = writetext + ("%s=%s\n"%( "key.alias.password",jsondata["key.alias.password"],))
	writetext = writetext + ("%s=%s\n"%( "app_name",jsondata["app_name"],))
	writetext = writetext + ("%s=%s\n"%( "app_version",jsondata["app_version"],))
	writetext = writetext + ("%s=%s\n"%( "versionCode",jsondata["versionCode"],))
	writetext = writetext + ("%s=%s\n"%( "versionName",jsondata["versionName"],))
	return writetext

print initChannelConfig(json_data2)

#check if channel exist
def ensure_dir(f):
	import os
	print f
	d = os.path.dirname(f)
	print d
	if not os.path.exists(d):
		os.makedirs(d)

# write channel config
def writeChannelConfig(channel, jsondata):
	channelPath = './pyAndroid/%s/' %(channel,)
	antPath = '%s/ant.properties' %(channelPath,)
	#need to be delete
	ensure_dir(channelPath)
	with open(antPath, 'w') as the_file:
		the_file.write(initChannelConfig(jsondata))


#write all channel
def writeAllChannelConfig(jsondata):
	print jsondata["market_channels"]
	for  item in jsondata["market_channels"]:
		writeChannelConfig(item, jsondata)
	# for item in jsondata["market_channels"]
	# 	print item
print "writeAllChannelConfig start"
writeAllChannelConfig(json_data2)
print "writeAllChannelConfig end"



	# writetext = writetext + "%s=%s", @(item[])

#define function test
def firstvalue(a,b):
	c = a + b
	return c
print firstvalue(1,2)


userCount = 6
print "Users connected: %d" % (userCount, ) 

testfile = "test.json"
userfile = "user.json"

def testVar():
	testfile = "heihei"
	print testfile
	print "%.3s" %("jcodeer")
	print "hello world%s" %(testfile)

testVar()
print testfile

# print data