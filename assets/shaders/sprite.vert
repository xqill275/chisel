#version 330 core

// Per-vertex inputs
layout (location = 0) in vec2 a_position;
layout (location = 1) in vec2 a_texCoord;

// Output to fragment shader
out vec2 v_texCoord;

// Uniforms
uniform mat4 u_model;
uniform mat4 u_projection;

void main() {
    gl_Position = u_projection * u_model * vec4(a_position, 0.0, 1.0);
    v_texCoord  = a_texCoord;
}
