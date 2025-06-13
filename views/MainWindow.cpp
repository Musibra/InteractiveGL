//
// Created by Mustafa İbrahim on 6/12/2025.
//

#include "MainWindow.h"


MainWindow::MainWindow(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
{
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

    canvas = new Canvas(this);
    canvas->SetMinSize(wxSize(600, -1));

    controlPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, -1));
    controlPanel->SetBackgroundColour(*wxLIGHT_GREY);

    wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);

    // Rotation label
    rotationLabel = new wxStaticText(controlPanel, wxID_ANY, wxString::Format("Rotation: 0\u00B0"));


    // Slider: 0–360 derece
    slider = new wxSlider(controlPanel, wxID_ANY, 0, 0, 360);

    // Checkbox
    checkbox = new wxCheckBox(controlPanel, wxID_ANY, "Show Triangle");

    // Add controls to panel
    panelSizer->Add(rotationLabel, 0, wxALL, 10);
    panelSizer->Add(slider, 0, wxALL | wxEXPAND, 10);
    panelSizer->Add(checkbox, 0, wxALL, 10);
    controlPanel->SetSizer(panelSizer);
    controlPanel->Hide();

    // Layout
    sizer->Add(canvas, 1, wxEXPAND);
    sizer->Add(controlPanel, 0, wxEXPAND);
    SetSizer(sizer);

    // Events
    slider->Bind(wxEVT_SLIDER, &MainWindow::OnSliderChanged, this);
    checkbox->Bind(wxEVT_CHECKBOX, &MainWindow::OnCheckBoxChanged, this);
    Bind(wxEVT_BUTTON, &MainWindow::OnOverlayButtonClicked, this, wxID_HIGHEST + 1);

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

void MainWindow::OnSliderChanged(wxCommandEvent& event) {
    int value = slider->GetValue();

    wxString text = wxString::Format("Rotation: %d\u00B0", value);
    rotationLabel->SetLabel(text);

    canvas->rotateObjectAroundZAxis(static_cast<float>(value));
    canvas->Refresh();
}

void MainWindow::OnCheckBoxChanged(wxCommandEvent& event) {

    canvas->Refresh();
}
