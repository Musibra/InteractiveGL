//
// Created by Mustafa İbrahim on 6/12/2025.
//

#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <glad/glad.h>
#include <vector>
#include <iostream>
#include "ShaderLoader.h"


class Background {
public:
    Background();
    ~Background();

    void draw() const;
    void initGL();

private:
    GLuint vao{}, vbo{};
    GLuint shaderProgram{};
    std::vector<float> vBuffer;

    static GLuint compileShader(GLenum type, const char* src);

    static GLuint linkProgram(const char* vertSrc, const char* fragSrc);
};

#endif //BACKGROUND_H
