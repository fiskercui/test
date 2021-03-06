#FileName:Android.mk
#Description:makefile of NdkGl
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
#LOCAL_CFLAGS := -DANDROID_NDK
LOCAL_CFLAGS := -DANDROID_NDK \
                -DDISABLE_IMPORTGL \
                
LOCAL_MODULE    := NdkGLRenderer
LOCAL_SRC_FILES := \
	 importgl.c \
	 ObjectRenderer.cpp \
	 TestObject.cpp \
	 math/CCAffineTransform.cpp \
	 math/CCGeometry.cpp \
	 math/CCVertex.cpp \
	 math/Mat4.cpp \
	 math/MathUtil.cpp \
	 math/Quaternion.cpp \
	 math/TransformUtils.cpp \
	 math/Vec2.cpp \
	 math/Vec3.cpp \
	 math/Vec4.cpp \
	 math/Mat4.inl \
	 math/MathUtil.inl \
	 math/MathUtilNeon.inl \
	 math/Quaternion.inl \
	 math/Vec2.inl \
	 math/Vec3.inl \
	 math/Vec4.inl \
	 base/CCRef.cpp \
	 base/ccTypes.cpp \
	 base/CCGLViewProtocol.cpp \
	 base/CCGLView.cpp \
	 base/CCAutoreleasePool.cpp \
	 base/CCLog.cpp \
	 help/JniHelper.cpp \
	 help/Java_com_example_ndkopengl_Cocos2dxHelper.cpp \
	 help/NdkOpenGL.cpp \
	 platform/CCFileUtilsAndroid.cpp \
	 platform/CCFileUtils.cpp \
	 LoadShaders.cpp \
	 ShaderRenderer.cpp \
	 samples/TestShader.cpp \
	 samples/DrawCommandTest.cpp \
#	 renderer/CCGLProgram.cpp \
	 
	 
LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/. \

LOCAL_LDLIBS := -lGLESv1_CM \
                -lGLESv2 \
                -lEGL \
                -llog \
                -lz \
                -landroid
#LOCAL_EXPORT_LDLIBS := -lGLESv2 \
                       -llog \
                       -lz \
                       -landroid
                                    
include $(BUILD_SHARED_LIBRARY)
