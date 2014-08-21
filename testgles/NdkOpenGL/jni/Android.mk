#FileName:Android.mk
#Description:makefile of NdkGl
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_CFLAGS := -DANDROID_NDK \
                -DDISABLE_IMPORTGL
                
LOCAL_MODULE    := NdkGLRenderer
LOCAL_SRC_FILES := \
    importgl.c \
	 NdkOpenGL.cpp \
	 ObjectRenderer.cpp \
	 TestObject.cpp \
LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/. \
#LOCAL_LDLIBS := -lGLESv1_CM

LOCAL_LDLIBS := -lGLESv1_CM \
				-ldl \
                -llog \
                -lz \
                -landroid
                
include $(BUILD_SHARED_LIBRARY)
