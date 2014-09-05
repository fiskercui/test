#include "base/ccMacros.h"
#include "base/CCLog.h"
#include "base/CCGL.h"
#include "base/CCPlatformMacros.h"



class DrawCommandTest
{
public:
	DrawCommandTest();
	~DrawCommandTest();

	void init(int width , int height);

	void draw();

	/* data */

protected:
	int m_index;
	float aspect;

	GLuint render_prog;

	GLuint vao[1];
	GLuint vbo[1];
	GLuint ebo[1];

	GLint render_model_matrix_loc;
	GLint render_projection_matrix_loc;
};
