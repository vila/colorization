#ifndef MAIN_FRAME_H
#define MAIN_FRAME_H

#include "color_picker.hh"

#include <wx/wx.h>
#include <opencv2/opencv.hpp>

class MainFrame : public wxFrame
{
public:
    MainFrame();

private:
    ColorPicker *color_picker;
    cv::Mat luminance;
};

#endif /* MAIN_FRAME_H */
