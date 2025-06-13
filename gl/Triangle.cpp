#include "Triangle.h"

Triangle::Triangle()
    : vao(0), vbo(0), locModel(-1), locView(-1), locProj(-1) {
    vBuffer = {
        //  x     y     z     r     g     b
        0.0f, 0.5f, 0.0f, 0.7f, 0.5f, 0.3f,
        -0.5f, -0.5f, 0.0f, 0.7f, 0.5f, 0.3f,
        0.5f, -0.5f, 0.0f, 0.7f, 0.5f, 0.3f,
    };
    if (!initGL()) {
        std::cerr << "Failed to initialize Triangle GL resources.\n";
    }
}

Triangle::~Triangle() {
    if (shaderProgram) glDeleteProgram(shaderProgram);
    if (vbo) glDeleteBuffers(1, &vbo);
    if (vao) glDeleteVertexArrays(1, &vao);
}

bool  Triangle::initGL() {
    std::string vertSrc = ShaderLoader::getShaderCode("shaders/Triangle.vert");
    std::string fragSrc = ShaderLoader::getShaderCode("shaders/Triangle.frag");

    shaderProgram = linkProgram(vertSrc.c_str(), fragSrc.c_str());
    if (!shaderProgram) {
        std::cerr << "Shader program failed to compile/link!\n";
        return false;
    }

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vBuffer.size() * sizeof(float), vBuffer.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    locModel = glGetUniformLocation(shaderProgram, "u_ModelMatrix");
    locView = glGetUniformLocation(shaderProgram, "u_ViewMatrix");
    locProj = glGetUniformLocation(shaderProgram, "u_ProjectionMatrix");

    if(locModel == -1 || locView == -1 || locProj == -1) {
        std::cerr << "Warning: could not get uniform locations\n";
    }
    return true;
}

void Triangle::draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) const {
    if (!shaderProgram || !vao) return;

    glUseProgram(shaderProgram);
    glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(locView, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(locProj, 1, GL_FALSE, glm::value_ptr(projection));

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

GLuint Triangle::linkProgram(const char* vertSrc, const char* fragSrc) {
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
