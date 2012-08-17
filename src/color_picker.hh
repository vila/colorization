#ifndef COLOR_PICKER_H
#define COLOR_PICKER_H

#include <wx/wx.h>
#include <opencv2/opencv.hpp>
#include <vector>


class ColorPicker : public wxPanel {
public:
    ColorPicker(wxWindow *parent);

    void set_luminance(int y);
    void draw_now();

private:
    void mouse_event(wxMouseEvent &event);
    void update_gamut();
    void paint_event(wxPaintEvent &event);
    void render(wxDC &dc);

private:
    int y;
    int u;
    int v;
    std::vector<cv::Mat> cache;

    cv::Mat gamut;
    wxBitmap bitmap;
};



#endif /* COLOR_PICKER_H */
