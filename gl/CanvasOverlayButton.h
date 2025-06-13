//
// Created by Mustafa İbrahim on 6/13/2025.
//

#ifndef CANVASOVERLAYBUTTON_H
#define CANVASOVERLAYBUTTON_H

#include <glad/glad.h>
#include <string>
#include <iostream>
#include "ShaderLoader.h"
#include "CanvasOverlayButton.h"
#include <vector>
#include <wx/image.h>

class CanvasOverlayButton {
public:
    CanvasOverlayButton(int x, int y, int width_, int height_);
    ~CanvasOverlayButton();

    bool initGL();
    void draw(int windowWidth, int windowHeight);
    void setPosition(int x, int y);
    void toggle();
    [[nodiscard]] bool hitTest(int mouseX, int mouseY) const;
    void releaseResources();

private:
    int posX, posY;
    int width, height;

    GLuint vao = 0, vbo = 0;
    GLuint shaderProgram = 0;
    GLuint texture1 = 0, texture2 = 0;
    bool toggled = false;

    static bool loadTextureFromFile(const std::string& filePath, GLuint& outTexture);
    GLuint compileShader(GLenum type, const char* src);
    GLuint linkProgram(const char* vertSrc, const char* fragSrc);
};


#endif //CANVASOVERLAYBUTTON_H
