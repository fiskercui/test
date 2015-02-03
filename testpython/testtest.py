import sys
import os, os.path
import shutil

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
            print ("path:%s, %s" %(path, dst,))
            shutil.copy(path, dst)
        if os.path.isdir(path):
            new_dst = os.path.join(dst, item)
            print ("new_dst:%s" %(new_dst,))
            copy_files(path, new_dst)


copy_files('./aadsf', './proj')
shutil.copy('./aadsf/cop.text', './aadsf/cop22.xml')