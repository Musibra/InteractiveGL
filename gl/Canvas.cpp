//
// Created by Mustafa İbrahim on 6/12/2025.
//

#include "Canvas.h"

wxBEGIN_EVENT_TABLE(Canvas, wxGLCanvas)
    EVT_PAINT(Canvas::OnPaint)
    EVT_SIZE(Canvas::OnResize)
    EVT_LEFT_DOWN(Canvas::OnMouse)
wxEND_EVENT_TABLE()

Canvas::Canvas(wxWindow* parent)
    : wxGLCanvas(parent, wxID_ANY, Constants::OpenGL::attribs), context(new wxGLContext(this))
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
    this->overlayButton = std::make_shared<CanvasOverlayButton>(10, 10, 24, 24);
    if (!this->overlayButton->initGL()) {
        std::cerr << "Failed to initialize overlay button!" << std::endl;
        return;
    }



    // Butonun ekran üst sağda, 100x100 px olacak şekilde konumu
    wxSize size = GetSize();
    buttonRect = wxRect(size.x - 110, 10, 100, 100);
}


void Canvas::OnPaint(wxPaintEvent& WXUNUSED(event)) {
    wxPaintDC dc(this);
    SetCurrent(*context);

    glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    background->draw();
    triangle->draw();
    overlayButton->draw(GetSize().x, GetSize().y);

    SwapBuffers();
}

void Canvas::OnResize(wxSizeEvent& event) {
    wxSize size = event.GetSize();
    SetCurrent(*context);
    glViewport(0, 0, size.x, size.y);

    int buttonWidth = 24;
    int buttonHeight = 24;

    int buttonX = size.x - buttonWidth - 10;
    int buttonY = 10;

    buttonRect = wxRect(buttonX, buttonY, buttonWidth, buttonHeight);
    overlayButton->setPosition(buttonX, buttonY);

    Refresh();
}

void Canvas::setButtonCallback(std::function<void()> cb) {
    onButtonClick = cb;
}

void Canvas::OnMouse(wxMouseEvent& event) {
    wxPoint pos = event.GetPosition();

    if (buttonRect.Contains(pos)) {
        if (onButtonClick) {
            onButtonClick();
        }
    }
}
