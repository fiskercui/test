__author__ = 'weihua'
from xml.etree import ElementTree as ET
import os
import os.path
import zipfile
import re
import subprocess
import platform
# from config import ConfigParse
import inspect
bPrint = False
curDir = os.getcwdu()

def delete_file_folder(src):
    if os.path.exists(src):
        if os.path.isfile(src):
            try:
                src = src.replace('\\', '/')
                os.remove(src)
            except:
                pass

        elif os.path.isdir(src):
            for item in os.listdir(src):
                itemsrc = os.path.join(src, item)
                delete_file_folder(itemsrc)

            try:
                os.rmdir(src)
            except:
                pass


def copyFiles(sourceDir, targetDir):
    if not os.path.exists(sourceDir) and not os.path.exists(targetDir):
        printf('copy Files from %s to %s Fail:file not found' % (sourceDir, targetDir))
        return
    if os.path.isfile(sourceDir):
        copyFile(sourceDir, targetDir)
        return
    # print "sourceDir", sourceDir
    for file in os.listdir(sourceDir):
        sourceFile = os.path.join(sourceDir, file)
        targetFile = os.path.join(targetDir, file)
        if os.path.isfile(sourceFile):
            if not os.path.exists(targetDir):
                os.makedirs(targetDir)
            if not os.path.exists(targetFile) or os.path.exists(targetFile) and os.path.getsize(targetFile) != os.path.getsize(sourceFile):
                targetFileHandle = open(targetFile, 'wb')
                sourceFileHandle = open(sourceFile, 'rb')
                targetFileHandle.write(sourceFileHandle.read())
                targetFileHandle.close()
                sourceFileHandle.close()
        if os.path.isdir(sourceFile):
            copyFiles(sourceFile, targetFile)


#add by weihua.cui
__defaultABI = "armeabi"
def copyLibs(sourceDir, targetDir):
    if not os.path.exists(sourceDir) and not os.path.exists(targetDir):
        printf('copy Files from %s to %s Fail:file not found' % (sourceDir, targetDir))
        return
    if os.path.isfile(sourceDir):
        copyFile(sourceDir, targetDir)
        return
    # print "sourceDir", sourceDir
    for file in os.listdir(sourceDir):
        sourceFile = os.path.join(sourceDir, file)
        targetFile = os.path.join(targetDir, file)
        if os.path.isfile(sourceFile):
            if not os.path.exists(targetDir):
                os.makedirs(targetDir)
            if not os.path.exists(targetFile) or os.path.exists(targetFile) and os.path.getsize(targetFile) != os.path.getsize(sourceFile):
                targetFileHandle = open(targetFile, 'wb')
                sourceFileHandle = open(sourceFile, 'rb')
                targetFileHandle.write(sourceFileHandle.read())
                targetFileHandle.close()
                sourceFileHandle.close()
        basename = os.path.basename(sourceFile)
        if os.path.isdir(sourceFile) and basename == __defaultABI:
            print("************************" + basename)
            copyFiles(sourceFile, targetFile)

def copyFile(sourceFile, targetFile):
    sourceFile = getFullPath(sourceFile)
    targetFile = getFullPath(targetFile)
    if not os.path.exists(sourceFile):
        return
    if not os.path.exists(targetFile) or os.path.exists(targetFile) and os.path.getsize(targetFile) != os.path.getsize(sourceFile):
        targetDir = os.path.dirname(targetFile)
        if not os.path.exists(targetDir):
            os.makedirs(targetDir)
        targetFileHandle = open(targetFile, 'wb')
        sourceFileHandle = open(sourceFile, 'rb')
        targetFileHandle.write(sourceFileHandle.read())
        targetFileHandle.close()
        sourceFileHandle.close()


def copyApkToZip(filename):
    dotIndex = filename.find('.')
    newfilename = filename
    if dotIndex >= 0 and os.path.exists(filename):
        name = filename[:dotIndex]
        ext = filename[dotIndex:]
        newext = '.zip'
        newfilename = name + newext
        if not os.path.exists(newfilename) or os.path.exists(newfilename) and os.path.getsize(newfilename) != os.path.getsize(filename):
            targetFileHandle = open(newfilename, 'wb')
            sourceFileHandle = open(filename, 'rb')
            targetFileHandle.write(sourceFileHandle.read())
            targetFileHandle.close()
            sourceFileHandle.close()
            printf('copy success')


