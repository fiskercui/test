//#include <GLES/gl.h>
//EGL/egl.h exists since android 2.3
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include "importgl.h"
#include "base/ccMacros.h"
#include "math/CCGeometry.h"
#include "math/Mat4.h"
#include "base/CCGL.h"
#include "renderer/CCGLProgram.h"

#include "TestObject.h"
#include "ObjectRenderer.h"

unsigned int vbo[2];
float positions[12] = {100,-100,0, 100,100,0, -100,-100,0, -100,100,0};
short indices  [4]  = {0,1,2,3};
TestObject::TestObject()
{

}


TestObject::~TestObject()
{

}


void TestObject::init()
{
    static float grey;
    grey += 0.01f;
    if (grey > 1.0f) {
        grey = 0.0f;
    }
//    glClearColor(grey, grey, grey, 1.0f);
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	//生成两个缓存区对象
	glGenBuffers (2, vbo);
	//绑定第一个缓存对象
	glBindBuffer (GL_ARRAY_BUFFER, vbo[0]);
	//创建和初始化第一个缓存区对象的数据
	glBufferData (GL_ARRAY_BUFFER, 4*12, positions, GL_STATIC_DRAW);
	//绑定第二个缓存对象
	glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
	//创建和初始化第二个缓存区对象的数据
	glBufferData (GL_ELEMENT_ARRAY_BUFFER, 2*4, indices, GL_STATIC_DRAW);
}

void TestObject::draw()
{
//	glClearColor (0,0,1,1);
//	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	ObjectRenderer::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
//	ObjectRenderer::getInstance()->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
//	glBindBuffer    (GL_ARRAY_BUFFER, vbo[0]);
////	glVertexPointer (3, GL_FLOAT, 0, 0);
//	 glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	 glBindBuffer    (GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
//	 glDrawElements  (GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);
//	ObjectRenderer::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	//启用顶点设置功能，之后必须要关闭功能
	glEnableClientState (GL_VERTEX_ARRAY);
//	清屏
	glClearColor (1,0,0,1);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	glBindBuffer    (GL_ARRAY_BUFFER, vbo[0]);
	//定义顶点坐标
	glVertexPointer (3, GL_FLOAT, 0, 0);
	glBindBuffer    (GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
	//按照参数给定的值绘制图形
	glDrawElements  (GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);
//	关闭顶点设置功能
	glDisableClientState(GL_VERTEX_ARRAY);
}
