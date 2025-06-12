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


class Canvas : public wxGLCanvas {
public:
    Canvas(wxWindow* parent);
    std::function<void()> onButtonClick;
    void setButtonCallback(std::function<void()> cb);

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

    wxDECLARE_EVENT_TABLE();
};

#endif //CANVAS_H
