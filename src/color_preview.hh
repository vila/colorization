#ifndef COLOR_PREVIEW_H
#define COLOR_PREVIEW_H

#include <wx/wx.h>
#include <opencv2/opencv.hpp>
#include <vector>

class ColorPreview : public wxPanel {
public:
    ColorPreview(wxWindow *parent);

    void draw_now();
    void set_preview_image(cv::Mat &m);
    void set_color(cv::Scalar color);


    static const int PREVIEW_IMAGE_SIZE = 64;
    static const int PREVIEW_SIZE = 256;


private:
    void paint_event(wxPaintEvent &event);
    void render(wxDC &dc);
    void update_preview();

private:
    cv::Mat preview_image;
    int u,v;
    wxBitmap bitmap;
};

#endif /* COLOR_PREVIEW_H */
