#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "ShaderLoader.h"

class Triangle {
public:
    Triangle();
    ~Triangle();

    void draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) const;

private:
    std::vector<float> vBuffer;
    GLuint vao{}, vbo{}, shaderProgram{};

    void initGL();
    static GLuint compileShader(GLenum type, const char* src);
    static GLuint linkProgram(const char* vertSrc, const char* fragSrc);
};

#endif // TRIANGLE_H
