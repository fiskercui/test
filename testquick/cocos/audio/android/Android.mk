LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := cocosdenshion_static

LOCAL_MODULE_FILENAME := libcocosdenshion

LOCAL_SRC_FILES := \
$(LOCAL_PATH)/cddSimpleAudioEngine.cpp \
$(LOCAL_PATH)/ccdandroidUtils.cpp \
$(LOCAL_PATH)/jni/cddandroidAndroidJavaEngine.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../include \
				    $(QUICK_V3_LIB)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include \
                    $(LOCAL_PATH)/../.. \
                    $(LOCAL_PATH)/../../platform/android \
                    $(LOCAL_PATH)/../../../external \
				    $(QUICK_V3_LIB)

include $(BUILD_STATIC_LIBRARY)
