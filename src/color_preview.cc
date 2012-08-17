#include "color_preview.hh"
#include <wx/wx.h>

ColorPreview::ColorPreview(wxWindow *parent) : wxPanel(parent, -1, wxPoint(-1,-1), wxSize(256,256))
{
    SetBackgroundColour(*wxBLACK);
    // TODO implement
}

void ColorPreview::set_color(int y, int u, int v) {
    // TODO implement
}
