#include "base/ccMacros.h"
#include "base/CCPlatformConfig.h"

#include "CCFileUtilsAndroid.h"
//#include "platform/CCCommon.h"
#include "help/Java_com_example_ndkopengl_Cocos2dxHelper.h"
#include "android/asset_manager.h"
#include "android/asset_manager_jni.h"

#include <stdlib.h>
#include <string>

#ifndef LOG_TAG
	#define  LOG_TAG    "CCFileUtilsAndroid.cpp"
#endif

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace std;

NS_CC_BEGIN

AAssetManager* FileUtilsAndroid::assetmanager = nullptr;

void FileUtilsAndroid::setassetmanager(AAssetManager* a) {
    if (nullptr == a) {
        LOGD("setassetmanager : received unexpected nullptr parameter");
        return;
    }

    cocos2d::FileUtilsAndroid::assetmanager = a;
}

FileUtils* FileUtils::getInstance()
{
    if (s_sharedFileUtils == nullptr)
    {
        s_sharedFileUtils = new FileUtilsAndroid();
        if(!s_sharedFileUtils->init())
        {
          delete s_sharedFileUtils;
          s_sharedFileUtils = nullptr;
          CCLOG("ERROR: Could not init CCFileUtilsAndroid");
        }
    }
    return s_sharedFileUtils;
}

FileUtilsAndroid::FileUtilsAndroid()
{
}

FileUtilsAndroid::~FileUtilsAndroid()
{
}

bool FileUtilsAndroid::init()
{
    _defaultResRootPath = "assets/";
    return FileUtils::init();
}

bool FileUtilsAndroid::isFileExistInternal(const std::string& strFilePath) const
{
    if (strFilePath.empty())
    {
        return false;
    }

    bool bFound = false;
    
    // Check whether file exists in apk.
    if (strFilePath[0] != '/')
    {
        const char* s = strFilePath.c_str();

        // Found "assets/" at the beginning of the path and we don't want it
        if (strFilePath.find(_defaultResRootPath) == 0) s += strlen("assets/");

        if (FileUtilsAndroid::assetmanager) {
            AAsset* aa = AAssetManager_open(FileUtilsAndroid::assetmanager, s, AASSET_MODE_UNKNOWN);
            if (aa)
            {
                bFound = true;
                AAsset_close(aa);
            } else {
                // CCLOG("[AssetManager] ... in APK %s, found = false!", strFilePath.c_str());
            }
        }
    }
    else
    {
        FILE *fp = fopen(strFilePath.c_str(), "r");
        if(fp)
        {
            bFound = true;
            fclose(fp);
        }
    }
    return bFound;
}

bool FileUtilsAndroid::isAbsolutePath(const std::string& strPath) const
{
    // On Android, there are two situations for full path.
    // 1) Files in APK, e.g. assets/path/path/file.png
    // 2) Files not in APK, e.g. /data/data/org.cocos2dx.hellocpp/cache/path/path/file.png, or /sdcard/path/path/file.png.
    // So these two situations need to be checked on Android.
    if (strPath[0] == '/' || strPath.find(_defaultResRootPath) == 0)
    {
        return true;
    }
    return false;
}

std::string FileUtilsAndroid::getStringFromFile(const std::string& filename)
{
    return getData(filename, true);
}



std::string FileUtilsAndroid::getData(const std::string& filename, bool forString)
{
    if (filename.empty())
    {
        return "";
    }

    unsigned char* data = nullptr;
    ssize_t size = 0;
    string fullPath = fullPathForFilename(filename);

    if (fullPath[0] != '/')
    {
        string relativePath = string();

        size_t position = fullPath.find("assets/");
        if (0 == position) {
            // "assets/" is at the beginning of the path and we don't want it
            relativePath += fullPath.substr(strlen("assets/"));
        } else {
            relativePath += fullPath;
        }
        LOGD("relative path = %s", relativePath.c_str());

        if (nullptr == FileUtilsAndroid::assetmanager) {
            LOGD("... FileUtilsAndroid::assetmanager is nullptr");
            return "";
        }

        // read asset data
        AAsset* asset =
            AAssetManager_open(FileUtilsAndroid::assetmanager,
                               relativePath.c_str(),
                               AASSET_MODE_UNKNOWN);
        if (nullptr == asset) {
            LOGD("asset is nullptr");
            return "";
        }

        off_t fileSize = AAsset_getLength(asset);

        if (forString)
        {
            data = (unsigned char*) malloc(fileSize + 1);
            data[fileSize] = '\0';
        }
        else
        {
            data = (unsigned char*) malloc(fileSize);
        }

        int bytesread = AAsset_read(asset, (void*)data, fileSize);
        size = bytesread;

        AAsset_close(asset);
    }
    else
    {
        do
        {
            // read rrom other path than user set it
            //CCLOG("GETTING FILE ABSOLUTE DATA: %s", filename);
            const char* mode = nullptr;
            if (forString)
                mode = "rt";
            else
                mode = "rb";

            FILE *fp = fopen(fullPath.c_str(), mode);
            CC_BREAK_IF(!fp);

            long fileSize;
            fseek(fp,0,SEEK_END);
            fileSize = ftell(fp);
            fseek(fp,0,SEEK_SET);
            if (forString)
            {
                data = (unsigned char*) malloc(fileSize + 1);
                data[fileSize] = '\0';
            }
            else
            {
                data = (unsigned char*) malloc(fileSize);
            }
            fileSize = fread(data,sizeof(unsigned char), fileSize,fp);
            fclose(fp);

            size = fileSize;
        } while (0);
    }

    std::string ret;
    if (data == nullptr || size == 0)
    {
        std::string msg = "Get data from file(";
        msg.append(filename).append(") failed!");
        CCLOG("%s", msg.c_str());
        return "";
    }
    else
    {
//        ret.fastSet(data, size);
    	std::string ret((char*)data, (int)size);
    	CCLOG("file data:%s", data);
    	return ret;
    }

//    return ret;
}

string FileUtilsAndroid::getWritablePath() const
{
    // Fix for Nexus 10 (Android 4.2 multi-user environment)
    // the path is retrieved through Java Context.getCacheDir() method
    string dir("");
    string tmp = getFileDirectoryJNI();

    if (tmp.length() > 0)
    {
        dir.append(tmp).append("/");

        return dir;
    }
    else
    {
        return "";
    }
}

NS_CC_END
