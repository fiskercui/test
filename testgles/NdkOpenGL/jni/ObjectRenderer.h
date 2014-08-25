#include <stack>
#include "math/Mat4.h"

using namespace cocos2d;

enum class MATRIX_STACK_TYPE
{
    MATRIX_STACK_MODELVIEW,
    MATRIX_STACK_PROJECTION,
    MATRIX_STACK_TEXTURE
};

class ObjectRenderer
{
public:
	ObjectRenderer();
	~ObjectRenderer();

	void onDrawFrame();
	void onSurfaceCreated();
	void onSurfaceChanged(int width, int height);

	static ObjectRenderer* getInstance();

	void setupProjection();

protected:
	static ObjectRenderer* s_render;
	/* data */
private:
    std::stack<Mat4> _modelViewMatrixStack;
    std::stack<Mat4> _projectionMatrixStack;
    std::stack<Mat4> _textureMatrixStack;
protected:
    void initMatrixStack();
public:
    void pushMatrix(MATRIX_STACK_TYPE type);
    void popMatrix(MATRIX_STACK_TYPE type);
    void loadIdentityMatrix(MATRIX_STACK_TYPE type);
    void loadMatrix(MATRIX_STACK_TYPE type, const Mat4& mat);
    void multiplyMatrix(MATRIX_STACK_TYPE type, const Mat4& mat);
    Mat4 getMatrix(MATRIX_STACK_TYPE type);
    void resetMatrixStack();
};