def decompression(filename, unziptodir):
    delete_file_folder(unziptodir)
    if not os.path.exists(unziptodir):
        os.mkdir(unziptodir, 511)
    f = zipfile.ZipFile(filename)
    f.extractall(unziptodir)
    printf('decompression success!')
    f.close()
    delete_file_folder(filename)


def getCurDir():
    global curDir
    retPath = curDir
    if platform.system == 'Windows':
        retPath = retPath.decode('gbk')
    return retPath
    caller_file = inspect.stack()[0][1]
    retPath = os.path.abspath(os.path.dirname(caller_file))
    if platform.system == 'Windows':
        retPath = retPath.decode('gbk')
    return retPath


def getFullPath(filename):
    if os.path.isabs(filename):
        return filename
    dirname = getCurDir()
    filename = os.path.join(dirname, filename)
    filename = filename.replace('\\', '/')
    filename = re.sub('/+', '/', filename)
    return filename


def getToolPath(filename):
    toolPath = ''
    if platform.system() == 'Darwin':
        toolPath = getFullPath('../tool/mac/' + filename)
    else:
        toolPath = getFullPath('../tool/win/' + filename)
    return toolPath


def modifyFileContent(source, fileType, oldContent, newContent):
    if os.path.isdir(source):
        for file in os.listdir(source):
            sourceFile = os.path.join(source, file)
            modifyFileContent(sourceFile, fileType, oldContent, newContent)

    elif os.path.isfile(source) and os.path.splitext(source)[1] == fileType:
        f = open(source, 'r+')
        data = str(f.read())
        f.close()
        bRet = False
        idx = data.find(oldContent)
        while idx != -1:
            data = data[:idx] + newContent + data[idx + len(oldContent):]
            idx = data.find(oldContent, idx + len(oldContent))
            bRet = True

        if bRet:
            fhandle = open(source, 'w')
            fhandle.write(data)
            fhandle.close()
            printf('modify file:%s' % source)
        else:
            printf('source:%s not found content:%s' %(source, oldContent))
            # error_operate.error(108)


def execFormatCmd(cmd):
    cmd = cmd.replace('\\', '/')
    cmd = re.sub('/+', '/', cmd)
    ret = 0
    if platform.system() == 'Windows':
        st = subprocess.STARTUPINFO
        st.dwFlags = subprocess.STARTF_USESHOWWINDOW
        st.wShowWindow = subprocess.SW_HIDE
        cmd = str(cmd).encode('gbk')
    s = subprocess.Popen(cmd, shell=True)
    ret = s.wait()
    if ret:
        cmd = 'ERROR:' + cmd + ' ===>>> exec Fail <<<=== '
    else:
        cmd += ' ===>>> exec success <<<=== '
    printf(cmd)
    return ret


def getApkVersion(apkFile):
    """get the version about apk"""
    cmd = getToolPath('aapt') + ' d badging ' + apkFile
    cmd = cmd.replace('\\', '/')
    cmd = re.sub('/+', '/', cmd)
    cmd = str(cmd).encode('utf-8')
    ret = 0
    if platform.system() == 'Windows':
        st = subprocess.STARTUPINFO
        st.dwFlags = subprocess.STARTF_USESHOWWINDOW
        st.wShowWindow = subprocess.SW_HIDE
    s = subprocess.Popen(cmd, stdout=subprocess.PIPE, shell=True)
    info = s.communicate()[0]
    nPos = info.find('versionName')
    nEnd = info.find("'", nPos + 13)
    versionName = info[nPos + 13:nEnd]
    return versionName

# def backupApk(source, game, versionName):
#     print "backupApk function is not complete"
def backupApk(source, game, versionName):
    # gameName = game['gameName']
    # outputDir = ConfigParse.shareInstance().getOutputDir()
    # if outputDir == '':
    #     outputDir = '../output/'
    # outputDir += '/' + game['gameName'] + '/' + versionName + '/common'
    # outputDir = getFullPath(outputDir)
    # backupName = '%s/common.apk' % outputDir
    # copyFile(source, backupName)
    return


def getJavaBinDir():
    if platform.system() == 'Darwin':
        javaBinDir = '/System/Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Commands/'
    else:
        bUseLocalJre = False
        if bUseLocalJre:
            javaBinDir = os.path.join(getCurDir(), '../tool/win/jre/bin/')
        else:
            javaBinDir = ''
    return javaBinDir


def getJava():
    return getJavaBinDir() + 'java'


def printf(str):
    """
    print info in debug mode
    or
    write info into pythonLog.txt in release mode
    """
    global bPrint
    if bPrint:
        print str


def setPrintEnable(bEnable):
    global bPrint
    bPrint = bEnable
