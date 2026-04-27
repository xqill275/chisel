#version 330 core

in  vec2 v_texCoord;
out vec4 FragColor;

uniform sampler2D u_texture;
uniform vec4      u_colour; // tint — use (1,1,1,1) for no tint

void main() {
    FragColor = texture(u_texture, v_texCoord) * u_colour;
}
