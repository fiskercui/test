#include "TestShader.h"
#include "LoadShaders.h"
#include <stdio.h>
#include <android/log.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

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

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };
GLuint  VAOs[NumVAOs];
GLuint  Buffers[NumBuffers];

const GLuint NumVertices = 6;



void ShaderObject::init(int width, int height)
{
    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

    LOGI("NumVAOS = %d", NumVAOs);
    LOGI("NumBuffers = %d", NumBuffers);

    LOGI("setupGraphics(%d, %d)", width, height);

	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);
//	GLfloat  vertices[NumVertices][2] = {
//		{ -0.90, -0.90 },  // Triangle 1
//		{  0.85, -0.90 },
//		{ -0.90,  0.85 },
//		{  0.90, -0.85 },  // Triangle 2
//		{  0.90,  0.90 },
//		{ -0.85,  0.90 }
//	};
	GLfloat vertices[3][2] = {
		{ -1, 1 },  // Triangle 1
		{  1, 2 },
		{ 1, 1 },
	};
	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	ShaderInfo  shaders[] = {
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" },
		{ GL_NONE, NULL }
	};
	GLuint program = LoadShaders(shaders);
	glUseProgram(program);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT,
	                  GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);


    LOGI("vPosition(\"vPosition\") = %d\n",
    		vPosition);

    GLuint gvPositionHandle;
    gvPositionHandle = glGetAttribLocation(program, "vPosition");
    checkGlError("glGetAttribLocation");
    LOGI("glGetAttribLocation(\"vPosition\") = %d\n",
            gvPositionHandle);
}

void ShaderObject::draw()
{
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(VAOs[Triangles]);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

}
