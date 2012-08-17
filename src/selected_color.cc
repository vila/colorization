#include "selected_color.hh"
#include "misc.hh"

#include <wx/wx.h>


SelectedColor::SelectedColor(wxWindow *parent) : wxPanel(parent, -1) {
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    SetSizer(hbox);

    wxStaticText *label = new wxStaticText(this, -1, _("Selected color:"));
    color_preview = new wxPanel(this, -1);

    hbox->Add(label, 0);
    hbox->Add(color_preview, 1, wxEXPAND | wxRIGHT | wxLEFT, 5);

    set_color(127,0,0);
}

void SelectedColor::set_color(int y, int u, int v) {
    color_preview->SetBackgroundColour(convert_yuv2rgb(y,u,v));
}

