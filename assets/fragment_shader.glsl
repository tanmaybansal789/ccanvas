#version 410 core

out vec4 FragColor;                  // Final color output
in vec2 TexCoord;                    // Texture coordinates from vertex shader

uniform sampler2D screenTexture;     // Texture sampler

void main() {
    FragColor = texture(screenTexture, TexCoord); // Sample the texture using TexCoord
}