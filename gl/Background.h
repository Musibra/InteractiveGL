//
// Created by Mustafa İbrahim on 6/12/2025.
//

#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <glad/glad.h>
#include <vector>
#include <iostream>


class Background {
public:
    Background();
    ~Background();

    void draw();
    void setBackGroundColorWhite();
    void setBackGroundColorDark();
    void initGL();

private:
    GLuint vao{}, vbo{};
    GLuint shaderProgram{};
    float color[3]{};
    std::vector<float> vBuffer;

    static GLuint compileShader(GLenum type, const char* src);

    static GLuint linkProgram(const char* vertSrc, const char* fragSrc);
};

#endif //BACKGROUND_H
