#include "TestShader.h"
#include "LoadShaders.h"
#include <stdio.h>
#include <android/log.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "math/CCGeometry.h"
#include "math/Mat4.h"

#include "base/ccMacros.h"
#include "base/CCLog.h"
#include "base/CCGL.h"
#include "base/CCPlatformMacros.h"

USING_NS_CC;

//#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

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

#define BUFFER_OFFSET(x)  ((const void*) (x))

enum VAO_IDs { Triangles, Triangles2, NumVAOs };
enum Buffer_IDs { ArrayBuffer, ArrayBuffer2,NumBuffers };
enum Attrib_IDs { vPosition = 0 };
GLuint  VAOs[NumVAOs];
GLuint  Buffers[NumBuffers];

const GLuint NumVertices = 6;


GLuint program;
static GLuint gvPositionHandle;
const GLfloat gTriangleVertices[] = { 0.0f, 0.5f, -0.5f, -0.5f,
        0.5f, -0.5f };

void ShaderObject::init(int width, int height)
{
	this->width = width;
	this->height = height;
	aspect = (float) width/height;
    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

    LOGI("NumVAOS = %d", NumVAOs);
    LOGI("NumBuffers = %d", NumBuffers);
    LOGI("setupGraphics(%d, %d)", width*2, height*2);

	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);
//	GLfloat vertices[NumVertices][2] = {
//		{ -0.90f, -.90f },  // Triangle 1
//		{  0.85f, -0.90f },
//		{ -0.90f, 0.85f },
//		{  0.90, -0.85 },  // Triangle 2
//		{  0.90,  0.90 },
//		{ -0.85,  0.90 },
//	};
//	GLfloat vertices[NumVertices][2] = {
//		{ -1.0f, -1.0f },  // Triangle 1
//		{  1.0f, -1.0f },
//		{ -1.0f, 1.0f },
//		{  1.0f, -1.0f },  // Triangle 2
//		{  1.0f,  1.0f },
//		{ -1.0f,  1.0f },
//	};
	GLfloat vertices[NumVertices][2] = {
		{ -90.0f, 90.0f },  // Triangle 1
		{  85.0f, 90.0f },
		{ -90.0f, 85.0f },
		{  90.0f, 85.0f },  // Triangle 2
		{  90.0f, 90.0f },
		{ -85.0f, 90.0f },
	};
	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	ShaderInfo  shaders[] = {
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" },
		{ GL_NONE, NULL }
	};
	program = LoadShaders(shaders);
	glUseProgram(program);

	render_model_matrix_loc = glGetUniformLocation(program, "model_matrix");
	checkGlError("glGetUniformLocation");
	LOGI("render_model_matrix_loc = %d",render_model_matrix_loc);
//	LOGI("", );
	render_projection_matrix_loc = glGetUniformLocation(program, "projection_matrix");
	checkGlError("glGetUniformLocation");
	LOGI("render_projection_matrix_loc = %d",render_projection_matrix_loc);


	glVertexAttribPointer(vPosition, 2, GL_FLOAT,
	                  GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);

    LOGI("vPosition(\"vPosition\") = %d\n",
    		vPosition);
    gvPositionHandle = glGetAttribLocation(program, "vPosition");
    checkGlError("glGetAttribLocation");
    LOGI("glGetAttribLocation(\"vPosition\") = %d\n",
            gvPositionHandle);
    glViewport(0, 0, width, height);
}


#define MAX_LEN 1024
static char s_temp[MAX_LEN];
static std::string FloatToChar10(float f)
{
    snprintf(s_temp, MAX_LEN, "%f", f);
    return (std::string) s_temp;
}

static std::string IntToChar10(int num)
{
	snprintf(s_temp, MAX_LEN, "%d", num);
	return (std::string) s_temp;
}

static std::string FloatArrayToString(float f[], int size)
{
	printf("convertFloatArrayToString\n");
	std::string sTemp;
	for (int i = 0; i < size; ++i)
	{
		sTemp += "[" + IntToChar10(i) + "]:" + FloatToChar10(f[i]) + ",";
	}
	return sTemp;
}

void ShaderObject::draw()
{
	static float grey;
	grey += 0.01f;
	if (grey > 1.0f) {
		grey = 0.0f;
	}
	glClearColor(grey, grey, grey, 1.0f);
	checkGlError("glClearColor");
	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	checkGlError("glClear");

	glUseProgram(program);
	checkGlError("glUseProgram");

	Mat4 projection_matrix = Mat4::IDENTITY;
//	Mat4::createPerspective(60, aspect, 10.0f, getZEye() + height/2, &projection_matrix);
//	Mat4::createFrustum(-1.0f, 1.0f, -aspect, aspect,1.0f, 500.0f, &projection_matrix);
//	std::string s = FloatArrayToString(projection_matrix.m,16);
//	LOGI("s = %s", s.c_str());

//	projection_matrix.m[0] = 1.1547f;
//	projection_matrix.m[5] = 1.73205090f;
//	projection_matrix.m[10] = 1.02316570f;
//	projection_matrix.m[11] = -1.0000f;
//	projection_matrix.m[14] = 20.2316570f;

	projection_matrix.m[12] = -480.0f;
	projection_matrix.m[13] = -320.0f;
	projection_matrix.m[14] = -553.346008f;
	projection_matrix.m[15] = 1.0f;

		std::string s = FloatArrayToString(projection_matrix.m,16);
		LOGI("s = %s", s.c_str());

//	projection_matrix.m[0] = 0.3f;
//	projection_matrix.m[5] = 0.3f;
//	projection_matrix.m[10] = 0.2f;

	LOGI("createPerspective  width=%f, height = %f,aspect=%f, zFar:%f",width,  height, aspect,getZEye() + height/2);
//    float matrixValue[16];
//    memcpy(matrixValue, projection_matrix.m, sizeof(float)*16);
	glUniformMatrix4fv(render_projection_matrix_loc, 1, GL_FALSE, projection_matrix.m);

	Mat4 model_matrix = Mat4::IDENTITY;
//    memcpy(matrixValue, model_matrix.m, sizeof(float)*16);
	glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, model_matrix.m);

    glBindVertexArray(VAOs[Triangles]);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

//	static float grey;
//	grey += 0.01f;
//	if (grey > 1.0f) {
//		grey = 0.0f;
//	}
//	glClearColor(grey, grey, grey, 1.0f);
//	checkGlError("glClearColor");
//	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
//	checkGlError("glClear");
//
//	glUseProgram(program);
//	checkGlError("glUseProgram");

//	glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
//	checkGlError("glVertexAttribPointer");
//	glEnableVertexAttribArray(gvPositionHandle);
//	checkGlError("glEnableVertexAttribArray");
//	glDrawArrays(GL_TRIANGLES, 0, 3);
//	checkGlError("glDrawArrays");
}

float ShaderObject::getZEye()
{
	return this->height/1.1566f;
}
