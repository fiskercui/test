import sys
import os, os.path
import shutil
import json, os, re, io,codecs


def copy_files(src, dst):
    if os.path.exists(dst) == 0:
   		os.mkdir(dst)

    for item in os.listdir(src):
        path = os.path.join(src, item)
        # Android can not package the file that ends with ".gz"
        if not item.startswith('.') and not item.endswith('.gz') and os.path.isfile(path):
        	# if os.path.exists(dst) == 0:
        	# 	os.mkdir(dst)
        	# else:
        	# 	os.remove(dst)
        	# 	os.mkdir(dst)
			shutil.copy(path, dst)
        if os.path.isdir(path):
            new_dst = os.path.join(dst, item)
            print ("new_dst:%s" %(new_dst,))
            copy_files(path, new_dst)



copy_files('./sdkres/360/res', './proj.androidtest/360/res')
copy_files('./sdkres/360/libs', './proj.androidtest/360/libs')


def find_string(file, key):
	try: 
		with codecs.open(file, 'r', 'utf-8') as f:
			content = f.readlines()
	except Exception, e:
		print "sss"
		return
	print content

	newContent = ""
	for item in content:
		newContent += item
	print "start"
	# print newContent
	str = re.search(r'package\s*=\s*"(.*)"', newContent)
	if not str:
		print "None"
	else:
		print str.group(0)
		print str.group(1)
	print "end"

	name="Hello,My name is kuangl,nice to meet you..."
	k=re.match(r"(\H....)",name)

	if k:
		print k.group(0),'\n',k.group(1)
	else:
		print "Sorry,not match!"


find_string('./proj.android/360/AndroidManifest.xml', "com.sevenroad.sexymaid")




def testString():
	astring = "hello world"
	astring.replace("world", "python")
	print astring
	astring = astring.replace("world", "python")
	print astring

testString()
