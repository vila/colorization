#include "scribble_panel.hh"
#include "color_preview.hh"
#include "color_picker.hh"

#include <wx/wx.h>
#include <opencv2/opencv.hpp>

#include <iostream>


ScribblePanel::ScribblePanel(wxWindow *parent, ColorPicker *picker, ColorPreview *preview)
    : wxScrolledWindow(parent, -1), color_picker(picker), color_preview(preview)
{
    image_panel = new wxPanel(this, -1, wxPoint(-1,1), wxSize(250,250));
    image_panel->SetBackgroundColour(*wxBLACK);

    image_panel->Connect(wxID_ANY, wxEVT_PAINT,
                         wxPaintEventHandler(ScribblePanel::paint_event), NULL, this);
    image_panel->Connect(wxID_ANY, wxEVT_LEFT_UP,
                         wxMouseEventHandler(ScribblePanel::mouse_event),  NULL, this);
    image_panel->Connect(wxID_ANY, wxEVT_RIGHT_UP,
                         wxMouseEventHandler(ScribblePanel::mouse_event),  NULL, this);
    cache.data = 0;
}

void ScribblePanel::set_image(cv::Mat image, bool keep_uv) {
    std::cout << "set_image()\n";
    CV_Assert(image.channels() == 1);
    CV_Assert(image.depth() == CV_8U);
    // TODO support the keep_uv flag with color images (for recoloring)

    image_yuv.clear();
    image_yuv.push_back(image.clone());
    image_yuv.push_back(cv::Mat(image.rows, image.cols, CV_8U, cv::Scalar(128)));
    image_yuv.push_back(cv::Mat(image.rows, image.cols, CV_8U, cv::Scalar(128)));
    // TODO possibly keep a mask of assigned pixels

    // update the scrolledwindow for the image size
    SetScrollbars(1, 1, image.cols, image.rows, 0, 0);
    image_panel->SetSize(-1,-1, image.cols, image.rows);

    update_bitmap();
}

void ScribblePanel::update_bitmap(cv::Rect rect) {
    cv::Mat src;
    if(rect.area() != 0) {
        std::vector<cv::Mat> tmp = {image_yuv[0](rect),
                                    image_yuv[1](rect),
                                    image_yuv[2](rect)};
        cv::merge(tmp,src);
        cv::Mat dst = cache(rect);
        cv::cvtColor(src, dst, CV_YCrCb2RGB);
    } else {
        cv::merge(image_yuv, src);
        cv::cvtColor(src, cache, CV_YCrCb2RGB);
    }

    bitmap = wxBitmap(wxImage(cache.cols, cache.rows, cache.data, true));
    image_panel->Refresh(false);
}

void ScribblePanel::render(wxDC &dc) {
    if(!cache.empty()) {
        dc.DrawBitmap(bitmap,0,0,false);
    } else {
        dc.SetPen(*wxRED_PEN);
        dc.DrawLine(0,0,100,100);
        dc.DrawLine(100,0,0,100);
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
    // TODO select preview on right click, draw on left click
    std::cout << "mouse event " << event.m_x << " " << event.m_y << "\n";
}
