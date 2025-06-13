#include "Triangle.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

Triangle::Triangle() {
    vBuffer = {
        //  x     y     z     r     g     b
         0.0f,  0.5f, 0.0f,  0.7f, 0.5f, 0.3f,
        -0.5f, -0.5f, 0.0f,  0.7f, 0.5f, 0.3f,
         0.5f, -0.5f, 0.0f,  0.7f, 0.5f, 0.3f,
    };
    initGL();
}

Triangle::~Triangle() {
    glDeleteProgram(shaderProgram);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Triangle::initGL() {
    const char* vertSrc = R"(
        #version 330 core
        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec3 aColor;

        uniform mat4 u_ModelMatrix;
        uniform mat4 u_ProjectionMatrix;
        uniform mat4 u_ViewMatrix;
        out vec3 ourColor;

        void main()
        {
            vec4 newPos = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * vec4(aPos, 1.0f);
            gl_Position = newPos;
            ourColor = aColor;
        }
    )";

    const char* fragSrc = R"(
        #version 330 core
        out vec4 FragColor;
        in vec3 ourColor;

        void main()
        {
            FragColor = vec4(ourColor.r, ourColor.g, ourColor.b, 1.0f);
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

    // Pozisyon: 3 float (vec3)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Renk: 3 float (vec3)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Triangle::draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) {
    glUseProgram(shaderProgram);

    GLint modelLoc = glGetUniformLocation(shaderProgram, "u_ModelMatrix");
    GLint viewLoc = glGetUniformLocation(shaderProgram, "u_ViewMatrix");
    GLint projLoc = glGetUniformLocation(shaderProgram, "u_ProjectionMatrix");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    glUseProgram(0);
}


GLuint Triangle::compileShader(GLenum type, const char* src) {
    GLuint shader = glCreateShader(type);
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

GLuint Triangle::linkProgram(const char* vertSrc, const char* fragSrc) {
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
