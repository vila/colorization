#include "main_frame.hh"
#include "color_picker.hh"
#include "color_preview.hh"

#include <wx/wx.h>
#include <opencv2/opencv.hpp>


MainFrame::MainFrame() : wxFrame(NULL, -1, _("Colorization - Viktor Larsson"),
                                 wxPoint(-1,-1), wxSize(800,600)) 
{

    wxPanel *main_panel = new wxPanel(this, -1);
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    main_panel->SetSizer(hbox);

    wxPanel *left_pane = new wxPanel(main_panel, -1);
    wxPanel *right_pane = new wxPanel(main_panel, -1);

    hbox->Add(left_pane, 1, wxEXPAND | wxRIGHT, 5);
    hbox->Add(right_pane, 0, wxEXPAND, 0);
    

    { // debug
        wxColour c1,c2;
        left_pane->SetBackgroundColour(*wxRED);
        //right_pane->SetBackgroundColour(*wxBLUE);
    }

    // right pane
    {
        wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
        right_pane->SetSizer(vbox);

        selected_color = new SelectedColor(right_pane);
        color_preview = new ColorPreview(right_pane);
        
        color_picker = new ColorPicker(right_pane, selected_color, color_preview);
        color_picker->set_luminance(220);
        

        // placeholder
        wxPanel *color_preview = new wxPanel(right_pane, -1, wxPoint(-1,-1), wxSize(256,256));
        color_preview->SetBackgroundColour(*wxBLACK);

        vbox->Add(color_picker, 0, wxBOTTOM, 5);
        vbox->Add(selected_color, 0, wxBOTTOM | wxEXPAND, 5);
        vbox->Add(color_preview, 0, wxBOTTOM, 5);

    }
    

    


    // Toolbar
    wxImage::AddHandler( new wxGIFHandler );
    wxBitmap icon_open(_("assets/open.gif"), wxBITMAP_TYPE_GIF);

    wxToolBar *toolbar = CreateToolBar();
    toolbar->SetToolBitmapSize(wxSize(12,12));
    toolbar->AddTool(wxID_EXIT, icon_open, _("Open image"));
    toolbar->AddTool(wxID_EXIT, icon_open, _("Open image"));
    toolbar->AddTool(wxID_EXIT, icon_open, _("Open image"));
    toolbar->AddTool(wxID_EXIT, icon_open, _("Open image"));
    toolbar->AddTool(wxID_EXIT, icon_open, _("Open image"));
    toolbar->Realize();
    
    Centre();
}
