#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec4 a_color;

out vec4 v_color;

void main() {
    gl_Position = vec4(position, 0.f, 1.f);
    v_color = a_color;
}