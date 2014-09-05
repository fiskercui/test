uniform mat4 model_matrix;
uniform mat4 projection_matrix;

attribute vec4 vPosition;

void main() {
    gl_Position = vPosition;
}