#version 410 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform vec2 uScreenSize;
uniform vec2 uPos;
uniform vec2 uSize;

void main() {
    vec2 pos = aPos * uSize + uPos;
    vec2 ndc = pos / uScreenSize * 2.0 - 1.0;
    ndc.y = -ndc.y;
    gl_Position = vec4(ndc, 0.0, 1.0);
    TexCoord = aTexCoord;
}
