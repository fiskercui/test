package Mesh;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.nio.ShortBuffer;

import javax.microedition.khronos.opengles.GL10;

import android.graphics.Bitmap;
import android.opengl.GLUtils;

public class Mesh {
	private FloatBuffer verticesBuffer = null;
	private ShortBuffer indicesBuffer = null;
	
	private int numofIndices = -1;
	
	private float[] rgba = new float[] {
			1.0f, 1.0f, 1.0f, 1.0f
	};
	private FloatBuffer colorBuffer = null;
	
	public float x = 0;
	public float y = 0;
	public float z = 0;
	
	public float rx = 0;
	public float ry = 0;
	public float rz = 0;
	
	//texture
	private FloatBuffer mTextureBuffer;
	/**
	 * Set the texture corrdinats
	 * @param gl
	 */
	protected void setTextureCoordinates(float[] textureCoords){
		ByteBuffer byteBuf = ByteBuffer.allocateDirect(textureCoords.length * 4);
		byteBuf.order(ByteOrder.nativeOrder());
		mTextureBuffer = byteBuf.asFloatBuffer();
		mTextureBuffer.put(textureCoords);
		mTextureBuffer.position(0);
	}
	private boolean mShouldLoadTexture = false;
	private int mTextureId = -1;
	private Bitmap mBitmap;
	/**
	 * 
	 * @param bitmap
	 */
	public void loadBitmap(Bitmap bitmap) {
		this.mBitmap = bitmap;
		mShouldLoadTexture = true;
	}
	
	private void loadGLTexture(GL10 gl)
	{
		int[] textures = new int[1];
		gl.glGenTextures(1,  textures, 0 );
		mTextureId = textures[0];
		
		gl.glBindTexture(GL10.GL_TEXTURE_2D, mTextureId);
		gl.glTexParameterf(GL10.GL_TEXTURE_2D,  GL10.GL_TEXTURE_MIN_FILTER, GL10.GL_LINEAR);
		gl.glTexParameterf(GL10.GL_TEXTURE_2D,  GL10.GL_TEXTURE_MAG_FILTER, GL10.GL_LINEAR);
		
		gl.glTexParameterf(GL10.GL_TEXTURE_2D,  GL10.GL_TEXTURE_WRAP_S, GL10.GL_CLAMP_TO_EDGE);
		gl.glTexParameterf(GL10.GL_TEXTURE_2D,  GL10.GL_TEXTURE_WRAP_T, GL10.GL_REPEAT);
		
		GLUtils.texImage2D(GL10.GL_TEXTURE_2D, 0, mBitmap, 0);
	}

	
	
	public void draw(GL10 gl){
		gl.glFrontFace(GL10.GL_CCW);
		gl.glEnable(GL10.GL_CULL_FACE);
		gl.glCullFace(GL10.GL_BACK);
		
//		gl.glLoadIdentity();
		
		gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);
		gl.glVertexPointer(3,  GL10.GL_FLOAT, 0, verticesBuffer);
		gl.glColor4f(rgba[0], rgba[1], rgba[2], rgba[3]);
		
		if(colorBuffer != null){
			gl.glEnableClientState(GL10.GL_COLOR_ARRAY);
			gl.glColorPointer(4, GL10.GL_FLOAT, 0, colorBuffer);
		}
		
		if(mShouldLoadTexture){
			loadGLTexture(gl);
			mShouldLoadTexture = false;
		}
		if(mTextureId != -1 && mTextureBuffer != null)
		{
			gl.glEnable(GL10.GL_TEXTURE_2D);
			gl.glEnableClientState(GL10.GL_TEXTURE_COORD_ARRAY);
			
			gl.glTexCoordPointer(2, GL10.GL_FLOAT, 0, mTextureBuffer);
			gl.glBindTexture(GL10.GL_TEXTURE_2D, mTextureId);
		}
		
		gl.glTranslatef(x,  y, z);
		gl.glRotatef(rx, 1, 0, 0);
		gl.glRotatef(ry, 0, 1, 0);
		gl.glRotatef(rz, 0, 0, 1);
		
		gl.glDrawElements(GL10.GL_TRIANGLES, numofIndices, GL10.GL_UNSIGNED_SHORT, indicesBuffer);
		
		gl.glDisableClientState(GL10.GL_VERTEX_ARRAY);
		gl.glDisable(GL10.GL_CULL_FACE);
	}
	
	protected void setVertices (float[] vertices){
		ByteBuffer vbb = ByteBuffer.allocateDirect(vertices.length * 4);
		vbb.order(ByteOrder.nativeOrder());
		verticesBuffer = vbb.asFloatBuffer();
		verticesBuffer.put(vertices);
		verticesBuffer.position(0);
	}
	
	protected void setIndices (short[] indices){
		ByteBuffer ibb = ByteBuffer.allocateDirect(indices.length * 2);
		ibb.order(ByteOrder.nativeOrder());
		indicesBuffer = ibb.asShortBuffer();
		indicesBuffer.put(indices);
		indicesBuffer.position(0);
		numofIndices = indices.length;
	}	
	
	protected void setColor(float red, float green, float blue, float alpha)
	{
		rgba[0] = red; 
		rgba[1] = green;
		rgba[2] = blue;
		rgba[3] = alpha;		
	}
	
	protected void setColors(float[] colors){
		ByteBuffer cbb = ByteBuffer.allocateDirect(colors.length * 4);
		cbb.order(ByteOrder.nativeOrder());
		colorBuffer = cbb.asFloatBuffer();
		colorBuffer.put(colors);
		colorBuffer.position(0);
	}

}
