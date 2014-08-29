package com.example.ndkopengl;



import com.example.ndkopengl.Cocos2dxHelper.Cocos2dxHelperListener;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;

public class MainActivity extends Activity  implements Cocos2dxHelperListener {
	private Cocos2dxGLSurfaceView mGLSurfaceView;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
//		setContentView(R.layout.activity_main);
		Cocos2dxHelper.init(this);		
		mGLSurfaceView = new Cocos2dxGLSurfaceView(this);    
//        surface.setEGLContextClientVersion(2);
		mGLSurfaceView.setCocos2dxRenderer(new NdkGlRender());    
        setContentView(mGLSurfaceView);   
	}
	
	
	static {
		System.loadLibrary("NdkGLRenderer");
	}
	
	

	
	//??
	@Override
	public void runOnGLThread(final Runnable pRunnable) {
		this.mGLSurfaceView.queueEvent(pRunnable);
	}

	@Override
	public void showDialog(String pTitle, String pMessage) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void showEditTextDialog(String pTitle, String pMessage,
			int pInputMode, int pInputFlag, int pReturnType, int pMaxLength) {
		// TODO Auto-generated method stub
		
	}
	
	
}
