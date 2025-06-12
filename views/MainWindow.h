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

private:
    Canvas* canvas;

};


#endif //MAINWINDOW_H
