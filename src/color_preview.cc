#include "color_preview.hh"
#include <wx/wx.h>

ColorPreview::ColorPreview(wxWindow *parent) : wxPanel(parent, -1,
                                                       wxPoint(-1,-1),
                                                       wxSize(PREVIEW_SIZE,PREVIEW_SIZE))
{
//    SetBackgroundColour(*wxBLACK);

    { // DEBUG
        preview_image = cv::imread("assets/test.jpg", 0);
        CV_Assert(preview_image.cols == 64);
        CV_Assert(preview_image.rows == 64);
       
    }

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
    dc.DrawBitmap(bitmap, 0, 0, false);
}

void ColorPreview::set_preview_image(cv::Mat &im) {
    CV_Assert(im.channels() == 1);
    CV_Assert(im.depth() == CV_8U);
    preview_image = im.clone();   
    update_preview();
}

void ColorPreview::update_preview() {
    cv::Mat preview;
    cv::merge(std::vector<cv::Mat>({preview_image,
                    u * cv::Mat::ones(PREVIEW_IMAGE_SIZE, PREVIEW_IMAGE_SIZE, CV_8U),
                    v * cv::Mat::ones(PREVIEW_IMAGE_SIZE, PREVIEW_IMAGE_SIZE, CV_8U)}), preview);
    
    cv::cvtColor(preview, preview, CV_YCrCb2RGB);
    cv::resize(preview, preview, cv::Size(PREVIEW_SIZE,PREVIEW_SIZE), 0, 0, cv::INTER_NEAREST);


    bitmap = wxBitmap(wxImage(preview.cols, preview.rows, preview.data, true));
    Refresh(false);
}
