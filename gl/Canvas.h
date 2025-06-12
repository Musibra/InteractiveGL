//
// Created by Mustafa İbrahim on 6/12/2025.
//

#ifndef CANVAS_H
#define CANVAS_H
#include "Background.h"
#include "Triangle.h"
#include <wx/glcanvas.h>
#include <wx/dcclient.h>
#include <memory>


class Canvas : public wxGLCanvas {
public:
    explicit Canvas(wxWindow* parent);

private:

    void OnPaint(wxPaintEvent& event);
    void OnResize(wxSizeEvent& event);
    std::unique_ptr<wxGLContext> context;
    std::unique_ptr<Background> background;
    std::shared_ptr<Triangle> triangle;

    DECLARE_EVENT_TABLE()
};


#endif //CANVAS_H
