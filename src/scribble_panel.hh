#ifndef SCRIBBLE_PANEL_H
#define SCRIBBLE_PANEL_H

#include "color_preview.hh"
#include "color_picker.hh"

#include <wx/wx.h>
#include <opencv2/opencv.hpp>
#include <vector>


class ScribblePanel : public wxScrolledWindow {
public:
    ScribblePanel(wxWindow *parent, ColorPicker *picker, ColorPreview *preview);

    void set_image(cv::Mat image, bool keep_uv = false);
    void draw_now();

private:
    void paint_event(wxPaintEvent &event);
    void mouse_event(wxMouseEvent &event);
    void update_bitmap(cv::Rect rect = cv::Rect());
    void render(wxDC &dc);

private:
    ColorPicker *color_picker;
    ColorPreview *color_preview;

    wxPanel *image_panel;
    std::vector<cv::Mat> image_yuv;
    cv::Mat cache;
    wxBitmap bitmap;
};


#endif /* SCRIBBLE_PANEL_H */
