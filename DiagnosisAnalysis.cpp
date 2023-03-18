#include "DiagnosisAnalysis.h"
#include "BckEnd.h"

DiagnosisAnalysis::DiagnosisAnalysis(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	
	// Creating the windows
	panel = new wxPanel(this);
	sqlOutput = "SQL output here";

	// Scrolling windows
	scrollWindow = new wxScrolledWindow(panel, wxID_ANY, wxPoint(225, 100), wxSize(550, 475));
	outputCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(225, 100), scrollWindow->GetSize(), wxTE_MULTILINE | wxTE_READONLY);
	//outputCtrl->SetValue(sqlOutput);

	// Setting the output size
	outputSize = outputCtrl->GetSize();
	scrollWindow->SetSize(outputSize);
	scrollWindow->SetScrollRate(20, 20);


	scrollWindow->Bind(wxEVT_SCROLLWIN_TOP, [=](wxScrollWinEvent&) { outputCtrl->ShowPosition(0); });
	scrollWindow->Bind(wxEVT_SCROLLWIN_BOTTOM, [=](wxScrollWinEvent&) { outputCtrl->ShowPosition(outputCtrl->GetLastPosition()); });
	scrollWindow->Bind(wxEVT_SCROLLWIN_LINEUP, [=](wxScrollWinEvent&) { outputCtrl->LineUp(); });
	scrollWindow->Bind(wxEVT_SCROLLWIN_LINEDOWN, [=](wxScrollWinEvent&) { outputCtrl->LineDown(); });
	scrollWindow->Bind(wxEVT_SCROLLWIN_PAGEUP, [=](wxScrollWinEvent&) { outputCtrl->PageUp(); });
	scrollWindow->Bind(wxEVT_SCROLLWIN_PAGEDOWN, [=](wxScrollWinEvent&) { outputCtrl->PageDown(); });

	tblDataButton = new wxButton(panel, wxID_ANY, "Table Content", wxPoint(275, 50), wxSize(100, 30));
	tblStructButton = new wxButton(panel, wxID_ANY, "Table Structure", wxPoint(400, 50), wxSize(100, 30));
	statsButton = new wxButton(panel, wxID_ANY, "Statistics", wxPoint(525, 50), wxSize(100, 30));
	suggestionsButton = new wxButton(panel, wxID_ANY, "Suggestions", wxPoint(650, 50), wxSize(100, 30));

	// Making the wxArray
	wxArrayString tables;
	p.con.Connect("(DESCRIPTION=(ADDRESS=(PROTOCOL=tcp) (HOST=LocalHost) (PORT=1521))(CONNECT_DATA = (SERVICE_NAME = orcl)))", "system", "oracle", SA_Oracle_Client);
	p.cmd.setConnection(&p.con);
	/*p.cmd.setCommandText("SELECT table_name FROM user_tables");
	p.cmd.Execute();*/
	
	while (p.cmd.FetchNext())
	{
		std::string t= (std::string)p.cmd.Field("table_name").asString();
		tables.Add(t);
	}

	wxArrayString stats;
	stats.Add("Tables");
	stats.Add("Indexes");
	stats.Add("Materialized views");
	stats.Add("Table Partitions");
	stats.Add("Columns of tables");
	stats.Add("Clusters");


	//initialising the drop downs
	tblChoice = new wxChoice(panel, wxID_ANY, wxPoint(50, 60), wxSize(120, -1), tables, wxCB_SORT);
	tblChoice->SetSelection(0);

	statsChoice = new wxChoice(panel, wxID_ANY, wxPoint(50, 120), wxSize(120, -1), stats, wxCB_SORT);
	statsChoice->SetSelection(0);


	tblChoice->Bind(wxEVT_CHOICE, &DiagnosisAnalysis::OnTblChoiceSelection, this);
	statsChoice->Bind(wxEVT_CHOICE, &DiagnosisAnalysis::OnStatsChoiceSelection, this);

	//Text for the drop down menus
	chooseTable = new wxStaticText(panel, wxID_ANY, "Choose a table:", wxPoint(50, 40));
	chooseStats = new wxStaticText(panel, wxID_ANY, "Choose a statistic:", wxPoint(50, 100));

	//Hiding the statistics drop down
	statsChoice->Hide();
	chooseStats->Hide();

	//this->Bind(wxEVT_BUTTON, &MainFrame::OnAnyButtonClicked, this);
	tblDataButton->Bind(wxEVT_BUTTON, &DiagnosisAnalysis::OnTblDataButtonClicked, this);
	tblStructButton->Bind(wxEVT_BUTTON, &DiagnosisAnalysis::OnTblStructButtonClicked, this);
	statsButton->Bind(wxEVT_BUTTON, &DiagnosisAnalysis::OnStatsButtonClicked, this);
	suggestionsButton->Bind(wxEVT_BUTTON, &DiagnosisAnalysis::OnSuggestButtonClicked, this);
	
}


// All methods being used 

void DiagnosisAnalysis::OnTblDataButtonClicked(wxCommandEvent& evt) {
	statsChoice->Hide();
	chooseStats->Hide();
	p.cmd.setCommandText("SELECT * FROM "+evt.GetSelection()); // get chosen table
	p.cmd.Execute();
	int numColumns = p.cmd.FieldCount();
	for (int i = 1; i <= numColumns; i++) {
		outputCtrl->SetValue((std::string)p.cmd.Field(i).Name());
		std::cout << '\t';
	}
	while (p.cmd.FetchNext()) {
		for (int i = 1; i <= numColumns; i++) {
			outputCtrl->SetValue((std::string)p.cmd.Field(i).asString());
			std::cout << "\t";
		}
		std::cout << std::endl;
	}
	
}

void DiagnosisAnalysis::OnTblStructButtonClicked(wxCommandEvent& evt) {
	//wxLogMessage("Button 1 Clicked");
	//wxLogMessage("Button 1 Clicked");
	statsChoice->Hide();
	chooseStats->Hide();
	outputCtrl->SetValue(sqlOutput);

}
void DiagnosisAnalysis::OnStatsButtonClicked(wxCommandEvent& evt) {
	//wxLogMessage("Button 2 Clicked");
	//wxLogMessage("Button 2 Clicked");
	statsChoice->Show();
	chooseStats->Show();
	outputCtrl->SetValue(sqlOutput);
}

void DiagnosisAnalysis::OnSuggestButtonClicked(wxCommandEvent& evt) {
	//wxLogMessage("Button Clicked");
	//wxLogStatus("Button Clicked");
	statsChoice->Hide();
	chooseStats->Hide();
	outputCtrl->SetValue(sqlOutput);
}

void DiagnosisAnalysis::OnTblChoiceSelection(wxCommandEvent& evt) {
	//wxLogMessage("Button Clicked");
	//wxLogStatus("Button Clicked");
	statsChoice->Hide();
	chooseStats->Hide();
	wxString tblSelection = evt.GetString();
	sqlOutput = tblSelection;
	outputCtrl->SetValue(sqlOutput);
}

void DiagnosisAnalysis::OnStatsChoiceSelection(wxCommandEvent& evt) {
	//wxLogMessage("Button Clicked");
	//wxLogStatus("Button Clicked");
	wxString statsSelection = evt.GetString();
	sqlOutput = statsSelection;
	outputCtrl->SetValue(sqlOutput);
}
