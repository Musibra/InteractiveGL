#include <glad/glad.h>
#include "Background.h"

Background::Background() {
    // Vertex + color verisini başta tanımla
    vBuffer = {
        -1.f, -1.f, 0.00f, 0.10f, 0.15f,
        -1.f,  1.f, 0.03f, 0.21f, 0.26f,
         1.f, -1.f, 0.00f, 0.12f, 0.18f,
         1.f,  1.f, 0.06f, 0.26f, 0.30f
    };

    initGL();
}

Background::~Background() {
    glDeleteProgram(shaderProgram);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Background::setBackGroundColorWhite() {
    color[0] = color[1] = color[2] = 1.0f;
}

void Background::setBackGroundColorDark() {
    color[0] = color[1] = color[2] = 0.1f;
}

void Background::initGL() {
    // TODO: load shaders from files
    const char* vertSrc = R"(
        #version 330 core
        layout(location = 0) in vec2 vertexPosition;
        layout(location = 1) in vec3 vertexColor;

        out vec3 fragColor;

        void main() {
            gl_Position = vec4(vertexPosition, 0.0, 1.0);
            fragColor = vertexColor;
        }
    )";

    const char* fragSrc = R"(
        #version 330 core
        in vec3 fragColor;
        out vec4 outColor;

        void main() {
            outColor = vec4(fragColor, 1.0);
        }
    )";

    shaderProgram = linkProgram(vertSrc, fragSrc);
    if (!shaderProgram) {
        std::cerr << "Shader program failed to compile/link!" << std::endl;
        return;
    }

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vBuffer.size() * sizeof(float), vBuffer.data(), GL_STATIC_DRAW);

    // position attribute: location 0, 2 floats, stride 5 floats
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute: location 1, 3 floats, stride 5 floats, offset 2 floats
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Cleanup
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Background::draw() {
    glUseProgram(shaderProgram);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);

    glUseProgram(0);
}

GLuint Background::compileShader(GLenum type, const char* src) {
    GLuint shader = glCreateShader(type);
    if (shader == 0) {
        std::cerr << "Error: Failed to create shader." << std::endl;
        return 0;
    }

    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint status = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        GLint logLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> buffer(logLength > 0 ? logLength : 512);
        glGetShaderInfoLog(shader, buffer.size(), nullptr, buffer.data());
        std::cerr << "Shader compile error: " << buffer.data() << std::endl;
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

GLuint Background::linkProgram(const char* vertSrc, const char* fragSrc) {
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

    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        char buffer[512];
        glGetProgramInfoLog(program, 512, nullptr, buffer);
        std::cerr << "Program link error: " << buffer << std::endl;
        glDeleteProgram(program);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}
