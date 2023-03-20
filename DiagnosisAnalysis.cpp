#include "MainFrame.h"
#include <wx/wx.h>
#include <string>



DiagnosisAnalysis::DiagnosisAnalysis(const wxString& title,Process& p) : wxFrame(nullptr, wxID_ANY, title),m_p(p) {
	panel = new wxPanel(this);
	panel->SetBackgroundColour(wxColour(60, 71, 75));
	sqlOutput = "";


	//Login widgets
	// Host input
	m_hostLabel = new wxStaticText(panel, wxID_ANY, "Host:", wxPoint(350, 25));
	m_hostLabel->SetForegroundColour(wxColour(255, 255, 255));
	m_hostText = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(350, 50), wxSize(100, 25));

	// Port input
	m_portLabel = new wxStaticText(panel, wxID_ANY, "Port:", wxPoint(350, 78));
	m_portLabel->SetForegroundColour(wxColour(255, 255, 255));
	m_portText = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(350, 100), wxSize(100, 25));

	// Service input
	m_serviceLabel = new wxStaticText(panel, wxID_ANY, "Service:", wxPoint(350, 130));
	m_serviceLabel->SetForegroundColour(wxColour(255, 255, 255));
	wxString choices[] = { "Oracle VM", "Oracle Express Edition", "Other" }; // Create choices for the wxComboBox
	wxArrayString choicesArray(WXSIZEOF(choices), choices);
	m_serviceComboBox = new wxComboBox(panel, wxID_ANY, "", wxPoint(350, 150), wxDefaultSize, choicesArray, wxCB_DROPDOWN);
	m_otherServiceText = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(350, 175), wxSize(100, 25), wxTE_PROCESS_ENTER);
	m_otherServiceText->Hide(); // Hide the wxTextCtrl initially

	// Username input
	m_usernameLabel = new wxStaticText(panel, wxID_ANY, "Username:", wxPoint(350, 200));
	m_usernameLabel->SetForegroundColour(wxColour(255, 255, 255));
	m_usernameText = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(350, 225), wxSize(100, 25));

	// Password input
	m_passwordLabel = new wxStaticText(panel, wxID_ANY, "Password:", wxPoint(350, 260));
	m_passwordLabel->SetForegroundColour(wxColour(255, 255, 255));
	m_passwordText = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(350, 285), wxSize(100, 25), wxTE_PASSWORD);

	// Connect button
	m_connectButton = new wxButton(panel, wxID_ANY, "Connect", wxPoint(350, 335), wxSize(100, 30));
	m_connectButton->SetBackgroundColour(wxColour(0, 177, 89));
	m_connectButton->SetForegroundColour(wxColour(255, 255, 255));


	m_serviceComboBox->Bind(wxEVT_COMBOBOX, [=](wxCommandEvent& event)
		{
			if (m_serviceComboBox->GetValue() == "Other")
			{
				m_otherServiceText->Show();
			}
			else
			{
				m_otherServiceText->Hide();
			}
		});



	//Initializing Display Window
	outputCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(225, 100), wxSize(550, 475), wxTE_MULTILINE | wxTE_READONLY | wxHSCROLL | wxVSCROLL | wxTE_RICH2);


	//Initializing Input Window, only shown when explain plan button clicked
	inputCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(225, 385), wxSize(550, 150), wxTE_MULTILINE | wxHSCROLL | wxVSCROLL | wxTE_RICH2);
	inputCtrl->Hide();

	//Text for the drop down menus
	chooseTable = new wxStaticText(panel, wxID_ANY, "Choose a table:", wxPoint(50, 40));
	chooseTable->SetForegroundColour(wxColour(255, 255, 255));
	chooseStats = new wxStaticText(panel, wxID_ANY, "Choose a statistic:", wxPoint(50, 100));
	chooseStats->SetForegroundColour(wxColour(255, 255, 255));

	//Text for user input in explain plan, only shown when explain button is clicked
	inputSQL = new wxStaticText(panel, wxID_ANY, "Type your SQL statement here, then click Run:", wxPoint(225, 360));
	inputSQL->SetForegroundColour(wxColour(255, 255, 255));
	inputSQL->Hide();

	//Initializing buttons
	tblDataButton = new wxButton(panel, wxID_ANY, "Table Content", wxPoint(250, 50), wxSize(100, 30), wxRAISED_BORDER);
	tblDataButton->SetBackgroundColour(wxColour(132, 220, 198));
	tblStructButton = new wxButton(panel, wxID_ANY, "Table Structure", wxPoint(350, 50), wxSize(100, 30), wxRAISED_BORDER);
	tblStructButton->SetBackgroundColour(wxColour(132, 220, 198));
	statsButton = new wxButton(panel, wxID_ANY, "Statistics", wxPoint(450, 50), wxSize(100, 30), wxRAISED_BORDER);
	statsButton->SetBackgroundColour(wxColour(132, 220, 198));
	suggestionsButton = new wxButton(panel, wxID_ANY, "Suggestions", wxPoint(550, 50), wxSize(100, 30), wxRAISED_BORDER);
	suggestionsButton->SetBackgroundColour(wxColour(132, 220, 198));
	exPlanButton = new wxButton(panel, wxID_ANY, "Explain Plan", wxPoint(650, 50), wxSize(100, 30), wxRAISED_BORDER);
	exPlanButton->SetBackgroundColour(wxColour(132, 220, 198));

	//Individual run buttons for each button above, so that they can be linked to those specific functions
	runTDButton = new wxButton(panel, wxID_ANY, "Run", wxPoint(60, 500), wxSize(100, 30), wxRAISED_BORDER);
	runTSButton = new wxButton(panel, wxID_ANY, "Run", wxPoint(60, 500), wxSize(100, 30), wxRAISED_BORDER);
	runStButton = new wxButton(panel, wxID_ANY, "Run", wxPoint(60, 500), wxSize(100, 30), wxRAISED_BORDER);
	runSuButton = new wxButton(panel, wxID_ANY, "Run", wxPoint(60, 500), wxSize(100, 30), wxRAISED_BORDER);
	runEPButton = new wxButton(panel, wxID_ANY, "Run", wxPoint(60, 500), wxSize(100, 30), wxRAISED_BORDER);
	reconnectButton = new wxButton(panel, wxID_ANY, "Reconnect", wxPoint(20, 550), wxSize(75, 30), wxRAISED_BORDER);
	disconnectButton = new wxButton(panel, wxID_ANY, "Disconnect", wxPoint(110, 550), wxSize(75, 30), wxRAISED_BORDER);

	runTDButton->SetBackgroundColour(wxColour(132, 220, 198));
	runTSButton->SetBackgroundColour(wxColour(132, 220, 198));
	runStButton->SetBackgroundColour(wxColour(132, 220, 198));
	runSuButton->SetBackgroundColour(wxColour(132, 220, 198));
	runEPButton->SetBackgroundColour(wxColour(132, 220, 198));
	reconnectButton->SetBackgroundColour(wxColour(132, 220, 198));
	disconnectButton->SetBackgroundColour(wxColour(132, 220, 198));

	runTDButton->Hide();
	runTSButton->Hide();
	runStButton->Hide();
	runSuButton->Hide();
	runEPButton->Hide();


	//initialising the drop downs
	tblChoice = new wxChoice(panel, wxID_ANY, wxPoint(50, 60), wxSize(120, -1), tables, wxCB_SORT);
	tblChoice->SetSelection(0);
	tblChoice->SetBackgroundColour(wxColour(132, 220, 198));

	statsChoice = new wxChoice(panel, wxID_ANY, wxPoint(50, 120), wxSize(120, -1), stats, wxCB_SORT);
	statsChoice->SetSelection(0);
	statsChoice->SetBackgroundColour(wxColour(132, 220, 198));

	//Hiding the statistics drop down, only shown when statistics button is clicked
	statsChoice->Hide();
	chooseStats->Hide();

	//Binding dropdowns to events
	tblChoice->Bind(wxEVT_CHOICE, &DiagnosisAnalysis::OnTblChoiceSelection, this);
	statsChoice->Bind(wxEVT_CHOICE, &DiagnosisAnalysis::OnStatsChoiceSelection, this);



	//Binding all buttons to events
	tblDataButton->Bind(wxEVT_BUTTON, &DiagnosisAnalysis::OnTblDataButtonClicked, this);
	tblStructButton->Bind(wxEVT_BUTTON, &DiagnosisAnalysis::OnTblStructButtonClicked, this);
	statsButton->Bind(wxEVT_BUTTON, &DiagnosisAnalysis::OnStatsButtonClicked, this);
	suggestionsButton->Bind(wxEVT_BUTTON, &DiagnosisAnalysis::OnSuggestButtonClicked, this);
	exPlanButton->Bind(wxEVT_BUTTON, &DiagnosisAnalysis::OnExPlanButtonClicked, this);

	runTDButton->Bind(wxEVT_BUTTON, &DiagnosisAnalysis::runTDButtonClicked, this);
	runTSButton->Bind(wxEVT_BUTTON, &DiagnosisAnalysis::runTSButtonClicked, this);
	runStButton->Bind(wxEVT_BUTTON, &DiagnosisAnalysis::runStButtonClicked, this);
	runSuButton->Bind(wxEVT_BUTTON, &DiagnosisAnalysis::runSuButtonClicked, this);
	runEPButton->Bind(wxEVT_BUTTON, &DiagnosisAnalysis::runEPButtonClicked, this);
	m_connectButton->Bind(wxEVT_BUTTON, &DiagnosisAnalysis::connectButtonClicked, this);
	reconnectButton->Bind(wxEVT_BUTTON, &DiagnosisAnalysis::reconnectButtonClicked, this);
	disconnectButton->Bind(wxEVT_BUTTON, &DiagnosisAnalysis::disconnectButtonClicked, this);

	//Hiding Diagnosis Stuff:

	outputCtrl->Hide();
	chooseTable->Hide();
	chooseStats->Hide();

	tblDataButton->Hide();
	tblStructButton->Hide();
	statsButton->Hide();
	suggestionsButton->Hide();
	exPlanButton->Hide();

	runTDButton->Hide();
	runTSButton->Hide();
	runStButton->Hide();
	runSuButton->Hide();
	runEPButton->Hide();

	tblChoice->Hide();
	statsChoice->Hide();
	reconnectButton->Hide();
	disconnectButton->Hide();

}

