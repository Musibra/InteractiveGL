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
    : wxGLCanvas(parent, wxID_ANY, Constants::OpenGL::attribs), context(new wxGLContext(this)) {
    wxWindowBase::SetBackgroundStyle(wxBG_STYLE_PAINT);
    SetCurrent(*context);

    if(!gladLoadGL()) {
        std::cerr << "glad failed to initialize!" << std::endl;
        return;
    }

    // create camera
    camera = std::make_shared<Camera>();
    // set up projection matrix
    projectionMatrix = glm::perspective(
        glm::radians(45.0f), // 45 degrees field of view
        static_cast<float>(GetSize().x) / static_cast<float>(GetSize().y), // aspect ratio
        0.1f, // near plane
        100.0f // far plane
    );
    // set up view matrix
    viewMatrix = glm::mat4(1.0f);
    // set up model matrix
    modelMatrix = glm::mat4(1.0f); // Identity matrix for initial state
    modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, zOffset));

    this->background = std::make_unique<Background>();
    this->background->initGL();
    this->triangle = std::make_shared<Triangle>();

    this->overlayButton = std::make_shared<CanvasOverlayButton>(10, 10, 24, 24);
    if(!this->overlayButton->initGL()) {
        std::cerr << "Failed to initialize overlay button!" << std::endl;
        return;
    }

    const wxSize size = GetSize();
    buttonRect = wxRect(
        size.x - Constants::OverlayButton::BUTTON_OFFSET_X - Constants::OverlayButton::BUTTON_WIDTH,
        Constants::OverlayButton::BUTTON_OFFSET_Y,
        Constants::OverlayButton::BUTTON_WIDTH,
        Constants::OverlayButton::BUTTON_HEIGHT
    );
}

void Canvas::OnPaint(wxPaintEvent& WXUNUSED(event)) {
    wxPaintDC dc(this);
    SetCurrent(*context);
    glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    background->draw();
    if(showTriangle) {
        triangle->draw(modelMatrix, viewMatrix, projectionMatrix);
    }
    overlayButton->draw(GetSize().x, GetSize().y);

    SwapBuffers();
}

void Canvas::OnResize(wxSizeEvent& event) {
    const wxSize size = event.GetSize();
    SetCurrent(*context);
    glViewport(0, 0, size.x, size.y);

    // update the projection matrix based on the new size
    float aspect = static_cast<float>(size.x) / static_cast<float>(size.y);
    projectionMatrix = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);

    // update the button position
    buttonRect = wxRect(size.x - Constants::OverlayButton::BUTTON_OFFSET_X - Constants::OverlayButton::BUTTON_WIDTH,
                        Constants::OverlayButton::BUTTON_OFFSET_Y,
                        Constants::OverlayButton::BUTTON_WIDTH,
                        Constants::OverlayButton::BUTTON_HEIGHT);
    overlayButton->setPosition(
        size.x - Constants::OverlayButton::BUTTON_OFFSET_X - Constants::OverlayButton::BUTTON_WIDTH,
        Constants::OverlayButton::BUTTON_OFFSET_Y);

    Refresh();
}

void Canvas::setButtonCallback(std::function<void()> cb) {
    onButtonClick = std::move(cb);
}

void Canvas::rotateObjectAroundZAxis(float angle) {
    currentAngle = angle;
    updateModelMatrix();
}

void Canvas::setScale(const float scale) {
    currentScale = scale;
    updateModelMatrix();
}

void Canvas::updateModelMatrix() {
    modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, zOffset));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(currentAngle), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(currentScale, currentScale, currentScale));
}

void Canvas::setShowTriangle(bool show) {
    showTriangle = show;
    Refresh();
}

void Canvas::OnMouse(wxMouseEvent& event) {
    if(const wxPoint pos = event.GetPosition(); buttonRect.Contains(pos) && onButtonClick) {
        onButtonClick();
        overlayButton->toggle();
    }
}
