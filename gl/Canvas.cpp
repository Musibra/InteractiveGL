//
// Created by Mustafa İbrahim on 6/12/2025.
//

#include "Canvas.h"

wxBEGIN_EVENT_TABLE(Canvas, wxGLCanvas)
    EVT_PAINT(Canvas::OnPaint)
    EVT_SIZE(Canvas::OnResize)
wxEND_EVENT_TABLE()

Canvas::Canvas(wxWindow* parent)
    : wxGLCanvas(parent, wxID_ANY, nullptr), context(new wxGLContext(this))
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    SetCurrent(*context);

    if (!gladLoadGL()) {
        std::cerr << "glad failed to initialize!" << std::endl;
        return;
    }

    this->background = std::make_unique<Background>();
    this->background->initGL();
    this->triangle = std::make_shared<Triangle>();

}

void Canvas::OnPaint(wxPaintEvent& WXUNUSED(event)) {
    wxPaintDC dc(this);
    SetCurrent(*context);

    glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    background->draw();
    triangle->draw();

    SwapBuffers();
}

void Canvas::OnResize(wxSizeEvent& event) {
    wxSize size = event.GetSize();
    SetCurrent(*context);
    glViewport(0, 0, size.x, size.y);
    Refresh();
}