void DiagnosisAnalysis::OnTblDataButtonClicked(wxCommandEvent& evt) {
	statsChoice->Hide();
	chooseStats->Hide();
	inputCtrl->Hide();
	inputSQL->Hide();
	runTDButton->Show();
	runTSButton->Hide();
	runStButton->Hide();
	runSuButton->Hide();
	runEPButton->Hide();
	outputCtrl->SetSize(550, 475);

	tblDataButton->SetWindowStyleFlag(tblDataButton->GetWindowStyleFlag() | wxBORDER_SIMPLE);

	outputCtrl->SetValue("Please Choose a Table and then click Run");

}

void DiagnosisAnalysis::OnTblStructButtonClicked(wxCommandEvent& evt) {
	//Page formatting
	statsChoice->Hide();
	chooseStats->Hide();
	inputCtrl->Hide();
	inputSQL->Hide();
	runTDButton->Hide();
	runTSButton->Show();
	runStButton->Hide();
	runSuButton->Hide();
	runEPButton->Hide();
	outputCtrl->SetSize(550, 475);


	//Setting display window output
	outputCtrl->SetValue("Please Choose a Table and then click Run");

}
void DiagnosisAnalysis::OnStatsButtonClicked(wxCommandEvent& evt) {
	//Page formatting
	statsChoice->Show();
	chooseStats->Show();
	inputCtrl->Hide();
	inputSQL->Hide();
	runTDButton->Hide();
	runTSButton->Hide();
	runStButton->Show();
	runSuButton->Hide();
	runEPButton->Hide();
	outputCtrl->SetSize(550, 475);

	outputCtrl->SetValue("Please Choose a Table and Statistic and then click Run");
}

