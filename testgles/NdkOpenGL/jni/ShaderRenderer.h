#include "base/CCGLView.h"

USING_NS_CC;

class ShaderRenderer
{
public:
	ShaderRenderer();
	~ShaderRenderer();

	void onDrawFrame();
	void onSurfaceCreated();
	void onSurfaceChanged(int width, int height);

	static ShaderRenderer* getInstance();
protected:
	static ShaderRenderer* s_render;

protected:
    /* The GLView, where everything is rendered */
    GLView *_openGLView;
};
