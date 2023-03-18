#pragma once
//#include <wx/wx.h>
#include "SecurityPage.h"
#include "DiagnosisAnalysis.h"
#include "ManageUsers.h"

class MainFrame : public wxFrame
{
public:

	MainFrame(const wxString& title);

private:
	wxButton* securityButton;
	wxButton* diagnosisButton;
	
	void OnSecurityButtonClick(wxCommandEvent& event); 
	void OnDiagnosisButtonClick(wxCommandEvent& event);
	void OnManageUserButtonClick(wxCommandEvent& event);

};







