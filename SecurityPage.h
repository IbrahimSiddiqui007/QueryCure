#pragma once
#include <wx/wx.h>
#include "BckEnd.h"
class SecurityPage : public wxFrame
{

public:
	SecurityPage(const wxString& title);

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



	// Declaring the variables
private:

	wxPanel* panel;
	wxTextCtrl* outputCtrl;
	std::string sqlOutput;
	wxString tblSelection = "";
	wxString statsSelection = "";

	wxButton* AllUserButton;
	wxButton* ActivityLogButton;
	wxButton* UsrPrivlageButton;
	wxButton* HostDetailsButton;
	wxButton* reconnectButton;
	wxButton* disconnectButton;
	wxChoice* tblChoice;
	wxStaticText* chooseTable;
	wxArrayString tables;

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


	// Declaring the methods 
	void OnAllUserButtonClicked(wxCommandEvent& evt);
	void OnActivityLogButtonClicked(wxCommandEvent& evt);
	void OnUsrPrivlageButtonClicked(wxCommandEvent& evt);
	void OnHostDetailsButtonClicked(wxCommandEvent& evt);
	void OnTblChoiceSelection(wxCommandEvent& event);
	void reconnectButtonClicked(wxCommandEvent& evt);
	void disconnectButtonClicked(wxCommandEvent& evt);
	void connectButtonClicked(wxCommandEvent& evt);
};
