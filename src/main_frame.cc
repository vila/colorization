#include "main_frame.hh"
#include "color_picker.hh"
#include "color_preview.hh"
#include "scribble_panel.hh"

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

        vbox->Add(color_picker, 0, wxBOTTOM, 5);
        vbox->Add(selected_color, 0, wxBOTTOM | wxEXPAND, 5);
        vbox->Add(color_preview, 0, wxBOTTOM, 5);

    }

    // left pane
    {
        wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
        left_pane->SetSizer(vbox);
        
        scribble_panel = new ScribblePanel(left_pane, color_picker, color_preview);
        
        vbox->Add(scribble_panel, 1, wxEXPAND);
    }
    

    // Toolbar
    wxImage::AddHandler( new wxGIFHandler );
    wxBitmap icon_open(_("assets/open.gif"), wxBITMAP_TYPE_GIF);

    wxToolBar *toolbar = CreateToolBar();
    toolbar->SetToolBitmapSize(wxSize(12,12));
    toolbar->AddTool(wxID_OPEN, icon_open, _("Open image"));
    toolbar->AddTool(wxID_EXIT, icon_open, _("Open image"));
    toolbar->AddTool(wxID_EXIT, icon_open, _("Open image"));
    toolbar->AddTool(wxID_EXIT, icon_open, _("Open image"));
    toolbar->AddTool(wxID_EXIT, icon_open, _("Open image"));
    toolbar->Realize();

    Connect(wxID_OPEN, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainFrame::open_file));

    Centre();
}

void MainFrame::open_file(wxCommandEvent &event) {
    wxFileDialog *dialog = new wxFileDialog(this, _("Choose image"), _("."));

    if(dialog->ShowModal() == wxID_OK) {
        // TODO support color images
        cv::Mat img = cv::imread(std::string(dialog->GetPath().ToAscii()), 0);
        
        if(img.data != 0)
            scribble_panel->set_image(img);
    }
}
