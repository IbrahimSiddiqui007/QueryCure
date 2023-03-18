#pragma once
//#include <wx/wx.h>
#include "BckEnd.h"
#include "DiagnosisAnalysis.h"


class ManageUsers : public wxFrame
{
public:

	ManageUsers(const wxString& title);
private:
    Process p;
    SAConnection con;
    SACommand cmd;
    wxPanel* m_panel;
    wxStaticText* m_hostLabel;
    wxTextCtrl* m_hostText;
    wxStaticText* m_portLabel;
    wxTextCtrl* m_portText;
    wxStaticText* m_serviceLabel;
    wxComboBox* m_serviceComboBox;  // Use wxComboBox instead of wxTextCtrl
    wxTextCtrl* m_otherServiceText; // New wxTextCtrl for "Other" option
    wxStaticText* m_usernameLabel;
    wxTextCtrl* m_usernameText;
    wxStaticText* m_passwordLabel;
    wxTextCtrl* m_passwordText;
    wxButton* m_connectButton;

};
