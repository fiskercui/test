#include <GLES/gl.h>
#include <stdio.h>
//EGL/egl.h exists since android 2.3
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
//#include "importgl.h"
#include "base/ccMacros.h"
#include "math/CCGeometry.h"
#include "math/Mat4.h"
#include "base/CCGL.h"

#include "ObjectRenderer.h"
#include "TestObject.h"
#include "samples/TestShader.h"

void xgluPerspective( float fovy, float aspect, float near_clip, float far_clip )
{
    const double PI = 3.1415926;
    double TWOPI_OVER_360 = 2.0 * PI / 360.0;
    float half_height = near_clip * (float)tan( fovy * 0.5 * TWOPI_OVER_360 );
    float half_width = half_height * aspect;

#ifdef WIN32
    glFrustum( -half_width, half_width, -half_height, half_height, near_clip, far_clip );
#elif defined(CK_ANDROID)
    glFrustumf( -half_width, half_width, -half_height, half_height, near_clip, far_clip );
#endif
}


ObjectRenderer* ObjectRenderer::s_render = nullptr;

//TestObject* object = new TestObject();
ShaderObject* object = new ShaderObject();
ObjectRenderer::ObjectRenderer()
{

}

ObjectRenderer::~ObjectRenderer()
{
    if (_openGLView)
    {
        _openGLView->end();
        _openGLView = nullptr;
    }

}

void ObjectRenderer::initMatrixStack()
{
    while (!_modelViewMatrixStack.empty())
    {
        _modelViewMatrixStack.pop();
    }

    while (!_projectionMatrixStack.empty())
    {
        _projectionMatrixStack.pop();
    }

    while (!_textureMatrixStack.empty())
    {
        _textureMatrixStack.pop();
    }

    _modelViewMatrixStack.push(Mat4::IDENTITY);
    _projectionMatrixStack.push(Mat4::IDENTITY);
    _textureMatrixStack.push(Mat4::IDENTITY);
}

void ObjectRenderer::resetMatrixStack()
{
    initMatrixStack();
}

void ObjectRenderer::popMatrix(MATRIX_STACK_TYPE type)
{
    if(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW == type)
    {
        _modelViewMatrixStack.pop();
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION == type)
    {
        _projectionMatrixStack.pop();
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE == type)
    {
        _textureMatrixStack.pop();
    }
    else
    {
        CCASSERT(false, "unknow matrix stack type");
    }
}

void ObjectRenderer::loadIdentityMatrix(MATRIX_STACK_TYPE type)
{
    if(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW == type)
    {
        _modelViewMatrixStack.top() = Mat4::IDENTITY;
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION == type)
    {
        _projectionMatrixStack.top() = Mat4::IDENTITY;
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE == type)
    {
        _textureMatrixStack.top() = Mat4::IDENTITY;
    }
    else
    {
        CCASSERT(false, "unknow matrix stack type");
    }
}

void ObjectRenderer::loadMatrix(MATRIX_STACK_TYPE type, const Mat4& mat)
{
    if(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW == type)
    {
        _modelViewMatrixStack.top() = mat;
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION == type)
    {
        _projectionMatrixStack.top() = mat;
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE == type)
    {
        _textureMatrixStack.top() = mat;
    }
    else
    {
        CCASSERT(false, "unknow matrix stack type");
    }
}

void ObjectRenderer::multiplyMatrix(MATRIX_STACK_TYPE type, const Mat4& mat)
{
    if(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW == type)
    {
        _modelViewMatrixStack.top() *= mat;
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION == type)
    {
        _projectionMatrixStack.top() *= mat;
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE == type)
    {
        _textureMatrixStack.top() *= mat;
    }
    else
    {
        CCASSERT(false, "unknow matrix stack type");
    }
}

void ObjectRenderer::pushMatrix(MATRIX_STACK_TYPE type)
{
    if(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW == type)
    {
        _modelViewMatrixStack.push(_modelViewMatrixStack.top());
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION == type)
    {
        _projectionMatrixStack.push(_projectionMatrixStack.top());
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE == type)
    {
        _textureMatrixStack.push(_textureMatrixStack.top());
    }
    else
    {
        CCASSERT(false, "unknow matrix stack type");
    }
}

Mat4 ObjectRenderer::getMatrix(MATRIX_STACK_TYPE type)
{
    Mat4 result;
    if(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW == type)
    {
        result = _modelViewMatrixStack.top();
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION == type)
    {
        result = _projectionMatrixStack.top();
    }
    else if(MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE == type)
    {
        result = _textureMatrixStack.top();
    }
    else
    {
        CCASSERT(false, "unknow matrix stack type, will return modelview matrix instead");
        result =  _modelViewMatrixStack.top();
    }
//    float diffResult(0);
//    for (int index = 0; index <16; ++index)
//    {
//        diffResult += abs(result2.mat[index] - result.mat[index]);
//    }
//    if(diffResult > 1e-30)
//    {
//        CCASSERT(false, "Error in director matrix stack");
//    }
    return result;
}

void ObjectRenderer::setupProjection()
{
	glViewport (0,0, 960, 640);
    Size size(960,640);
    float zeye = 640/1.1566f;

    Mat4 matrixPerspective, matrixLookup;

    loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);

#if CC_TARGET_PLATFORM == CC_PLATFORM_WP8
    //if needed, we need to add a rotation for Landscape orientations on Windows Phone 8 since it is always in Portrait Mode
    GLView* view = getOpenGLView();
    if(getOpenGLView() != nullptr)
    {
        multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, getOpenGLView()->getOrientationMatrix());
    }
#endif
    // issue #1334
    Mat4::createPerspective(60, (GLfloat)size.width/size.height, 1, zeye+size.height/2, &matrixPerspective);

    multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, matrixPerspective);

    Vec3 eye(size.width/2, size.height/2, zeye), center(size.width/2, size.height/2, 0.0f), up(0.0f, 1.0f, 0.0f);
    Mat4::createLookAt(eye, center, up, &matrixLookup);
    multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, matrixLookup);

    loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void ObjectRenderer::onDrawFrame()
{
//	object->draw();
}

void ObjectRenderer::onSurfaceCreated()
{
    initMatrixStack();
//	object->init();
}

void ObjectRenderer::onSurfaceChanged(int width, int height)
{
	glViewport (0,0,width,height);
	//指定矩阵
	glMatrixMode   (GL_PROJECTION);
	//将当前的矩阵设置为glMatrixMode指定的矩阵
	glLoadIdentity ();

    Size size(960,640);
    float zeye = 640/1.1566f;
    xgluPerspective(60, (GLfloat)size.width/size.height, 1, zeye+size.height/2);
//    xgluLookAt(size.width/2, size.height/2, zeye, size.width/2, size.height/2, 0.0f, 0.0f, 1.0f, 0.0f);
//    Vec3 eye(size.width/2, size.height/2, zeye), center(size.width/2, size.height/2, 0.0f), up(0.0f, 1.0f, 0.0f);
//    glLookAt()
//	glOrthof(-2, 2, -2, 2, -2, 2);

	CCLOGINFO("width:%d, height:%d", width, height);
//	setupProjection();
}

ObjectRenderer* ObjectRenderer::getInstance()
{
	if (s_render == NULL)
	{
		s_render = new ObjectRenderer();
	}
	return s_render;
}
