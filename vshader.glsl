#version 330

in vec4 vertex;
uniform mat4 projMatrix;
uniform mat4 mvMatrix;

void main() {
    vec4 vert = mvMatrix * vertex;
    gl_Position = projMatrix * vert;
}
