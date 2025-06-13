#include "Background.h"

Background::Background() {
    vBuffer = {
        -1.f, -1.f, 0.00f, 0.10f, 0.15f,
        -1.f, 1.f, 0.03f, 0.21f, 0.26f,
        1.f, -1.f, 0.00f, 0.12f, 0.18f,
        1.f, 1.f, 0.06f, 0.26f, 0.30f
    };
    initGL();
}

Background::~Background() {
    glDeleteProgram(shaderProgram);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Background::initGL() {
    std::string vertSrc = ShaderLoader::getShaderCode("shaders/Background.vert");
    std::string fragSrc = ShaderLoader::getShaderCode("shaders/Background.frag");

    shaderProgram = linkProgram(vertSrc.c_str(), fragSrc.c_str());
    if(!shaderProgram) {
        std::cerr << "Shader program failed to compile/link!" << std::endl;
        return;
    }

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vBuffer.size() * sizeof(float), vBuffer.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Background::draw() const {
    glUseProgram(shaderProgram);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);

    glUseProgram(0);
}

GLuint Background::compileShader(GLenum type, const char* src) {
    GLuint shader = glCreateShader(type);
    if(shader == 0) {
        std::cerr << "Error: Failed to create shader." << std::endl;
        return 0;
    }

    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint status = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE) {
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
    if(!vertexShader) return 0;

    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragSrc);
    if(!fragmentShader) {
        glDeleteShader(vertexShader);
        return 0;
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if(status != GL_TRUE) {
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
