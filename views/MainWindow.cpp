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

    // Kontrol paneli
    controlPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, -1));
    controlPanel->SetBackgroundColour(*wxLIGHT_GREY);

    wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
    slider = new wxSlider(controlPanel, wxID_ANY, 0, 0, 100);
    checkbox = new wxCheckBox(controlPanel, wxID_ANY, "Show Triangle");

    panelSizer->Add(slider, 0, wxALL | wxEXPAND, 10);
    panelSizer->Add(checkbox, 0, wxALL, 10);
    controlPanel->SetSizer(panelSizer);

    controlPanel->Hide(); // Başlangıçta kapalı

    sizer->Add(canvas, 1, wxEXPAND);
    sizer->Add(controlPanel, 0, wxEXPAND);
    SetSizer(sizer);

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
    float rot = slider->GetValue() / 100.0f;
    canvas->Refresh();
}

void MainWindow::OnCheckBoxChanged(wxCommandEvent& event) {
    canvas->Refresh();
}
