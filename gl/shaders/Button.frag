#version 410 core

in vec2 TexCoord;
out vec4 FragColor;
uniform sampler2D uTexture;
void main() {
    FragColor = texture(uTexture, TexCoord);
    if (FragColor.a < 0.1) discard;
}
