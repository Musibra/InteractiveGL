//
// Created by Mustafa İbrahim on 6/12/2025.
//

#ifndef CANVAS_H
#define CANVAS_H

#include "Background.h"
#include "Triangle.h"
#include "CanvasOverlayButton.h"
#include <wx/glcanvas.h>
#include <wx/dcclient.h>
#include <memory>
#include "constants.h"
#include <wx/image.h>
#include "Camera.h"


class Canvas : public wxGLCanvas {
public:
    Canvas(wxWindow* parent);
    std::function<void()> onButtonClick;
    void setButtonCallback(std::function<void()> cb);

    void rotateObjectAroundZAxis(float angle);

private:
    wxGLContext* context;
    std::unique_ptr<Background> background;
    std::shared_ptr<Triangle> triangle;
    std::shared_ptr<CanvasOverlayButton> overlayButton;

    GLuint buttonTexture = 0;
    wxRect buttonRect;

    void drawButton();

    void OnPaint(wxPaintEvent& event);
    void OnResize(wxSizeEvent& event);
    void OnMouse(wxMouseEvent& event);

    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    std::shared_ptr<Camera> camera;
    float zOffset{-2.0f}; // Initial Z offset for the model

    wxDECLARE_EVENT_TABLE();
};

#endif //CANVAS_H
