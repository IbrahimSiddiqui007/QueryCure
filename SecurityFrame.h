#pragma once
//#include <wx/wx.h>

class SecurityFrame : public wxFrame {
public:
    SecurityFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
        wxPanel* panel = new wxPanel(this);
        // Add the content of the security page to this panel
    }
};
