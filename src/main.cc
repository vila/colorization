#include "main.hh"
#include <wx/wx.h>
#include <opencv2/opencv.hpp>

#include "main_frame.hh"

#include <iostream>
#include <string>
using namespace std;


bool ColorizationApp::OnInit()
{
    MainFrame *frame = new MainFrame;
    frame->Show(true);
    SetTopWindow(frame);
    return true;
}
