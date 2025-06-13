#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Triangle {
public:
    Triangle();
    ~Triangle();

    void draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);

private:
    std::vector<float> vBuffer;
    GLuint vao, vbo, shaderProgram;

    void initGL();
    GLuint compileShader(GLenum type, const char* src);
    GLuint linkProgram(const char* vertSrc, const char* fragSrc);
};

#endif // TRIANGLE_H
