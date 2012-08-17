#ifndef COLOR_PREVIEW_H
#define COLOR_PREVIEW_H

#include <wx/wx.h>

class ColorPreview : public wxPanel {
public:
    ColorPreview(wxWindow *parent);

    void set_color(int y, int u, int v);
};

#endif /* COLOR_PREVIEW_H */
