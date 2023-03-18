#include "SecurityPage.h"
#include "wx/wx.h"
#include <wx/spinctrl.h>
#include <string>
#include "BckEnd.h"


SecurityPage::SecurityPage(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	// Setting the windows
	panel = new wxPanel(this);
	sqlOutput = "Security info here";

	scrollWindow = new wxScrolledWindow(panel, wxID_ANY, wxPoint(225, 100), wxSize(550, 475));
	outputCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(225, 100), scrollWindow->GetSize(), wxTE_MULTILINE | wxTE_READONLY);
	//outputCtrl->SetValue(sqlOutput);

	outputSize = outputCtrl->GetSize();
	scrollWindow->SetSize(outputSize);
	scrollWindow->SetScrollRate(20, 20);

	scrollWindow->Bind(wxEVT_SCROLLWIN_TOP, [=](wxScrollWinEvent&) { outputCtrl->ShowPosition(0); });
	scrollWindow->Bind(wxEVT_SCROLLWIN_BOTTOM, [=](wxScrollWinEvent&) { outputCtrl->ShowPosition(outputCtrl->GetLastPosition()); });
	scrollWindow->Bind(wxEVT_SCROLLWIN_LINEUP, [=](wxScrollWinEvent&) { outputCtrl->LineUp(); });
	scrollWindow->Bind(wxEVT_SCROLLWIN_LINEDOWN, [=](wxScrollWinEvent&) { outputCtrl->LineDown(); });
	scrollWindow->Bind(wxEVT_SCROLLWIN_PAGEUP, [=](wxScrollWinEvent&) { outputCtrl->PageUp(); });
	scrollWindow->Bind(wxEVT_SCROLLWIN_PAGEDOWN, [=](wxScrollWinEvent&) { outputCtrl->PageDown(); });



	AllUserButton = new wxButton(panel, wxID_ANY, "All Users", wxPoint(275, 50), wxSize(100, 30));
	ActivityLogButton = new wxButton(panel, wxID_ANY, "Activity Log", wxPoint(400, 50), wxSize(100, 30));
	UsrPrivlageButton = new wxButton(panel, wxID_ANY, "User Privlage", wxPoint(525, 50), wxSize(100, 30));
	HostDetailsButton = new wxButton(panel, wxID_ANY, "Host details", wxPoint(650, 50), wxSize(100, 30));

	wxArrayString tables;
	p.con.Connect("(DESCRIPTION=(ADDRESS=(PROTOCOL=tcp) (HOST=LocalHost) (PORT=1521))(CONNECT_DATA = (SERVICE_NAME = XEPDB1)))", "hr", "hr", SA_Oracle_Client); // big problem
	p.cmd.setConnection(&p.con);
	p.cmd.setCommandText("SELECT table_name FROM user_tables");
	p.cmd.Execute();

	while (p.cmd.FetchNext())
	{
		std::string t = (std::string)p.cmd.Field("table_name").asString();
		tables.Add(t);
	}

	
	//initialising the drop downs
	tblChoice = new wxChoice(panel, wxID_ANY, wxPoint(50, 60), wxSize(120, -1), tables, wxCB_SORT);
	tblChoice->SetSelection(0);

	tblChoice->Bind(wxEVT_CHOICE, &SecurityPage::OnTblChoiceSelection, this);
	//statsChoice->Bind(wxEVT_CHOICE, &MainFrame::OnStatsChoiceSelection, this);

	//Text for the drop down menus
	chooseTable = new wxStaticText(panel, wxID_ANY, "Choose a table:", wxPoint(50, 40));
	//chooseStats = new wxStaticText(panel, wxID_ANY, "Choose a statistic:", wxPoint(50, 100));

	AllUserButton->Bind(wxEVT_BUTTON, &SecurityPage::OnAllUserButtonClicked, this);
	ActivityLogButton->Bind(wxEVT_BUTTON, &SecurityPage::OnActivityLogButtonClicked, this);
	UsrPrivlageButton->Bind(wxEVT_BUTTON, &SecurityPage::OnUsrPrivlageButtonClicked, this);
	HostDetailsButton->Bind(wxEVT_BUTTON, &SecurityPage::OnHostDetailsButtonClicked, this);


	
}

void SecurityPage::OnAllUserButtonClicked(wxCommandEvent& evt) {
	
	outputCtrl->SetValue(sqlOutput);
}


void SecurityPage::OnActivityLogButtonClicked(wxCommandEvent& evt) {
	
	outputCtrl->SetValue(sqlOutput);

}
void SecurityPage::OnUsrPrivlageButtonClicked(wxCommandEvent& evt) {
	
	outputCtrl->SetValue(sqlOutput);
}

void SecurityPage::OnHostDetailsButtonClicked(wxCommandEvent& evt) {
	
	outputCtrl->SetValue(sqlOutput);
}

void SecurityPage::OnTblChoiceSelection(wxCommandEvent& evt) {
	
	wxString tblSelection = evt.GetString();
	sqlOutput = tblSelection;
	outputCtrl->SetValue(sqlOutput);
}