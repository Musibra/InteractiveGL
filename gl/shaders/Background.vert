#version 410 core

in vec2 vertexPosition;
in vec3 vertexColor;

out vec3 fragColor;

void main() {
    gl_Position = vec4(vertexPosition, 0.0, 1.0);
    fragColor = vertexColor;
}
