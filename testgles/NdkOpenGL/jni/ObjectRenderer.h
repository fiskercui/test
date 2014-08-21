

class ObjectRenderer
{
public:
	ObjectRenderer();
	~ObjectRenderer();

	void onDrawFrame();
	void onSurfaceCreated();
	void onSurfaceChanged(int width, int height);

	static ObjectRenderer* getInstance();

protected:
	static ObjectRenderer* s_render;
	/* data */
};
