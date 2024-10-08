#version 430 core

layout (location=0) in vec3 position;
layout (location=1) in vec3 normal;

uniform mat4 ls_model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * ls_model * vec4(position, 1.0f);
}