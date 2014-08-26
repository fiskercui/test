package Square;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLU;
import android.opengl.GLSurfaceView.Renderer;
import android.util.Log;

public class SquareRenderer implements Renderer {
	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * android.opengl.GLSurfaceView.Renderer#onSurfaceCreated(javax.
         * microedition.khronos.opengles.GL10, javax.microedition.khronos.
         * egl.EGLConfig)
         * 
	 */
	
	public FlatColoredSquare square = new FlatColoredSquare();
	public float angle = 30.0f;
	
	
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		// Set the background color to black ( rgba ).
		gl.glClearColor(0.0f, 0.0f, 0.0f, 0.5f);  // OpenGL docs.
		// Enable Smooth Shading, default not really needed.
		gl.glShadeModel(GL10.GL_SMOOTH);// OpenGL docs.
		// Depth buffer setup.
		gl.glClearDepthf(1.0f);// OpenGL docs.
		// Enables depth testing.
		gl.glEnable(GL10.GL_DEPTH_TEST);// OpenGL docs.
		// The type of depth testing to do.
		gl.glDepthFunc(GL10.GL_LEQUAL);// OpenGL docs.
		// Really nice perspective calculations.
		gl.glHint(GL10.GL_PERSPECTIVE_CORRECTION_HINT, // OpenGL docs.
                          GL10.GL_NICEST);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * android.opengl.GLSurfaceView.Renderer#onDrawFrame(javax.
         * microedition.khronos.opengles.GL10)
	 */
	public void onDrawFrame(GL10 gl) {
		// Clears the screen and depth buffer.
		gl.glClear(GL10.GL_COLOR_BUFFER_BIT | // OpenGL docs.
                           GL10.GL_DEPTH_BUFFER_BIT);
		gl.glLoadIdentity();
		int width = 960,height = 640;
		float zeye = 640/1.1566f;
		GLU.gluLookAt(gl, width/2, height/2, zeye,  width/3, height/2, 0f, 0.0f, 1.0f, 0.0f);
//		GLU.gluLookAt(gl, 7.5, 7.5, 12.5,  2.5, 2.5, -5.0, 0.0, 1.0, 0.0);
//		GLU.gluLookAt(gl, width/2, height/2, zeye, width/2, height/2, 0.0f, 0.0f, 1.0f, 0.0f);
//		gl.glTranslatef(0,0,-10);
		
		gl.glPushMatrix();
		gl.glRotatef(angle, 0 , 0, 1);
		square.draw(gl);
		gl.glPopMatrix();
	
		// SQUARE B
		// Save the current matrix
		gl.glPushMatrix();
		// Rotate square B before moving it,
		// making it rotate around A.
		gl.glRotatef(-angle, 0, 0, 1);
		// Move square B.
		gl.glTranslatef(2, 0, 0);
		// Scale it to 50% of square A
		gl.glScalef(.5f, .5f, .5f);
		// Draw square B.
		square.draw(gl);

		// SQUARE C
		// Save the current matrix
		gl.glPushMatrix();
		// Make the rotation around B
		gl.glRotatef(-angle, 0, 0, 1);
		gl.glTranslatef(2, 0, 0);
		// Scale it to 50% of square B
		gl.glScalef(.5f, .5f, .5f);
		// Rotate around it's own center.
//		gl.glRotatef(angle * 10, 0, 0, 1);
		// Draw square C.
		square.draw(gl);
		
		gl.glPopMatrix();
		gl.glPopMatrix();
		
		angle++;
		Log.i("angle", "android" + angle);

	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * android.opengl.GLSurfaceView.Renderer#onSurfaceChanged(javax.
         * microedition.khronos.opengles.GL10, int, int)
	 */
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		
//		glViewport (0,0, 960, 640);
//	    Size size(960,640);
//	    float zeye = 640/1.1566f;
//
//	    Mat4 matrixPerspective, matrixLookup;
//
//	    loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
//
//	#if CC_TARGET_PLATFORM == CC_PLATFORM_WP8
//	    //if needed, we need to add a rotation for Landscape orientations on Windows Phone 8 since it is always in Portrait Mode
//	    GLView* view = getOpenGLView();
//	    if(getOpenGLView() != nullptr)
//	    {
//	        multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, getOpenGLView()->getOrientationMatrix());
//	    }
//	#endif
//	    // issue #1334
//	    Mat4::createPerspective(60, (GLfloat)size.width/size.height, 1, zeye+size.height/2, &matrixPerspective);
//
//	    multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, matrixPerspective);
//
//	    Vec3 eye(size.width/2, size.height/2, zeye), center(size.width/2, size.height/2, 0.0f), up(0.0f, 1.0f, 0.0f);
//	    Mat4::createLookAt(eye, center, up, &matrixLookup);
//	    multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, matrixLookup);
//
//	    loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);		
		
		float zeye = 640/1.1566f;
		// Sets the current view port to the new size.
		gl.glViewport(0, 0, width, height);// OpenGL docs.
//		gl.glOrthox(0, 0, width, height, -2, 100);

		// Select the projection matrix
		gl.glMatrixMode(GL10.GL_PROJECTION);// OpenGL docs.
		// Reset the projection matrix
		gl.glLoadIdentity();// OpenGL docs.
		// Calculate the aspect ratio of the window
		
//		GLU.gluPerspective(gl, 45.0f,
//                (float) width / (float) height,
//                0.1f, 100.0f);
		GLU.gluPerspective(gl, 90.0f,
                                   (float) width / (float) height,
                                   0.1f, 800);
//		GLU.gluLookAt(gl, width/2, height/2, zeye, width/2, height/2, 0.0f, 0.0f, 1.0f, 0.0f);
		// Select the modelview matrix
		gl.glMatrixMode(GL10.GL_MODELVIEW);// OpenGL docs.
		// Reset the modelview matrix

		gl.glLoadIdentity();// OpenGL docs.
//		GLU.gluLookAt(gl, width/2+300, height/2+100, zeye, width/2+300, height/2+100, 0.0f, 0.0f, 1.0f, 0.0f);
	}
}
