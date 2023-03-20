#pragma once
#include <wx/wx.h>
#include <SQLAPI.h>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

class DiagnosisAnalysis : public wxFrame
{
public:
	DiagnosisAnalysis(const wxString& title,Process& p);

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
	Process& m_p;

private:
	
	//Process& m_p;
	wxPanel* panel;
	wxPanel* panel2;
	wxTextCtrl* outputCtrl;
	wxTextCtrl* inputCtrl;
	SAString tbl;
	std::string sqlOutput;
	wxString tblSelection = "";
	wxString statsSelection = "";
	wxArrayString tables;
	wxArrayString stats;

	wxButton* tblDataButton;
	wxButton* tblStructButton;
	wxButton* statsButton;
	wxButton* suggestionsButton;
	wxButton* exPlanButton;
	wxChoice* tblChoice;
	wxChoice* statsChoice;

	wxButton* runTDButton;
	wxButton* runTSButton;
	wxButton* runStButton;
	wxButton* runSuButton;
	wxButton* runEPButton;
	wxButton* reconnectButton;
	wxButton* disconnectButton;
	wxStaticText* chooseTable;
	wxStaticText* chooseStats;
	wxStaticText* inputSQL;

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


	void OnTblDataButtonClicked(wxCommandEvent& evt);
	void OnTblStructButtonClicked(wxCommandEvent& evt);
	void OnStatsButtonClicked(wxCommandEvent& evt);
	void OnSuggestButtonClicked(wxCommandEvent& evt);
	void OnExPlanButtonClicked(wxCommandEvent& evt);
	void OnTblChoiceSelection(wxCommandEvent& event);
	void OnStatsChoiceSelection(wxCommandEvent& event);


	void runTDButtonClicked(wxCommandEvent& evt);
	void runTSButtonClicked(wxCommandEvent& evt);
	void runStButtonClicked(wxCommandEvent& evt);
	void runSuButtonClicked(wxCommandEvent& evt);
	void runEPButtonClicked(wxCommandEvent& evt);
	void reconnectButtonClicked(wxCommandEvent& evt);
	void disconnectButtonClicked(wxCommandEvent& evt);
	void connectButtonClicked(wxCommandEvent& evt);

};

