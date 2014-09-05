
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ShaderRenderer.h"

#include "samples/TestShader.h"
#include "samples/DrawCommandTest.h"


//ShaderObject* shaderobject = new ShaderObject();
DrawCommandTest* shaderobject = new DrawCommandTest();

ShaderRenderer* ShaderRenderer::s_render = nullptr;

ShaderRenderer::ShaderRenderer()
{
	_openGLView = GLView::create("glview");
}
ShaderRenderer::~ShaderRenderer()
{

}

void ShaderRenderer::onDrawFrame()
{
//    renderFrame();
    shaderobject->draw();
}

void ShaderRenderer::onSurfaceCreated()
{
}

void ShaderRenderer::onSurfaceChanged(int width, int height)
{
//    setupGraphics(width, height);
	shaderobject->init(width, height);
}


ShaderRenderer* ShaderRenderer::getInstance()
{
	if (s_render == NULL)
	{
		s_render = new ShaderRenderer();
	}
	return s_render;
}
