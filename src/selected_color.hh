#ifndef SELECTED_COLOR_H
#define SELECTED_COLOR_H

#include <wx/wx.h>

class SelectedColor : public wxPanel {
public:
    SelectedColor(wxWindow *parent);
    void set_color(int y, int u, int v);

private:
    wxPanel *color_preview;
};

#endif /* SELECTED_COLOR_H */
