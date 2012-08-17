#include "color_preview.hh"
#include <wx/wx.h>

ColorPreview::ColorPreview(wxWindow *parent) : wxPanel(parent, -1,
                                                       wxPoint(-1,-1),
                                                       wxSize(PREVIEW_SIZE,PREVIEW_SIZE))
{
    Connect(wxID_ANY, wxEVT_PAINT, wxPaintEventHandler(ColorPreview::paint_event));
}

void ColorPreview::set_color(cv::Scalar color) {
    u = color[1];
    v = color[2];
    update_preview();
}


void ColorPreview::paint_event(wxPaintEvent &event) {
    // TODO maybe refactor this together with color_picker, scribblepanel
    wxPaintDC dc(this);
    render(dc);
}

void ColorPreview::draw_now() {
    wxClientDC dc(this);
    render(dc);
}



void ColorPreview::render(wxDC &dc) {
    if(!preview_image.empty()) {
        dc.DrawBitmap(bitmap, 0, 0, false);
    }
}

void ColorPreview::set_preview_image(cv::Mat &im) {
    CV_Assert(im.channels() == 1);
    CV_Assert(im.depth() == CV_8U);
    preview_image = im.clone();   
    update_preview();
}

void ColorPreview::update_preview() {
    if(preview_image.empty())
        return;

    cv::Mat preview;
    cv::merge(std::vector<cv::Mat>({preview_image,
                    cv::Mat(preview_image.cols, preview_image.rows, CV_8U, cv::Scalar(u)),
                    cv::Mat(preview_image.cols, preview_image.rows, CV_8U, cv::Scalar(v))}),
        preview);
    
    cv::cvtColor(preview, preview, CV_YCrCb2RGB);
    cv::resize(preview, preview, cv::Size(PREVIEW_SIZE,PREVIEW_SIZE), 0, 0, cv::INTER_NEAREST);

    bitmap = wxBitmap(wxImage(preview.cols, preview.rows, preview.data, true));
    Refresh(false);
}
