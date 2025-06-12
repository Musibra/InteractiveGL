#include <wx/wx.h>
#include "MainWindow.h"

class App : public wxApp {
public:
    bool OnInit() override {
        auto mainWindow = new MainWindow("Interactive GL");
        mainWindow->Show();
        return true;
    }
};

wxIMPLEMENT_APP(App);
