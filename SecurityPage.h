#pragma once
#//include <wx/wx.h>
#include "BckEnd.h"
class SecurityPage : public wxFrame
{

public:
	SecurityPage(const wxString& title);

// Declaring the variables
private:
	Process p;
	wxPanel* panel;
	wxScrolledWindow* scrollWindow;
	wxTextCtrl* outputCtrl;
	std::string sqlOutput;
	wxString tblSelection = "";
	wxString statsSelection = "";
	wxSize outputSize;

	wxButton* AllUserButton;
	wxButton* ActivityLogButton;
	wxButton* UsrPrivlageButton;
	wxButton* HostDetailsButton;
	wxChoice* tblChoice;
	//wxChoice* statsChoice;

	wxStaticText* chooseTable;
	//wxStaticText* chooseStats;

// Declaring the methods 
	void OnAllUserButtonClicked(wxCommandEvent& evt);
	void OnActivityLogButtonClicked(wxCommandEvent& evt);
	void OnUsrPrivlageButtonClicked(wxCommandEvent& evt);
	void OnHostDetailsButtonClicked(wxCommandEvent& evt);
	void OnTblChoiceSelection(wxCommandEvent& event);

};
