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
    wxImage::AddHandler( new wxPNGHandler );
    wxBitmap icon_open(_("assets/open.gif"), wxBITMAP_TYPE_GIF);
    wxBitmap icon_save(_("assets/save.png"), wxBITMAP_TYPE_PNG);
    wxBitmap icon_draw(_("assets/draw.gif"), wxBITMAP_TYPE_GIF);
    wxBitmap icon_erase(_("assets/erase.png"), wxBITMAP_TYPE_PNG);
    wxBitmap icon_color(_("assets/color_picker.png"), wxBITMAP_TYPE_PNG);

    wxToolBar *toolbar = CreateToolBar();
    toolbar->SetToolBitmapSize(wxSize(12,12));
    toolbar->AddTool(wxID_OPEN, icon_open, _("Open image"));
    toolbar->AddTool(wxID_SAVE, icon_save, _("Save image"));
    toolbar->AddSeparator();
    toolbar->AddRadioTool(ScribblePanel::DrawingMode::DRAWING,
                          _("Draw"), icon_draw);
    toolbar->AddRadioTool(ScribblePanel::DrawingMode::ERASING,
                           _("Erase"), icon_erase);
    toolbar->AddRadioTool(ScribblePanel::DrawingMode::COLOR_PICK,
                           _("Copy color"), icon_color);
    toolbar->Realize();

    Connect(wxID_OPEN, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainFrame::open_file));
    Connect(wxID_SAVE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainFrame::save_file));
    
    Connect(ScribblePanel::DrawingMode::DRAWING, wxEVT_COMMAND_TOOL_CLICKED,
            wxCommandEventHandler(ScribblePanel::update_drawing_mode), NULL, scribble_panel);
    Connect(ScribblePanel::DrawingMode::ERASING, wxEVT_COMMAND_TOOL_CLICKED,
            wxCommandEventHandler(ScribblePanel::update_drawing_mode), NULL, scribble_panel);
    Connect(ScribblePanel::DrawingMode::COLOR_PICK, wxEVT_COMMAND_TOOL_CLICKED,
            wxCommandEventHandler(ScribblePanel::update_drawing_mode), NULL, scribble_panel);


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

void MainFrame::save_file(wxCommandEvent &event) {
    wxFileDialog *dialog = new wxFileDialog(this, _("Choose image"), _("."));

    if(dialog->ShowModal() == wxID_OK) {
        // TODO support color images
        cv::Mat img = cv::imread(std::string(dialog->GetPath().ToAscii()), 0);
        
        if(img.data != 0)
            scribble_panel->set_image(img);
    }
}
