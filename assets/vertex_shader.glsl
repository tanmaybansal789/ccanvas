#version 410 core

layout (location = 0) in vec2 aPos;  // Position of each vertex in the quad
out vec2 TexCoord;                   // Texture coordinates for the fragment shader

void main() {
    TexCoord = (aPos + 1.0) / 2.0;   // Map from [-1, 1] range to [0, 1] range
    gl_Position = vec4(aPos, 0.0, 1.0); // Set position in clip space
}