#include <jni.h>
#include "importgl.h"
#include "ObjectRenderer.h"

extern "C"
{

	JNIEXPORT void JNICALL Java_com_example_ndkopengl_NdkGlRender_onNdkSurfaceCreated (JNIEnv* env, jobject obj)
	{
//		importGLInit();
		ObjectRenderer* render = ObjectRenderer::getInstance();
		ObjectRenderer::getInstance()->onSurfaceCreated();
	}

	JNIEXPORT void JNICALL Java_com_example_ndkopengl_NdkGlRender_onNdkSurfaceChanged(JNIEnv* env, jobject obj, jint width, jint height)
	{
		//图形最终显示到屏幕的区域的位置、长和宽
		ObjectRenderer::getInstance()->onSurfaceChanged(width, height);
	}

	JNIEXPORT void JNICALL Java_com_example_ndkopengl_NdkGlRender_onNdkDrawFrame (JNIEnv* env, jobject obj)
	{
		ObjectRenderer::getInstance()->onDrawFrame();
	}
}
