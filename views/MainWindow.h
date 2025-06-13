//
// Created by Mustafa İbrahim on 6/12/2025.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <wx/wx.h>
#include <wx/checkbox.h>
#include "Canvas.h"

class MainWindow : public wxFrame {
public:
    explicit MainWindow(const wxString& title);
    ~MainWindow() override = default;

private:
    Canvas* canvas;
    wxPanel* controlPanel;
    wxSlider* rotationSlider;
    wxSlider* scaleSlider;
    wxCheckBox* checkbox;
    wxStaticText* rotationLabel;
    wxStaticText* scaleLabel;
    bool panelVisible = false;

    void ToggleControlPanel();
    void OnOverlayButtonClicked(wxCommandEvent& event);
    void OnRotationSliderChanged(wxCommandEvent& event);
    void OnCheckBoxChanged(wxCommandEvent& event);
    void OnScaleSliderChanged(wxCommandEvent& event);
};
#endif //MAINWINDOW_H
