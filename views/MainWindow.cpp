//
// Created by Mustafa İbrahim on 6/12/2025.
//

#include "MainWindow.h"

MainWindow::MainWindow(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
{
    canvas = new Canvas(this);  // güncellendi
}
