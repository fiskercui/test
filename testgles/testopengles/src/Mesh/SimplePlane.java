package Mesh;

public class SimplePlane extends Mesh{
	
	public SimplePlane()
	{
		this(1, 1);
	}
	
	 public SimplePlane(float width, float height) 
	 {
		  // Mapping coordinates for the vertices
		 float textureCoordinates[] = { 
			0.0f, 2.0f, //
		    2.0f, 2.0f, //
		  	0.0f, 0.0f, //
		  	2.0f, 0.0f, //
		  };
		 short[] indices = new short[] { 0, 1, 2, 1, 3, 2 };

		 float[] vertices = new float[] { 
				 -0.5f, -0.5f, 0.0f,
				  0.5f, -0.5f, 0.0f,
				  -0.5f,  0.5f, 0.0f,
				  0.5f, 0.5f, 0.0f };
		 setIndices(indices);
		 setVertices(vertices);
		 setTextureCoordinates(textureCoordinates);
	 }
	
}
