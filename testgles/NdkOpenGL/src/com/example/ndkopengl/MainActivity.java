package com.example.ndkopengl;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
//		setContentView(R.layout.activity_main);
		
		GLSurfaceView surface = new GLSurfaceView(this);    
        surface.setRenderer(new NdkGlRender());    
        setContentView(surface);   
	}
	
	
	static {
		System.loadLibrary("NdkGLRenderer");
	}
	
	
}
