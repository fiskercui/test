from Conf import *
import string
# a = object.__new__(Conf)
# a = Conf('test.ini')
# print a.get(None,"test")


abc = 'key.store.= release.keystore'
sp = abc.split('=')

i =1
for item in sp:
  print item
  i = i+1
  print i
print len(abc)
print len(sp[0])
if len(sp[0]) == len('key.store'):
  pass
elif len(sp[0]) > len('key.store') and sp[0][len('key.store')] == ' ':
  print sp[0][len('key.store')]
                    

def changeLuaConfig(filename, key, value):
  print "changeLuaConfig%s ------key:%s ------value:%s" %(filename, key, value) 
  try:
    with open(filename) as file:
      content = file.readlines()
  except Exception, e:
    print "Exception error" + str(e)
    raise
  else:
    pass
  finally:
    pass
  newcontent = ""
  for item in content:
    keypos = string.find(item, key)
    epos = string.find(item, "=")
    if keypos != -1 and epos != -1 and keypos < epos:
      item = '%s = "%s"\n' %(key, value)
    newcontent += item
  with open(filename, "w") as the_file:
    the_file.write(newcontent)

changeLuaConfig('test.ini', 'version_name', "14")
changeLuaConfig('test.ini', 'version_code', '1.15.1.2')
changeLuaConfig('test.ini', 'sdkuser', 'useryywan')
changeLuaConfig('test.ini', 'sdkiap', 'iapyywan')





class CAnimal: 
  name = 'unname'
  def __init__(self,voice='hello'):
    self.voice = voice
  def __del__(self):
    pass
  def Say(self): 
    print self.voice 

t = CAnimal()
t.Say()
dog = CAnimal('wow')
dog.Say()
