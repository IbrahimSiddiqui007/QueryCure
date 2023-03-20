#pragma once
#include <wx/wx.h>
#include "BckEnd.h"
#include "DiagnosisAnalysis.h"
#include "MainFrame.h"


class ManageUsers : public wxFrame
{
public:
	ManageUsers(const wxString& title);
    // Getter functions
    wxString GetHost() const { return m_hostText->GetValue(); }
    wxString GetPort() const { return m_portText->GetValue(); }
    wxString GetService() const { return m_serviceComboBox->GetValue(); }
    wxString GetUsername() const { return m_usernameText->GetValue(); }
    wxString GetPassword() const { return m_passwordText->GetValue(); }

    // Setter functions
    void SetHost(const wxString& host) { m_hostText->SetValue(host); }
    void SetPrt(const wxString& port) { m_portText->SetValue(port); }
    void SetService(const wxString& service) { m_serviceComboBox->SetValue(service); }
    void SetUsername(const wxString& username) { m_usernameText->SetValue(username); }
    void SetPassword(const wxString& password) { m_passwordText->SetValue(password); }
private:
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
