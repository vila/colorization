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
    void update_drawing_mode(wxCommandEvent &event);

    cv::Mat get_rgb() const;
    cv::Mat get_mask() const;

    // These are used for IDs for the toolbar
    enum DrawingMode {
        DRAWING = 1,
        ERASING,
        COLOR_PICK
    };

private:
    void paint_event(wxPaintEvent &event);
    void mouse_event(wxMouseEvent &event);
    void update_bitmap();
    void render(wxDC &dc);

    void draw(int x, int y, bool erase = false);
    void pick_color(int x, int y);

private:
    ColorPicker *color_picker;
    ColorPreview *color_preview;
    wxPanel *image_panel;

    DrawingMode draw_mode;
    cv::Mat img_y;
    cv::Mat img_rgb;
    cv::Mat img_mask;
    bool bitmap_dirty;
    wxBitmap bitmap;
};


#endif /* SCRIBBLE_PANEL_H */
