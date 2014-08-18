package com.test.opengl;

import Mesh.Cube;
import Mesh.MeshRenderer;
import Mesh.SimplePlane;
import android.app.Activity;
import android.graphics.BitmapFactory;
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


 		SimplePlane plane = new SimplePlane(1, 1);
		plane.z = 1.7f;
		plane.rx = -65;
		// Load the texture.
		plane.loadBitmap(BitmapFactory.decodeResource(getResources(),
				R.drawable.jay));
		
		Cube cube = new Cube(1, 1, 1);
		cube.rx = 45;
		cube.ry = 45;
		
 		MeshRenderer renderer = new MeshRenderer();
 		//add先后顺序有影响
// 		renderer.AddMesh(cube);
 		renderer.AddMesh(plane);
 		view.setRenderer(renderer); 


   		setContentView(view);
    }
}