void DiagnosisAnalysis::OnSuggestButtonClicked(wxCommandEvent& evt) {
	//Page formatting
	statsChoice->Hide();
	chooseStats->Hide();
	inputCtrl->Hide();
	inputSQL->Hide();
	runTDButton->Hide();
	runTSButton->Hide();
	runStButton->Hide();
	runSuButton->Show();
	runEPButton->Hide();
	outputCtrl->SetSize(550, 475);

	outputCtrl->SetValue("Database Suggestions shown here");
}

void DiagnosisAnalysis::OnExPlanButtonClicked(wxCommandEvent& evt) {
	//Page formatting
	statsChoice->Hide();
	chooseStats->Hide();
	inputCtrl->Show();
	inputSQL->Show();
	runTDButton->Hide();
	runTSButton->Hide();
	runStButton->Hide();
	runSuButton->Hide();
	runEPButton->Show();
	outputCtrl->SetSize(550, 250);

	outputCtrl->SetValue("Please type an SQL Statement and then click Run");
}

void DiagnosisAnalysis::OnTblChoiceSelection(wxCommandEvent& evt) {
	//Page formatting
	statsChoice->Hide();
	chooseStats->Hide();

	//functions you can use to get the selection made from the table
	wxString tblSelection = evt.GetString();
	sqlOutput = tblSelection;
	
}

void DiagnosisAnalysis::OnStatsChoiceSelection(wxCommandEvent& evt) {

	//functions you can use to get the selection made from the table
	wxString statsSelection = evt.GetString();
	sqlOutput = statsSelection;
	outputCtrl->SetValue(sqlOutput);
}

