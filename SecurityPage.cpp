#include "SecurityPage.h"
#include "wx/wx.h"
#include <wx/spinctrl.h>
#include <string>
#include "BckEnd.h"


SecurityPage::SecurityPage(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	// Setting the windows
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



	outputCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(225, 100), wxSize(550, 475), wxTE_MULTILINE | wxTE_READONLY | wxHSCROLL | wxVSCROLL | wxTE_RICH2);



	AllUserButton = new wxButton(panel, wxID_ANY, "All Users", wxPoint(275, 50), wxSize(100, 30));
	AllUserButton->SetBackgroundColour(wxColour(132, 220, 198));
	ActivityLogButton = new wxButton(panel, wxID_ANY, "Activity Log", wxPoint(400, 50), wxSize(100, 30));
	ActivityLogButton->SetBackgroundColour(wxColour(132, 220, 198));
	UsrPrivlageButton = new wxButton(panel, wxID_ANY, "User Privlage", wxPoint(525, 50), wxSize(100, 30));
	UsrPrivlageButton->SetBackgroundColour(wxColour(132, 220, 198));
	HostDetailsButton = new wxButton(panel, wxID_ANY, "Host details", wxPoint(650, 50), wxSize(100, 30));
	HostDetailsButton->SetBackgroundColour(wxColour(132, 220, 198));

	reconnectButton = new wxButton(panel, wxID_ANY, "Reconnect", wxPoint(20, 550), wxSize(75, 30), wxRAISED_BORDER);
	disconnectButton = new wxButton(panel, wxID_ANY, "Disconnect", wxPoint(110, 550), wxSize(75, 30), wxRAISED_BORDER);
	reconnectButton->SetBackgroundColour(wxColour(132, 220, 198));
	disconnectButton->SetBackgroundColour(wxColour(132, 220, 198));



	//initialising the drop downs
	tblChoice = new wxChoice(panel, wxID_ANY, wxPoint(50, 60), wxSize(120, -1), tables, wxCB_SORT);
	tblChoice->SetSelection(0);

	tblChoice->Bind(wxEVT_CHOICE, &SecurityPage::OnTblChoiceSelection, this);
	//statsChoice->Bind(wxEVT_CHOICE, &MainFrame::OnStatsChoiceSelection, this);

	//Text for the drop down menus
	chooseTable = new wxStaticText(panel, wxID_ANY, "Choose a table:", wxPoint(50, 40));
	chooseTable->SetForegroundColour(wxColour(255, 255, 255));
	//chooseStats = new wxStaticText(panel, wxID_ANY, "Choose a statistic:", wxPoint(50, 100));

	AllUserButton->Bind(wxEVT_BUTTON, &SecurityPage::OnAllUserButtonClicked, this);
	ActivityLogButton->Bind(wxEVT_BUTTON, &SecurityPage::OnActivityLogButtonClicked, this);
	UsrPrivlageButton->Bind(wxEVT_BUTTON, &SecurityPage::OnUsrPrivlageButtonClicked, this);
	HostDetailsButton->Bind(wxEVT_BUTTON, &SecurityPage::OnHostDetailsButtonClicked, this);
	reconnectButton->Bind(wxEVT_BUTTON, &SecurityPage::reconnectButtonClicked, this);
	disconnectButton->Bind(wxEVT_BUTTON, &SecurityPage::disconnectButtonClicked, this);
	m_connectButton->Bind(wxEVT_BUTTON, &SecurityPage::connectButtonClicked, this);




	//Hiding Security Widgets:

	outputCtrl->Hide();
	tblChoice->Hide();
	chooseTable->Hide();

	AllUserButton->Hide();
	ActivityLogButton->Hide();
	UsrPrivlageButton->Hide();
	HostDetailsButton->Hide();
	reconnectButton->Hide();
	disconnectButton->Hide();

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

void SecurityPage::reconnectButtonClicked(wxCommandEvent& evt) {

	outputCtrl->Hide();
	tblChoice->Hide();
	chooseTable->Hide();

	AllUserButton->Hide();
	ActivityLogButton->Hide();
	UsrPrivlageButton->Hide();
	HostDetailsButton->Hide();
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

void SecurityPage::disconnectButtonClicked(wxCommandEvent& evt) {
	bool isConnected = false;
	if (isConnected != true) {
		wxLogMessage("You have been disconnected.");
	}
	else {
		return;
	}
}

void SecurityPage::connectButtonClicked(wxCommandEvent& evt) {

	wxString host = m_hostText->GetValue();
	wxString port = m_portText->GetValue();
	wxString service = m_serviceComboBox->GetValue(); // Get the value from the wxComboBox instead of wxTextCtrl
	if (service == "Other")
	{
		service = m_otherServiceText->GetValue();
	}
	wxString username = m_usernameText->GetValue();
	wxString password = m_passwordText->GetValue();


	//Remember to use tables->Append() here to add tables

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
	tblChoice->Show();
	chooseTable->Show();

	AllUserButton->Show();
	ActivityLogButton->Show();
	UsrPrivlageButton->Show();
	HostDetailsButton->Show();
	reconnectButton->Show();
	disconnectButton->Show();

}