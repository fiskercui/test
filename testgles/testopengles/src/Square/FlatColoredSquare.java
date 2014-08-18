package Square;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import javax.microedition.khronos.opengles.GL10;

public class FlatColoredSquare extends Square {
	
	public float colors[] = {
			1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 1.0f,	
			1.0f, 0.0f, 1.0f, 1.0f,
	};
	private FloatBuffer colorBuffer;
	public FlatColoredSquare()
	{
		super();
		ByteBuffer ccb = ByteBuffer.allocateDirect(colors.length*4);
		ccb.order(ByteOrder.nativeOrder());
		colorBuffer = ccb.asFloatBuffer();
		colorBuffer.put(colors);
		colorBuffer.position(0);
	}
	
	
	public void draw(GL10 gl)
	{
		gl.glVertexPointer(3, GL10.GL_FLOAT, 0, vertexBuffer);
		gl.glEnableClientState(GL10.GL_COLOR_ARRAY);
		gl.glColorPointer(4, GL10.GL_FLOAT, 0, colorBuffer);		
		super.draw(gl);
		gl.glDisableClientState(GL10.GL_COLOR_ARRAY);
	}
}
