#version 330 core

layout(location = 0) in vec3 inVertex;
layout(location = 1) in vec3 inColor;
out vec3 color;

uniform mat4 transform;

void main() {
    color = inColor;
    gl_Position = transform * vec4(inVertex, 1.0);
}