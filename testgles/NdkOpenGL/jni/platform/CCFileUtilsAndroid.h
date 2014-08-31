
#ifndef __CC_FILEUTILS_ANDROID_H__
#define __CC_FILEUTILS_ANDROID_H__

#include "base/CCPlatformConfig.h"

#include <string>
#include <vector>
#include "jni.h"
#include "android/asset_manager.h"
#include "CCFileUtils.h"



NS_CC_BEGIN

/**
 * @addtogroup platform
 * @{
 */

//! @brief  Helper class to handle file operations
class CC_DLL FileUtilsAndroid : public FileUtils
{
    friend class FileUtils;
    FileUtilsAndroid();
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~FileUtilsAndroid();

    static void setassetmanager(AAssetManager* a);

    /* override funtions */
    bool init();
    /**
     *  Gets string from a file.
     */
    virtual std::string getStringFromFile(const std::string& filename) override;

    virtual std::string getWritablePath() const;
    virtual bool isAbsolutePath(const std::string& strPath) const;
private:
    virtual bool isFileExistInternal(const std::string& strFilePath) const;
    std::string getData(const std::string& filename, bool forString);

    static AAssetManager* assetmanager;
};

// end of platform group
/// @}

NS_CC_END
#endif
