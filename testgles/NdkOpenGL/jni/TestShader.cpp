#include "TestShader.h"
#include "LoadShaders.h"
#include <stdio.h>
#include <android/log.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>



#include "base/CCGL.h"

#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
//#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


#define BUFFER_OFFSET(x)  ((const void*) (x))

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };
GLuint  VAOs[NumVAOs];
GLuint  Buffers[NumBuffers];

const GLuint NumVertices = 6;



void ShaderObject::init(int width, int height)
{
    glViewport(0, 0, width, height);
	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);
	GLfloat  vertices[NumVertices][2] = {
	{ -0.90, -0.90 },  // Triangle 1
	{  0.85, -0.90 },
	{ -0.90,  0.85 },
	{  0.90, -0.85 },  // Triangle 2
	{  0.90,  0.90 },
	{ -0.85,  0.90 }
	};
	glGenBuffers(NumBuffers, Buffers); glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]); glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
	         vertices, GL_STATIC_DRAW);
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
}

void ShaderObject::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(VAOs[Triangles]);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

}
