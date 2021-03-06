//#include <GLES/gl.h>
//EGL/egl.h exists since android 2.3
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <stdlib.h>
#include <stdio.h>

#include "math/CCGeometry.h"
#include "math/Mat4.h"

#include "base/ccMacros.h"
#include "base/CCLog.h"
#include "base/CCGL.h"
#include "base/CCPlatformMacros.h"

#include "DrawCommandTest.h"
//#include "ObjectRenderer.h
#include "LoadShaders.h"

USING_NS_CC;

static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}

static void checkGlError(const char* op) {
    for (GLint error = glGetError(); error; error
            = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

//MyPerspective与glFrustum的相互转换
//void MyPerspective( GLdouble fov, GLdouble aspectRatio, GLdouble zNear, GLdouble zFar )
//{
//    // 使用glu库函数，需要添加glu.h头文件
//    //gluPerspective( fov, aspectRatio, zNear, zFar );
//
//
//    // 使用OpenGL函数，但是需要添加math.h头文件
//    GLdouble rFov = fov * 3.14159265 / 180.0;
//    glFrustum( -zNear * tan( rFov / 2.0 ) * aspectRatio,
//               zNear * tan( rFov / 2.0 ) * aspectRatio,
//               -zNear * tan( rFov / 2.0 ),
//               zNear * tan( rFov / 2.0 ),
//               zNear, zFar );
//}


DrawCommandTest::DrawCommandTest():m_index(0)
{

}

DrawCommandTest::~DrawCommandTest()
{

}

void DrawCommandTest::init(int width, int height)
{
    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);
//
    aspect = width*1.0f/height;
    LOGI("setupGraphics(%d, %d)", width*2, height*2);
//
//	static const ShaderInfo shader_info[] = {
//		{GL_VERTEX_SHADER, "shaders/primitive_restart.vs.glsl"},
//		{GL_FRAGMENT_SHADER, "shaders/primitive_restart.fs.glsl"},
//		{GL_NONE, NULL}
//	};
	ShaderInfo  shaders[] = {
		{ GL_VERTEX_SHADER, "shaders/primitive_restart.vs.glsl" },
		{ GL_FRAGMENT_SHADER, "shaders/primitive_restart.fs.glsl" },
		{ GL_NONE, NULL }
	};
	render_prog = LoadShaders(shaders);
	glUseProgram(render_prog);
	render_model_matrix_loc = glGetUniformLocation(render_prog, "model_matrix");
	checkGlError("glGetUniformLocation");
	LOGI("render_model_matrix_loc = %d",render_model_matrix_loc);
//	LOGI("", );
	render_projection_matrix_loc = glGetUniformLocation(render_prog, "projection_matrix");
	checkGlError("glGetUniformLocation");
	LOGI("render_projection_matrix_loc = %d",render_projection_matrix_loc);

	static const GLfloat vertex_positions[] = {
		 -1.0f, -1.0f, 0.0f, 1.0f,
		  1.0f, -1.0f, 0.0f, 1.0f,
		 -1.0f,  1.0f, 0.0f, 1.0f,
		 -1.0f, -1.0f, 0.0f, 1.0f,
	};
	// Color for each vertex
	static const GLfloat vertex_colors[] = {
		 1.0f, 1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 0.0f, 1.0f,
		 1.0f, 0.0f, 1.0f, 1.0f,
		 0.0f, 1.0f, 1.0f, 1.0f
	};
	// Three indices (we’re going to draw one triangle at a time static const GLushort vertex_indices[] =
	static const GLushort vertex_indices[] = {0, 1, 2 };
	// Set up the element array buffer
	glGenBuffers(1, ebo);
	checkGlError("glGenBuffers");
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
	checkGlError("glBindBuffer");
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(vertex_indices), vertex_indices, GL_STATIC_DRAW);
	checkGlError("glBufferData");
	// Set up the vertex attributes
	glGenVertexArrays(1, vao);
	checkGlError("glGenVertexArrays");
	glBindVertexArray(vao[0]);
	checkGlError("glBindVertexArray");
	glGenBuffers(1, vbo);
	checkGlError("glGenBuffers");
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	checkGlError("glBindBuffer");
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertex_positions) + sizeof(vertex_colors), NULL, GL_STATIC_DRAW);
	checkGlError("glBufferData");
	glBufferSubData(GL_ARRAY_BUFFER, 0,sizeof(vertex_positions), vertex_positions);
	checkGlError("glBufferSubData");
	glBufferSubData(GL_ARRAY_BUFFER,sizeof(vertex_positions), sizeof(vertex_colors), vertex_colors);
	checkGlError("glBufferSubData");
	glViewport(0,0,width, height);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)sizeof(vertex_positions));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

