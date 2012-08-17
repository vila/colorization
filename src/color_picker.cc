#include "color_picker.hh"
#include "selected_color.hh"

#include <wx/wx.h>

using namespace std;

ColorPicker::ColorPicker(wxWindow *parent,
                         SelectedColor *sc,
                         ColorPreview *cp) : wxPanel(parent, -1, wxPoint(-1,-1), wxSize(256,256)),
                                             selected_color(sc),
                                             color_preview(cp)
{
    y = 127; u = 0; v = 0;

    cache.push_back(y * cv::Mat::ones(256,256,CV_8U));
    cache.push_back(cv::Mat::zeros(256,256,CV_8U));
    cache.push_back(cv::Mat::zeros(256,256,CV_8U));

    for(int i = 0; i < 256; i++) {
        for(int j = 0; j < 256; j++) {
            cache[1].at<uchar>(i,j) = i;
            cache[2].at<uchar>(i,j) = j;
        }
    }    

    update_gamut();
    Connect(wxID_ANY, wxEVT_PAINT, wxPaintEventHandler(ColorPicker::paint_event));
    Connect(wxID_ANY, wxEVT_LEFT_DOWN, wxMouseEventHandler(ColorPicker::mouse_event));
}

void ColorPicker::update_gamut() {
    cache[0].setTo(y);
    cv::merge(cache, gamut);
    cv::cvtColor(gamut, gamut, CV_YCrCb2RGB);   
    bitmap = wxBitmap(wxImage(gamut.cols, gamut.rows, gamut.data, true));
    Refresh(false);
}

void ColorPicker::paint_event(wxPaintEvent &event) {
    wxPaintDC dc(this);
    render(dc);
}

void ColorPicker::draw_now() {
    wxClientDC dc(this);
    render(dc);
}

void ColorPicker::render(wxDC &dc) {
    dc.DrawBitmap(bitmap,0,0,false);    
    dc.SetPen(*wxBLACK_PEN);
    dc.DrawLine(v,0,v,255);
    dc.DrawLine(0,u,255,u);
}

void ColorPicker::set_luminance(int new_y) {
    y = new_y;
    update_gamut();
    color_updated();
}

/* Called when the other gui components need to be updated */
void ColorPicker::color_updated() {
    selected_color->set_color(y,u,v);
    color_preview->set_color(y,u,v);
}

void ColorPicker::mouse_event(wxMouseEvent &event) {
    if(event.LeftDown()) {
        u = event.m_y;
        v = event.m_x;
        Refresh(false);
        color_updated();
    }
}
