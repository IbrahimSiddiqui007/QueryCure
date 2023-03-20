#pragma once
#include <wx/wx.h>
#include "SecurityPage.h"
#include "DiagnosisAnalysis.h"
#include "ManageUsers.h"
#include "BckEnd.h"
#include <SQLAPI.h>

class MainFrame : public wxFrame
{
public:

	MainFrame(const wxString& title);
	wxString GetHost() const { return m_host; }
	wxString GetPort() const { return m_port; }
	wxString GetService() const { return m_service; }
	wxString GetUsername() const { return m_username; }
	wxString GetPassword() const { return m_password; }

	// Setter functions
	void SetHost(const wxString& host) { m_host = host; }
	void SetPrt(const wxString& port) { m_port = port; }
	void SetService(const wxString& service) { m_service = service; }
	void SetUsername(const wxString& username) { m_username = username; }
	void SetPassword(const wxString& password) { m_password = password; }

private:
	Process M_p;
	wxButton* securityButton;
	wxButton* diagnosisButton;
	wxString m_host;
	wxString m_port;
	wxString m_service;
	wxString m_username;
	wxString m_password;
	void OnSecurityButtonClick(wxCommandEvent& event);
	void OnDiagnosisButtonClick(wxCommandEvent& event);

};