#define MAX_LEN 1024
static char s_temp[MAX_LEN];
std::string FloatToChar10(float f)
{
    snprintf(s_temp, MAX_LEN, "%f", f);
    return (std::string) s_temp;
}

std::string IntToChar10(int num)
{
	snprintf(s_temp, MAX_LEN, "%d", num);
	return (std::string) s_temp;
}

std::string FloatArrayToString(float f[], int size)
{
	printf("convertFloatArrayToString\n");
	std::string sTemp;
	for (int i = 0; i < size; ++i)
	{
		sTemp += "[" + IntToChar10(i) + "]:" + FloatToChar10(f[i]) + ",";
	}
	return sTemp;
}


void DrawCommandTest::draw()
{
//	LOGI("DrawCommandTest Draw:%d",m_index);
	Mat4 projection_matrix;
    float matrixValue[16];
//
	Mat4::createPerspective(45, aspect, 1.0f, 500.f, &projection_matrix);
    memcpy(matrixValue, projection_matrix.m, sizeof(float)*16);
    if (m_index++ < 10 )
    {
		LOGI("render_projection_matrix_loc\n");
    	LOGI("%s\n", FloatArrayToString(matrixValue, 16).c_str());
    }
    glUniformMatrix4fv(render_projection_matrix_loc, 1, GL_FALSE, matrixValue);
    checkGlError("render_projection_matrix_loc glUniformMatrix4fv");

    glBindVertexArray(vao[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);

	Mat4 model_matrix;
	model_matrix.translate(-3.0f, 0.0f, -5.0f);
	memcpy(matrixValue, model_matrix.m, sizeof(float)*16);
	if (m_index++ < 10 )
	{
		LOGI("render_model_matrix_loc\n");
		LOGI("%s\n", FloatArrayToString(matrixValue, 16).c_str());
	}
	glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, matrixValue);
	checkGlError("render_model_matrix_loc glUniformMatrix4fv");
	glDrawArrays(GL_TRIANGLES, 0, 3);
	checkGlError("checkGlError");

//	 // DrawElements
//	 model_matrix.translate(-1.0f, 0.0f, -5.0f);
//     memcpy(matrixValue, &model_matrix, sizeof(matrixValue));
//	 glUniformMatrix4fv(render_model_matrix_loc, 4, GL_FALSE, matrixValue);
//	 checkGlError("glUniformMatrix4fv");
//	 glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL);
//	 checkGlError("glDrawElements");
//	 // DrawElementsBaseVertex
//	 model_matrix.translate(1.0f, 0.0f, -5.0f);
//     memcpy(matrixValue, &model_matrix, sizeof(matrixValue));
//	 glUniformMatrix4fv(render_model_matrix_loc, 4, GL_FALSE, matrixValue);
//	 checkGlError("glUniformMatrix4fv");
//	 glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL);
//	 checkGlError("glDrawElements");
//	 // DrawArraysInstanced
//	 model_matrix.translate(3.0f, 0.0f, -5.0f);
//     memcpy(matrixValue, &model_matrix, sizeof(matrixValue));
//	 glUniformMatrix4fv(render_model_matrix_loc, 4, GL_FALSE, matrixValue);
//	 checkGlError("glUniformMatrix4fv");
//	 glDrawArrays(GL_TRIANGLES, 0, 3);
//	 checkGlError("glDrawArrays");
}
