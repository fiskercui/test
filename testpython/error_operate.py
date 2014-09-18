#Embedded file name: /Projects/GitLab/anysdk_package/Env/Script/error_operate.py
import file_operate
import core

def error(code):
    file_operate.printf('%s Failed at code %s!' % (idChannel, -100 - code))
