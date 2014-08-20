#include <jni.h>
#include <GLES/gl.h>
unsigned int vbo[2];
float positions[12] = {1,-1,0, 1,1,0, -1,-1,0, -1,1,0};
short indices  [4]  = {0,1,2,3};
JNIEXPORT void JNICALL Java_com_example_ndkopengl_NdkGlRender_onNdkSurfaceCreated (JNIEnv* env, jobject obj)
{
	//������������������
	glGenBuffers (2, vbo);
	//�󶨵�һ���������
	glBindBuffer (GL_ARRAY_BUFFER, vbo[0]);
	//�����ͳ�ʼ����һ�����������������
	glBufferData (GL_ARRAY_BUFFER, 4*12, positions, GL_STATIC_DRAW);
	//�󶨵ڶ����������
	glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
	//�����ͳ�ʼ���ڶ������������������
	glBufferData (GL_ELEMENT_ARRAY_BUFFER, 2*4, indices, GL_STATIC_DRAW);
}

JNIEXPORT void JNICALL Java_com_example_ndkopengl_NdkGlRender_onNdkSurfaceChanged(JNIEnv* env, jobject obj, jint width, jint height)
{
	//ͼ��������ʾ����Ļ�������λ�á����Ϳ�
	glViewport (0,0,width,height);
	//ָ������
	glMatrixMode   (GL_PROJECTION);
	//����ǰ�ľ�������ΪglMatrixModeָ���ľ���
	glLoadIdentity ();
	glOrthof(-2, 2, -2, 2, -2, 2);
}

JNIEXPORT void JNICALL Java_com_example_ndkopengl_NdkGlRender_onNdkDrawFrame (JNIEnv* env, jobject obj)
{
	//���ö������ù��ܣ�֮�����Ҫ�رչ���
	glEnableClientState (GL_VERTEX_ARRAY);
	//����
	glClearColor (0,0,1,1);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	glBindBuffer    (GL_ARRAY_BUFFER, vbo[0]);
	//���嶥������
	glVertexPointer (3, GL_FLOAT, 0, 0);
	glBindBuffer    (GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
	//���ղ���������ֵ����ͼ��
	glDrawElements  (GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);
	//�رն������ù���
	glDisableClientState(GL_VERTEX_ARRAY);
}
