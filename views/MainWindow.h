//
// Created by Mustafa İbrahim on 6/12/2025.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <wx/wx.h>
#include <wx/slider.h>
#include <wx/checkbox.h>
#include "Canvas.h"

class MainWindow : public wxFrame {
public:
    MainWindow(const wxString& title);

private:
    Canvas* canvas;
    wxPanel* controlPanel;
    wxSlider* slider;
    wxCheckBox* checkbox;
    wxStaticText* rotationLabel;
    bool panelVisible = false;

    void ToggleControlPanel();
    void OnOverlayButtonClicked(wxCommandEvent& event);
    void OnSliderChanged(wxCommandEvent& event);
    void OnCheckBoxChanged(wxCommandEvent& event);
};
#endif //MAINWINDOW_H
