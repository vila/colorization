#ifndef COLOR_PICKER_H
#define COLOR_PICKER_H

#include "selected_color.hh"
#include "color_preview.hh"

#include <wx/wx.h>
#include <opencv2/opencv.hpp>
#include <vector>


class ColorPicker : public wxPanel {
public:
    ColorPicker(wxWindow *parent, SelectedColor *sc, ColorPreview *cp);

    void set_luminance(int y);
    void draw_now();
    cv::Scalar get_color();

private:
    void mouse_event(wxMouseEvent &event);
    void update_gamut();
    void paint_event(wxPaintEvent &event);
    void render(wxDC &dc);
    void color_updated();

private:
    // for callback when color updates
    SelectedColor *selected_color;
    ColorPreview *color_preview;

    cv::Scalar color;
    std::vector<cv::Mat> cache;

    cv::Mat gamut;
    wxBitmap bitmap;
};



#endif /* COLOR_PICKER_H */
