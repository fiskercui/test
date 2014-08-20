package com.example.ndkopengl;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView.Renderer;

public class NdkGlRender implements Renderer {

	native private void onNdkSurfaceCreated ();   	
	native private void onNdkDrawFrame ();   
	native private void onNdkSurfaceChanged (int width, int height);   
	
	@Override
	public void onDrawFrame(GL10 gl) {
		// TODO Auto-generated method stub
		onNdkDrawFrame();
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		// TODO Auto-generated method stub
		onNdkSurfaceChanged(width, height);
	}

	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig arg1) {
		// TODO Auto-generated method stub
		onNdkSurfaceCreated();
	}

}
