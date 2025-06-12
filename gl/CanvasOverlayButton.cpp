//
// Created by Mustafa İbrahim on 6/13/2025.
//

#include "CanvasOverlayButton.h"
#include <iostream>
#include <vector>
#include <wx/image.h>  // wxWidgets image loading

CanvasOverlayButton::CanvasOverlayButton(int x, int y, int width_, int height_)
    : posX(x), posY(y), width(width_), height(height_)
{
}

CanvasOverlayButton::~CanvasOverlayButton()
{
    if (shaderProgram) glDeleteProgram(shaderProgram);
    if (texture) glDeleteTextures(1, &texture);
    if (vbo) glDeleteBuffers(1, &vbo);
    if (vao) glDeleteVertexArrays(1, &vao);
}

bool CanvasOverlayButton::initGL()
{
    // Simple textured quad shader (orthographic)
    const char* vertSrc = R"(
        #version 330 core
        layout(location = 0) in vec2 aPos;
        layout(location = 1) in vec2 aTexCoord;

        out vec2 TexCoord;

        uniform vec2 uScreenSize;
        uniform vec2 uPos;
        uniform vec2 uSize;

        void main()
        {
            // Convert pos to normalized device coords (-1 to 1)
            vec2 pos = aPos * uSize + uPos;
            vec2 ndc = pos / uScreenSize * 2.0 - 1.0;
            ndc.y = -ndc.y; // invert y for OpenGL coords

            gl_Position = vec4(ndc, 0.0, 1.0);
            TexCoord = aTexCoord;
        }
    )";

    const char* fragSrc = R"(
        #version 330 core
        in vec2 TexCoord;
        out vec4 FragColor;
        uniform sampler2D uTexture;
        void main()
        {
            FragColor = texture(uTexture, TexCoord);
            if (FragColor.a < 0.1)
                discard; // discard transparent pixels for better blending
        }
    )";

    shaderProgram = linkProgram(vertSrc, fragSrc);
    if (!shaderProgram) {
        std::cerr << "Failed to create shader program for button" << std::endl;
        return false;
    }

    // Quad vertices: position(x,y), texCoord(u,v)
    float vertices[] = {
        0.0f, 0.0f, 0.0f, 0.0f, // bottom-left
        1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
        1.0f, 1.0f, 1.0f, 1.0f, // top-right
        0.0f, 1.0f, 0.0f, 1.0f  // top-left
    };

    unsigned int indices[] = { 0,1,2, 2,3,0 };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    GLuint ebo;
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // pos attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texcoord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    glDeleteBuffers(1, &ebo); // EBO data is stored in VAO

    // Load texture (set your PNG path here)
    if (!loadTexture("icon.png")) {
        std::cerr << "Failed to load button texture" << std::endl;
        return false;
    }

    return true;
}

void CanvasOverlayButton::draw(int windowWidth, int windowHeight)
{
    glUseProgram(shaderProgram);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(shaderProgram, "uTexture"), 0);

    glUniform2f(glGetUniformLocation(shaderProgram, "uScreenSize"), (float)windowWidth, (float)windowHeight);
    glUniform2f(glGetUniformLocation(shaderProgram, "uPos"), (float)posX, (float)posY);
    glUniform2f(glGetUniformLocation(shaderProgram, "uSize"), (float)width, (float)height);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glUseProgram(0);
}

bool CanvasOverlayButton::hitTest(int mouseX, int mouseY) const
{
    // Mouse y is top-left origin, OpenGL is bottom-left origin, so we assume mouse y is from top-left
    // If your mouse coords differ, adjust accordingly
    if (mouseX >= posX && mouseX <= posX + width &&
        mouseY >= posY && mouseY <= posY + height) {
        return true;
    }
    return false;
}

bool CanvasOverlayButton::loadTexture(const std::string& filePath)
{
    wxImage img;
    if (!img.LoadFile(filePath, wxBITMAP_TYPE_PNG)) {
        std::cerr << "Failed to load image: " << filePath << std::endl;
        return false;
    }

    if (!img.HasAlpha()) {
        img.InitAlpha();
    }

    img = img.Mirror(false);

    int width = img.GetWidth();
    int height = img.GetHeight();

    unsigned char* rgb = img.GetData();
    unsigned char* alpha = img.GetAlpha();

    if (!rgb || !alpha) {
        std::cerr << "Image missing RGB or Alpha data." << std::endl;
        return false;
    }

    // RGBA buffer oluştur
    std::vector<unsigned char> rgbaData(width * height * 4);
    for (int i = 0; i < width * height; ++i) {
        rgbaData[i * 4 + 0] = rgb[i * 3 + 0]; // R
        rgbaData[i * 4 + 1] = rgb[i * 3 + 1]; // G
        rgbaData[i * 4 + 2] = rgb[i * 3 + 2]; // B
        rgbaData[i * 4 + 3] = alpha[i];       // A
    }

    // Texture oluştur
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, rgbaData.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}

void CanvasOverlayButton::setPosition(int x, int y) {
    posX = x;
    posY = y;
}

GLuint CanvasOverlayButton::compileShader(GLenum type, const char* src)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader compilation failed:\n" << infoLog << std::endl;
        return 0;
    }
    return shader;
}

GLuint CanvasOverlayButton::linkProgram(const char* vertSrc, const char* fragSrc)
{
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertSrc);
    if (!vertexShader) return 0;

    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragSrc);
    if (!fragmentShader) {
        glDeleteShader(vertexShader);
        return 0;
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "Program linking failed:\n" << infoLog << std::endl;
        glDeleteProgram(program);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}
