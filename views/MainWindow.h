//
// Created by Mustafa İbrahim on 6/12/2025.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Canvas.h"
#include <wx/wx.h>

class MainWindow : public wxFrame {
public:
    MainWindow(const wxString& title);

    void ToggleControlPanel();

private:
    Canvas* canvas;
    wxPanel* controlPanel;
    wxSlider* slider;
    wxCheckBox* checkbox;
    bool panelVisible = false;

    void OnSliderChanged(wxCommandEvent& event);
    void OnCheckBoxChanged(wxCommandEvent& event);
    void OnOverlayButtonClicked(wxCommandEvent& event);
};

#endif //MAINWINDOW_H
