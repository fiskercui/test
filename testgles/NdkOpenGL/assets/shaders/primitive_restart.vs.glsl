
uniform mat4 model_matrix;
uniform mat4 projection_matrix;


attribute vec4 position;
attribute vec4 color;

vec4 vs_fs_color;

void main(void)
{
    vs_fs_color = color;
    gl_Position = projection_matrix * (model_matrix * position);
}
