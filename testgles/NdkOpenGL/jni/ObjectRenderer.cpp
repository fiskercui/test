//#include <GLES/gl.h>
//EGL/egl.h exists since android 2.3
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include "importgl.h"

#include "ObjectRenderer.h"
#include "TestObject.h"

ObjectRenderer* ObjectRenderer::s_render = nullptr;

TestObject* object = new TestObject();
ObjectRenderer::ObjectRenderer()
{

}

ObjectRenderer::~ObjectRenderer()
{

}

void ObjectRenderer::onDrawFrame()
{
	object->draw();
}

void ObjectRenderer::onSurfaceCreated()
{

	object->init();
}

void ObjectRenderer::onSurfaceChanged(int width, int height)
{
	glViewport (0,0,width,height);
	//指定矩阵
	glMatrixMode   (GL_PROJECTION);
	//将当前的矩阵设置为glMatrixMode指定的矩阵
	glLoadIdentity ();
	glOrthof(-2, 2, -2, 2, -2, 2);
}

ObjectRenderer* ObjectRenderer::getInstance()
{
	if (s_render == NULL)
	{
		s_render = new ObjectRenderer();
	}
	return s_render;
}
