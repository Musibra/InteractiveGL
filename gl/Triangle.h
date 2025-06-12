//
// Created by Mustafa İbrahim on 6/12/2025.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H


#include <glad/glad.h>
#include <vector>

class Triangle {
public:
    Triangle();
    ~Triangle();

    void initGL();
    void draw();

private:
    GLuint shaderProgram = 0;
    GLuint vao = 0;
    GLuint vbo = 0;

    std::vector<float> vBuffer;

    GLuint compileShader(GLenum type, const char* src);
    GLuint linkProgram(const char* vertSrc, const char* fragSrc);
};

#endif //TRIANGLE_H
