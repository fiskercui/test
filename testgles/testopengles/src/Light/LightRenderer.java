package Light;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import Mesh.Sphere;
import android.opengl.GLU;
import android.opengl.GLSurfaceView.Renderer;

public class LightRenderer implements Renderer{
	
	public Sphere sphere = new Sphere();
	
	public void initScene(GL10 gl) {
		float[] amb = { 1.0f, 1.0f, 1.0f, 1.0f, };
		float[] diff = { 1.0f, 1.0f, 1.0f, 1.0f, };
		float[] spec = { 1.0f, 1.0f, 1.0f, 1.0f, };
		float[] pos = { 0.0f, 5.0f, 5.0f, 1.0f, };
		float[] spot_dir = { 0.0f, -1.0f, 0.0f, };
		gl.glEnable(GL10.GL_DEPTH_TEST);
		gl.glEnable(GL10.GL_CULL_FACE);

		gl.glEnable(GL10.GL_LIGHTING);
		gl.glEnable(GL10.GL_LIGHT0);
		ByteBuffer abb = ByteBuffer.allocateDirect(amb.length * 4);
		abb.order(ByteOrder.nativeOrder());
		FloatBuffer ambBuf = abb.asFloatBuffer();
		ambBuf.put(amb);
		ambBuf.position(0);

		ByteBuffer dbb = ByteBuffer.allocateDirect(diff.length * 4);
		dbb.order(ByteOrder.nativeOrder());
		FloatBuffer diffBuf = dbb.asFloatBuffer();
		diffBuf.put(diff);
		diffBuf.position(0);

		ByteBuffer sbb = ByteBuffer.allocateDirect(spec.length * 4);
		sbb.order(ByteOrder.nativeOrder());
		FloatBuffer specBuf = sbb.asFloatBuffer();
		specBuf.put(spec);
		specBuf.position(0);

		ByteBuffer pbb = ByteBuffer.allocateDirect(pos.length * 4);
		pbb.order(ByteOrder.nativeOrder());
		FloatBuffer posBuf = pbb.asFloatBuffer();
		posBuf.put(pos);
		posBuf.position(0);

		ByteBuffer spbb = ByteBuffer.allocateDirect(spot_dir.length * 4);
		spbb.order(ByteOrder.nativeOrder());
		FloatBuffer spot_dirBuf = spbb.asFloatBuffer();
		spot_dirBuf.put(spot_dir);
		spot_dirBuf.position(0);

		gl.glLightfv(GL10.GL_LIGHT0, GL10.GL_AMBIENT, ambBuf);
		gl.glLightfv(GL10.GL_LIGHT0, GL10.GL_DIFFUSE, diffBuf);
		gl.glLightfv(GL10.GL_LIGHT0, GL10.GL_SPECULAR, specBuf);
		gl.glLightfv(GL10.GL_LIGHT0, GL10.GL_POSITION, posBuf);
		gl.glLightfv(GL10.GL_LIGHT0, GL10.GL_SPOT_DIRECTION, spot_dirBuf);
		gl.glLightf(GL10.GL_LIGHT0, GL10.GL_SPOT_EXPONENT, 0.0f);
		gl.glLightf(GL10.GL_LIGHT0, GL10.GL_SPOT_CUTOFF, 45.0f);

		gl.glLoadIdentity();
		GLU.gluLookAt(gl, 0.0f, 4.0f, 4.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	}

	@Override
	public void onDrawFrame(GL10 gl) {
		// TODO Auto-generated method stub
		gl.glClear(GL10.GL_COLOR_BUFFER_BIT | GL10.GL_DEPTH_BUFFER_BIT);
		// Replace the current matrix with the identity matrix
		gl.glLoadIdentity();
		// Translates 4 units into the screen.
		gl.glTranslatef(0, 0, -4); 
		// Draw our scene.

		float[] mat_amb = { 0.2f * 0.4f, 0.2f * 0.4f, 0.2f * 1.0f, 1.0f, };
		float[] mat_diff = { 0.4f, 0.4f, 1.0f, 1.0f, };
		float[] mat_spec = { 1.0f, 1.0f, 1.0f, 1.0f, };

		ByteBuffer mabb = ByteBuffer.allocateDirect(mat_amb.length * 4);
		mabb.order(ByteOrder.nativeOrder());
		FloatBuffer mat_ambBuf = mabb.asFloatBuffer();
		mat_ambBuf.put(mat_amb);
		mat_ambBuf.position(0);

		ByteBuffer mdbb = ByteBuffer.allocateDirect(mat_diff.length * 4);
		mdbb.order(ByteOrder.nativeOrder());
		FloatBuffer mat_diffBuf = mdbb.asFloatBuffer();
		mat_diffBuf.put(mat_diff);
		mat_diffBuf.position(0);

		ByteBuffer msbb = ByteBuffer.allocateDirect(mat_spec.length * 4);
		msbb.order(ByteOrder.nativeOrder());
		FloatBuffer mat_specBuf = msbb.asFloatBuffer();
		mat_specBuf.put(mat_spec);
		mat_specBuf.position(0);

		gl.glMaterialfv(GL10.GL_FRONT_AND_BACK, GL10.GL_AMBIENT, mat_ambBuf);
		gl.glMaterialfv(GL10.GL_FRONT_AND_BACK, GL10.GL_DIFFUSE, mat_diffBuf);
		gl.glMaterialfv(GL10.GL_FRONT_AND_BACK, GL10.GL_SPECULAR, mat_specBuf);
		gl.glMaterialf(GL10.GL_FRONT_AND_BACK, GL10.GL_SHININESS, 64.0f);
		sphere.draw(gl);
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		// TODO Auto-generated method stub
		gl.glViewport(0, 0, width, height);
		// Select the projection matrix
		gl.glMatrixMode(GL10.GL_PROJECTION);
		// Reset the projection matrix
		gl.glLoadIdentity();
		// Calculate the aspect ratio of the window
		GLU.gluPerspective(gl, 45.0f, (float) width / (float) height, 0.1f,
				100.0f);
		// Select the modelview matrix
		gl.glMatrixMode(GL10.GL_MODELVIEW);
		// Reset the modelview matrix
		gl.glLoadIdentity();		
	}

	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		// TODO Auto-generated method stub
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
		this.initScene(gl);
	}

}
