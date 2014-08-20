#FileName:Android.mk
#Description:makefile of NdkGl
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := NdkGLRenderer
LOCAL_SRC_FILES := NdkOpenGL.c
 
LOCAL_LDLIBS := -lGLESv1_CM

include $(BUILD_SHARED_LIBRARY)
