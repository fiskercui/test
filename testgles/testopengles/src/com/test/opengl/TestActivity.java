package com.test.opengl;

import Square.SquareRenderer;
import Mesh.MeshRenderer;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.Window;
import android.view.WindowManager;

public class TestActivity extends Activity {
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
    	super.onCreate(savedInstanceState);
    	this.requestWindowFeature(Window.FEATURE_NO_TITLE); // (NEW)
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
            WindowManager.LayoutParams.FLAG_FULLSCREEN); // (NEW)

 		GLSurfaceView view = new GLSurfaceView(this);

 		//   		view.setRenderer(new SquareRenderer());
 		view.setRenderer(new MeshRenderer()); 
   		setContentView(view);
    }
}
