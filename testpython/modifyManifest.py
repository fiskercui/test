#Embedded file name: /Projects/package/Env/Script/modifyManifest.py
import sys, string, os
from xml.etree import ElementTree as ET
import re
import file_operate
androidNS = 'http://schemas.android.com/apk/res/android'

def doModify(manifestFile, sourceFile, root):
    """
        modify AndroidManifest.xml by ForManifest.xml
    """
    if not os.path.exists(manifestFile):
        return False
    if not os.path.exists(sourceFile):
        return False
    bRet = False
    sourceTree = ET.parse(sourceFile)
    sourceRoot = sourceTree.getroot()
    f = open(manifestFile)
    targetContent = f.read()
    f.close()
    appCfgNode = sourceRoot.find('applicationCfg')
    if appCfgNode is not None and len(appCfgNode) > 0:
        appKeyWord = appCfgNode.get('keyword')
        if appKeyWord != None and len(appKeyWord) > 0:
            keyIndex = targetContent.find(appKeyWord)
            if -1 == keyIndex:
                bRet = True
                for node in list(appCfgNode):
                    root.find('application').append(node)

    perCfgNode = sourceRoot.find('permissionCfg')
    if perCfgNode is not None and len(perCfgNode) > 0:
        for oneNode in list(perCfgNode):
            key = '{' + androidNS + '}name'
            perAttr = oneNode.get(key)
            if perAttr != None and len(perAttr) > 0:
                attrIndex = targetContent.find(perAttr)
                if -1 == attrIndex:
                    bRet = True
                    root.append(oneNode)

    return bRet

def modifyApplicationActivity(key, value, androidManiFest = 'AndroidManifest.xml'):
    if not os.path.exists(androidManiFest):
        return False
    ET.register_namespace('android', androidNS)
    targetTree = ET.parse(androidManiFest)
    targetRoot = targetTree.getroot()
    applicationNode = targetRoot.find('application')
    if applicationNode is None:
        error_operate.error(121)
        return 1
    activityNodes = applicationNode.findall('activity')
    if activityNodes is not None and len(activityNodes) > 0:
        for oneNode in list(activityNodes):
            file_operate.printf("hello world")
            nsKey = '{' + androidNS + '}configChanges'
            file_operate.printf(nsKey)
            ET.dump(oneNode)
            perAttr = oneNode.get(nsKey)
            if perAttr != None and len(perAttr) > 0:
                file_operate.printf("hehehe")
                oneNode.attrib[nsKey] = value
    targetTree.write(androidManiFest, 'UTF-8')

def renameAppName(appName, androidManiFest = 'AndroidManifest.xml'):
    if not os.path.exists(androidManiFest):
        return False
    ET.register_namespace('android', androidNS)
    targetTree = ET.parse(androidManiFest)
    targetRoot = targetTree.getroot()
    key = '{' + androidNS + '}label'
    file_operate.printf(key)
    applicationNode = targetRoot.find('application')
    if applicationNode is None:
        error_operate.error(121)
        return 1
    ET.dump(applicationNode)
    applicationNode.attrib[key] = appName
    print('rename appname----- :'+appName)
    targetTree.write(androidManiFest, 'UTF-8')

def modify(manifestFile, sourceCfgFile, pluginName):
    manifestFile = file_operate.getFullPath(manifestFile)
    sourceXml = sourceCfgFile
    sourceXml = file_operate.getFullPath(sourceXml)
    file_operate.printf("modify source xml:%s manifestFile:%s" %(sourceXml, manifestFile))
    if not os.path.exists(sourceXml):
        ForManifestDir = os.path.dirname(sourceXml)
        screenOrientation = getStartActivityOrientation(manifestFile)
        file_operate("screenOrientation:%s"%(screenOrientation,))
        if screenOrientation == 'portrait':
            sourceXml = ForManifestDir + '/ForManifestPortrait.xml'
        else:
            sourceXml = ForManifestDir + '/ForManifestLandscape.xml'
    if not os.path.exists(sourceXml):
        return
    ET.register_namespace('android', androidNS)
    targetTree = ET.parse(manifestFile)
    targetRoot = targetTree.getroot()
    haveChanged = doModify(manifestFile, sourceXml, targetRoot)
    if haveChanged:
        file_operate.printf('Modify AndroidManifest.xml for plugin ' + pluginName)
        targetTree.write(manifestFile, 'UTF-8')

def modify_attrbute(manifestFile, sourceCfgFIle, pluginName):
    return ""

def getStartActivityOrientation(manifestFile):
    """
        @return original activity's name.
    """
    ET.register_namespace('android', androidNS)
    key = '{' + androidNS + '}name'
    targetTree = ET.parse(manifestFile)
    targetRoot = targetTree.getroot()
    applicationNode = targetRoot.find('targetRoot')
    if applicationNode is None:
        return
    if applicationNode is not None:
        activityLsNode = applicationNode.findall('activity')
    if activityLsNode is None:
        return
    screenOrientation = ''
    for activityNode in activityLsNode:
        bMainActivity = False
        intentLsNode = activityNode.findall('intent-filter')
        if intentLsNode is None:
            return
        for intentNode in intentLsNode:
            bFindAction = False
            bFindCategory = False
            actionLsNode = intentNode.findall('action')
            for actionNode in actionLsNode:
                if actionNode.attrib[key] == 'android.intent.action.MAIN':
                    bFindAction = True
                    break

            if not bFindAction:
                continue
            categoryLsNode = intentNode.findall('category')
            for categoryNode in categoryLsNode:
                if categoryNode.attrib[key] == 'android.intent.category.LAUNCHER':
                    bFindCategory = True
                    break

            if bFindAction and bFindCategory:
                bMainActivity = True
                break

        if bMainActivity:
            if activityNode.attrib.get('android:screenOrientation') is not None:
                screenOrientation = activityNode.attrib['android:screenOrientation']
            else:
                screenOrientation = 'portrait'
            break

    return screenOrientation
