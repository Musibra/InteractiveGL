//
// Created by Mustafa İbrahim on 6/13/2025.
//

#ifndef CANVASOVERLAYBUTTON_H
#define CANVASOVERLAYBUTTON_H

#include <glad/glad.h>
#include <wx/glcanvas.h>
#include <string>
#include <iostream>
#include <vector>
#include <wx/image.h>

class CanvasOverlayButton {
public:
    CanvasOverlayButton(int x, int y, int width = 64, int height = 64);
    ~CanvasOverlayButton();

    bool initGL();
    void draw(int windowWidth, int windowHeight);
    bool hitTest(int mouseX, int mouseY) const;
    bool loadTexture(const std::string& filePath);
    void setPosition(int x, int y);
private:
    GLuint shaderProgram = 0;
    GLuint texture = 0;
    GLuint vao = 0, vbo = 0;

    int posX;
    int posY;
    int width;
    int height;

    GLuint compileShader(GLenum type, const char* src);
    GLuint linkProgram(const char* vertSrc, const char* fragSrc);
};




#endif //CANVASOVERLAYBUTTON_H
