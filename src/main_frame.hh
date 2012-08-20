#ifndef MAIN_FRAME_H
#define MAIN_FRAME_H

#include "color_picker.hh"
#include "color_preview.hh"
#include "selected_color.hh"
#include "scribble_panel.hh"


#include <wx/wx.h>
#include <opencv2/opencv.hpp>

class MainFrame : public wxFrame
{
public:
    MainFrame();

    void open_file(wxCommandEvent &event);
    void save_file(wxCommandEvent &event);

private:
    ScribblePanel *scribble_panel;
    ColorPicker *color_picker;
    ColorPreview *color_preview;
    SelectedColor *selected_color;
    cv::Mat luminance;
};

#endif /* MAIN_FRAME_H */
