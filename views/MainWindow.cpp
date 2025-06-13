//
// Created by Mustafa İbrahim on 6/12/2025.
//

#include "MainWindow.h"


MainWindow::MainWindow(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)) {
    auto* sizer = new wxBoxSizer(wxHORIZONTAL);

    canvas = new Canvas(this);
    canvas->SetMinSize(wxSize(600, -1));

    controlPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, -1));
    controlPanel->SetBackgroundColour(*wxLIGHT_GREY);

    auto panelSizer = new wxBoxSizer(wxVERTICAL);

    // Rotation label
    rotationLabel = new wxStaticText(controlPanel, wxID_ANY, wxString::Format("Rotation: 0\u00B0"));

    // Slider: 0–360 degree
    rotationSlider = new wxSlider(controlPanel, wxID_ANY, 0, 0, 360);

    // Scale slider: 0.1 to 2.0
    scaleSlider = new wxSlider(controlPanel, wxID_ANY, 10, 1, 20);
    scaleSlider->SetValue(10);

    // Scale label
    scaleLabel = new wxStaticText(controlPanel, wxID_ANY, wxString::Format("Scale: %.1f", 1.0f));

    // Checkbox
    checkbox = new wxCheckBox(controlPanel, wxID_ANY, "Show Triangle");
    checkbox->SetValue(true); // Default to checked

    // Add controls to panel
    panelSizer->Add(rotationLabel, 0, wxALL, 10);
    panelSizer->Add(rotationSlider, 0, wxALL | wxEXPAND, 10);
    panelSizer->Add(scaleLabel, 0, wxALL, 10);
    panelSizer->Add(scaleSlider, 0, wxALL | wxEXPAND, 10);
    panelSizer->Add(checkbox, 0, wxALL, 10);
    controlPanel->SetSizer(panelSizer);
    controlPanel->Hide();

    // Layout
    sizer->Add(canvas, 1, wxEXPAND);
    sizer->Add(controlPanel, 0, wxEXPAND);
    SetSizer(sizer);

    // Events
    rotationSlider->Bind(wxEVT_SLIDER, &MainWindow::OnRotationSliderChanged, this);
    checkbox->Bind(wxEVT_CHECKBOX, &MainWindow::OnCheckBoxChanged, this);
    Bind(wxEVT_BUTTON, &MainWindow::OnOverlayButtonClicked, this, wxID_HIGHEST + 1);
    scaleSlider->Bind(wxEVT_SLIDER, &MainWindow::OnScaleSliderChanged, this);

    canvas->setButtonCallback([this]() {
        wxCommandEvent evt(wxEVT_BUTTON, wxID_HIGHEST + 1);
        wxPostEvent(this, evt);
    });
}

void MainWindow::ToggleControlPanel() {
    panelVisible = !panelVisible;
    controlPanel->Show(panelVisible);
    Layout();
}

void MainWindow::OnOverlayButtonClicked(wxCommandEvent&) {
    ToggleControlPanel();
}

void MainWindow::OnRotationSliderChanged(wxCommandEvent& event) {
    int value = rotationSlider->GetValue();

    wxString text = wxString::Format("Rotation: %d\u00B0", value);
    rotationLabel->SetLabel(text);

    canvas->rotateObjectAroundZAxis(static_cast<float>(value));
    canvas->Refresh();
}

void MainWindow::OnCheckBoxChanged(wxCommandEvent& event) {
    bool showTriangle = checkbox->IsChecked();
    canvas->setShowTriangle(showTriangle);
    canvas->Refresh();
}

void MainWindow::OnScaleSliderChanged(wxCommandEvent& event) {
    int value = scaleSlider->GetValue();
    float scale = static_cast<float>(value) / 10.0f; // Convert to 0.1 to 2.0 range
    scaleLabel->SetLabel(wxString::Format("Scale: %.1f", scale));
    canvas->setScale(scale);
    canvas->Refresh();
}