//runButton functions that lead to an output on the display window (outputCtrl)
void DiagnosisAnalysis::runTDButtonClicked(wxCommandEvent& evt) {
	outputCtrl->SetValue("");

	std::string tblSelection = (std::string)tblChoice->GetStringSelection();

	tbl = tblSelection.c_str();

	m_p.GetCommand().setCommandText("SELECT * FROM " + tbl);
	m_p.GetCommand().Execute();
	int numCols = m_p.GetCommand().FieldCount();
	for (int i = 1; i <= numCols; i++) {
		outputCtrl->AppendText("|");
		outputCtrl->AppendText(m_p.GetCommand().Field(i).Name().GetMultiByteChars());
		outputCtrl->AppendText("\t");
	}
	outputCtrl->AppendText("|");
	outputCtrl->AppendText("\n");

	// Output the row data
	while (m_p.GetCommand().FetchNext()) 
	{
		for (int i = 1; i <= numCols; i++) 
		{
			outputCtrl->AppendText("|");
			outputCtrl->AppendText(m_p.GetCommand().Field(i).asString().GetMultiByteChars());
			outputCtrl->AppendText("\t");
			outputCtrl->AppendText("\t");
		}
		outputCtrl->AppendText("|");
		outputCtrl->AppendText("\n");
	}
	//Test string to check for scrolling
}

void DiagnosisAnalysis::runTSButtonClicked(wxCommandEvent& evt) {
	outputCtrl->SetValue("Table Structure Shown");


}
void DiagnosisAnalysis::runStButtonClicked(wxCommandEvent& evt) {
	outputCtrl->SetValue("Statistic Shown");
}
void DiagnosisAnalysis::runSuButtonClicked(wxCommandEvent& evt) {
	outputCtrl->SetValue("Suggestion Shown");
}
void DiagnosisAnalysis::runEPButtonClicked(wxCommandEvent& evt) {
	std::string sql = (std::string)inputCtrl->GetValue();

	outputCtrl->SetValue(sql);
}

void DiagnosisAnalysis::reconnectButtonClicked(wxCommandEvent& evt) {

	outputCtrl->Hide();
	chooseTable->Hide();
	chooseStats->Hide();

	tblDataButton->Hide();
	tblStructButton->Hide();
	statsButton->Hide();
	suggestionsButton->Hide();
	exPlanButton->Hide();

	runTDButton->Hide();
	runTSButton->Hide();
	runStButton->Hide();
	runSuButton->Hide();
	runEPButton->Hide();

	tblChoice->Hide();
	statsChoice->Hide();
	reconnectButton->Hide();
	disconnectButton->Hide();

	m_hostLabel->Show();
	m_hostText->Show();
	m_portLabel->Show();
	m_portText->Show();
	m_serviceLabel->Show();
	m_serviceComboBox->Show();
	m_otherServiceText->Show();
	m_usernameLabel->Show();
	m_usernameText->Show();
	m_passwordLabel->Show();
	m_passwordText->Show();
	m_connectButton->Show();


}

void DiagnosisAnalysis::disconnectButtonClicked(wxCommandEvent& evt) {
	bool isConnected = false;
	if (isConnected != true) {
		wxLogMessage("You have been disconnected.");
	}
	else {
		return;
	}
}

void DiagnosisAnalysis::connectButtonClicked(wxCommandEvent& evt)
{
	wxString host = m_hostText->GetValue();
	wxString port = m_portText->GetValue();
	wxString service = m_serviceComboBox->GetValue(); // Get the value from the wxComboBox instead of wxTextCtrl
	if (service == "Other")
	{
		service = m_otherServiceText->GetValue();
	}
	wxString username = m_usernameText->GetValue();
	wxString password = m_passwordText->GetValue();

	m_p.connection((std::string)username, (std::string)password, (std::string)service, (std::string)host, (std::string)port);

	m_p.GetCommand().setCommandText("SELECT table_name FROM user_tables");
	m_p.GetCommand().Execute();

	while (m_p.GetCommand().FetchNext())
	{
		tblChoice->Append((std::string)m_p.GetCommand().Field("TABLE_NAME").asString());

	}

	m_hostLabel->Hide();
	m_hostText->Hide();
	m_portLabel->Hide();
	m_portText->Hide();
	m_serviceLabel->Hide();
	m_serviceComboBox->Hide();
	m_otherServiceText->Hide();
	m_usernameLabel->Hide();
	m_usernameText->Hide();
	m_passwordLabel->Hide();
	m_passwordText->Hide();
	m_connectButton->Hide();

	outputCtrl->Show();
	chooseTable->Show();
	chooseStats->Hide();
	tblDataButton->Show();
	tblStructButton->Show();
	statsButton->Show();
	suggestionsButton->Show();
	exPlanButton->Show();
	runTDButton->Show();
	runTSButton->Show();
	runStButton->Show();
	runSuButton->Show();
	runEPButton->Show();
	tblChoice->Show();
	statsChoice->Hide();
	reconnectButton->Show();
	disconnectButton->Show();


}
