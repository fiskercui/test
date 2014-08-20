package Mesh;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLES20;


public class VBOMesh {
	
	public FloatBuffer verticesBuffer = null;
	public FloatBuffer colorBuffer = null;
	
	public FloatBuffer vaoHandle = null;
	
	public int floatSize = 4;
	
	protected void setVertices (float[] vertices){
		ByteBuffer vbb = ByteBuffer.allocateDirect(vertices.length * 4);
		vbb.order(ByteOrder.nativeOrder());
		verticesBuffer = vbb.asFloatBuffer();
		verticesBuffer.put(vertices);
		verticesBuffer.position(0);
	}
	
	protected void setColors(float[] colors){
		ByteBuffer cbb = ByteBuffer.allocateDirect(colors.length * 4);
		cbb.order(ByteOrder.nativeOrder());
		colorBuffer = cbb.asFloatBuffer();
		colorBuffer.put(colors);
		colorBuffer.position(0);
	}

	
	void initVBO(GL10 gl)  
	{  
		
		int[] vboHandles = new int[2];
		GLES20.glGenBuffers(2, vboHandles, 0);
		int positionBufferHandle = vboHandles[0];
		int colorBufferHandle = vboHandles[1];
		
		GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, positionBufferHandle);
		GLES20.glBufferData(GLES20.GL_ARRAY_BUFFER, floatSize * 9, verticesBuffer, GLES20.GL_STATIC_DRAW);
		
		GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, colorBufferHandle);
		GLES20.glBufferData(GLES20.GL_ARRAY_BUFFER, floatSize * 9, colorBuffer, GLES20.GL_STATIC_DRAW);
		
//		GLES10.
//		GLES20.glGenVertexArrays(1, &vaoHandle);
		
	    // Create and populate the buffer objects  
//	    GLuint vboHandles[2];  
//	    gl.glGenBuffers(2, vboHandles);  
//	    GLuint positionBufferHandle = vboHandles[0];  
//	    GLuint colorBufferHandle = vboHandles[1];  
//	  
//	    //绑定VBO以供使用  
//	    gl.glBindBuffer(GL10.GL_ARRAY_BUFFER,positionBufferHandle);  
//	    //加载数据到VBO  
//	    glBufferData(GL_ARRAY_BUFFER,9 * sizeoffloat,  
//	        positionData,GL_STATIC_DRAW);  
//	  
//	    //绑定VBO以供使用  
//	    glBindBuffer(GL_ARRAY_BUFFER,colorBufferHandle);  
//	    //加载数据到VBO  
//	    glBufferData(GL_ARRAY_BUFFER,9 * sizeoffloat,  
//	        colorData,GL_STATIC_DRAW);  
//	  
//	    glGenVertexArrays(1,&vaoHandle);  
//	    glBindVertexArray(vaoHandle);  
//	  
//	    glEnableVertexAttribArray(0);//顶点坐标  
//	    glEnableVertexAttribArray(1);//顶点颜色  
//	  
//	    //调用glVertexAttribPointer之前需要进行绑定操作  
//	    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);  
//	    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL );  
//	  
//	    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);  
//	    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL );  
	}  
	
	
	public VBOMesh(){
		float ver[] = {  
			    -0.8f, -0.8f, 0.0f,  
			    0.8f, -0.8f, 0.0f,  
			    0.0f,  0.8f, 0.0f };  
			//颜色数组  
		float colorData[] = {  
			        1.0f, 0.0f, 0.0f,  
			        0.0f, 1.0f, 0.0f,  
		        0.0f, 0.0f, 1.0f }; 
		setVertices(ver);
		setColors(colorData);		
	}
	
}
