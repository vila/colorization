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
    color = cv::Scalar(128,128,128);
    cache.push_back(cv::Mat(256,256,CV_8U, cv::Scalar(128)));
    cache.push_back(cv::Mat(256,256,CV_8U, cv::Scalar(128)));
    cache.push_back(cv::Mat(256,256,CV_8U, cv::Scalar(128)));
    color_updated();


    for(int i = 0; i < 256; i++) {
        for(int j = 0; j < 256; j++) {
            cache[1].at<uchar>(i,j) = i;
            cache[2].at<uchar>(i,j) = j;
        }
    }    

    update_gamut();
    Connect(wxID_ANY, wxEVT_PAINT, wxPaintEventHandler(ColorPicker::paint_event));
    Connect(wxID_ANY, wxEVT_LEFT_DOWN, wxMouseEventHandler(ColorPicker::mouse_event));
    Connect(wxID_ANY, wxEVT_LEFT_UP, wxMouseEventHandler(ColorPicker::mouse_event));
}

cv::Scalar ColorPicker::get_color() {
    return color;
}

void ColorPicker::update_gamut() {
    cache[0].setTo(color[0]);
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
    dc.DrawLine(color[2],0,color[2],255);
    dc.DrawLine(0,color[1],255,color[1]);
}

void ColorPicker::set_luminance(int new_y) {
    color[0] = new_y;
    update_gamut();
    color_updated();
}

/* Called when the other gui components need to be updated */
void ColorPicker::color_updated() {
    selected_color->set_color(color);
    color_preview->set_color(color);
}

void ColorPicker::mouse_event(wxMouseEvent &event) {
    color[1] = event.m_y;
    color[2] = event.m_x;
    Refresh(false);
    color_updated();
}
