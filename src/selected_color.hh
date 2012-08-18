#ifndef SELECTED_COLOR_H
#define SELECTED_COLOR_H

#include <wx/wx.h>
#include <opencv2/opencv.hpp>

class SelectedColor : public wxPanel {
public:
    SelectedColor(wxWindow *parent);
    void set_color(cv::Scalar &color);

private:
    wxPanel *color_preview;
};

#endif /* SELECTED_COLOR_H */
