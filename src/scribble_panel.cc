#include "scribble_panel.hh"
#include "color_preview.hh"
#include "color_picker.hh"
#include "misc.hh"

#include <wx/wx.h>
#include <opencv2/opencv.hpp>

#include <iostream>


ScribblePanel::ScribblePanel(wxWindow *parent, ColorPicker *picker, ColorPreview *preview)
    : wxScrolledWindow(parent, -1), color_picker(picker), color_preview(preview)
{
    image_panel = new wxPanel(this, -1, wxPoint(-1,1), wxSize(250,250));

    image_panel->Connect(wxID_ANY, wxEVT_PAINT,
                         wxPaintEventHandler(ScribblePanel::paint_event), NULL, this);
    image_panel->Connect(wxID_ANY, wxEVT_LEFT_DOWN,
                         wxMouseEventHandler(ScribblePanel::mouse_event),  NULL, this);
    image_panel->Connect(wxID_ANY, wxEVT_LEFT_UP,
                         wxMouseEventHandler(ScribblePanel::mouse_event),  NULL, this);
    image_panel->Connect(wxID_ANY, wxEVT_MOTION,
                         wxMouseEventHandler(ScribblePanel::mouse_event),  NULL, this);
    image_panel->Connect(wxID_ANY, wxEVT_RIGHT_UP,
                         wxMouseEventHandler(ScribblePanel::mouse_event),  NULL, this);

    draw_mode = DrawingMode::DRAWING;
}

void ScribblePanel::set_image(cv::Mat image, bool keep_uv) {
    CV_Assert(image.channels() == 1);
    CV_Assert(image.depth() == CV_8U);
    // TODO support the keep_uv flag with color images (for recoloring)


    img_y = image.clone();
    cv::cvtColor(img_y, img_rgb, CV_GRAY2RGB);

    int m = image.rows;
    int n = image.cols;
    img_mask = cv::Mat::zeros(m,n, CV_8U);

    // update the scrolledwindow for the image size
    SetScrollbars(1, 1, n, m, 0, 0);
    image_panel->SetSize(-1,-1, n, m);
    
    bitmap_dirty = true;
}

void ScribblePanel::update_bitmap() {
    bitmap_dirty = false;
    bitmap = wxBitmap(wxImage(img_rgb.cols, img_rgb.rows, img_rgb.data, true));
}

void ScribblePanel::render(wxDC &dc) {
    if(bitmap_dirty)
        update_bitmap();

    if(!img_rgb.empty()) {
        dc.DrawBitmap(bitmap,0,0,false);
    }
}

void ScribblePanel::draw_now() {
    wxClientDC dc(image_panel);
    render(dc);
}

void ScribblePanel::paint_event(wxPaintEvent &event) {
    wxPaintDC dc(image_panel);
    render(dc);
}

void ScribblePanel::mouse_event(wxMouseEvent &event) {
    if(img_rgb.empty())
        return;

    switch(draw_mode) {
    case DRAWING:
    case ERASING:
        if (event.LeftUp() || (event.LeftIsDown() && event.Dragging()))
            draw(event.m_x, event.m_y, draw_mode == ERASING);
        break;

    case COLOR_PICK:
        if(event.LeftUp())
            pick_color(event.m_x, event.m_y);
    }

    if(event.RightUp()) {
        // TODO: handle edge cases
        cv::Mat preview = img_y(cv::Rect(event.m_x-32, event.m_y-32,64,64));
        color_preview->set_preview_image(preview);       
        color_picker->set_luminance(img_y.at<uchar>(event.m_y, event.m_x));
    }
}


void ScribblePanel::draw(int x, int y, bool erase) {
    int bsize = 5;
    int bhalf = bsize/2;

    cv::Scalar color = erase ? cv::Scalar(0,128,128) : color_picker->get_color();
    cv::Rect brush(x-bhalf,y-bhalf,bsize,bsize);
    cv::Mat dst;

    cv::merge(std::vector<cv::Mat>({img_y(brush),
                    cv::Mat(bsize,bsize, CV_8UC1, cv::Scalar(color[1])),
                    cv::Mat(bsize,bsize, CV_8UC1, cv::Scalar(color[2])),}),dst);
    
    cv::cvtColor(dst, dst, CV_YCrCb2RGB);
    
    // update the rgb image and mark the bitmap as dirty

    img_mask(brush).setTo(erase ? 0 : 1);
    img_rgb(brush) = dst;
    bitmap_dirty = true;

    wxClientDC dc(image_panel);
    wxBitmap tmp(wxImage(dst.cols,dst.rows,dst.data,true));
    dc.DrawBitmap(tmp, x-bhalf, y-bhalf, false);
}

void ScribblePanel::pick_color(int x, int y) {
    // TODO
}


void ScribblePanel::update_drawing_mode(wxCommandEvent &event) {
    switch(event.GetId()) {
    case DRAWING:    draw_mode = DRAWING; break;
    case ERASING:    draw_mode = ERASING; break;
    case COLOR_PICK: draw_mode = COLOR_PICK; break;
    }
}
