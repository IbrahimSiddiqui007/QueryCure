#pragma once
//#include <wx/wx.h>
#include "BckEnd.h"
#include "ManageUsers.h"
class DiagnosisAnalysis : public wxFrame
{
public:

	DiagnosisAnalysis(const wxString& title);
private:
	Process p;
	wxPanel* panel;
	wxScrolledWindow* scrollWindow;
	wxTextCtrl* outputCtrl;
	std::string sqlOutput;
	wxString tblSelection = "";
	wxString statsSelection = "";
	wxSize outputSize;

	wxButton* tblDataButton;
	wxButton* tblStructButton;
	wxButton* statsButton;
	wxButton* suggestionsButton;
	wxChoice* tblChoice;
	wxChoice* statsChoice;

	wxStaticText* chooseTable;
	wxStaticText* chooseStats;

	void OnTblDataButtonClicked(wxCommandEvent& evt);
	void OnTblStructButtonClicked(wxCommandEvent& evt);
	void OnStatsButtonClicked(wxCommandEvent& evt);
	void OnSuggestButtonClicked(wxCommandEvent& evt);
	void OnTblChoiceSelection(wxCommandEvent& event);
	void OnStatsChoiceSelection(wxCommandEvent& event);

};

