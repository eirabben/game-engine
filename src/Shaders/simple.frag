#version 330 core

in vec3 vertexColor;

out vec4 color;

void main() {
//    color = vec4(0.5, 0.0, 0.0, 1.0);
//    color = vertexColor;
    color = vec4(vertexColor, 1.0);
}