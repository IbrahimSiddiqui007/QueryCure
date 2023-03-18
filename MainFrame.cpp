#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include "SecurityFrame.h"
#include "SecurityPage.h"
#include "DiagnosisAnalysis.h"
#include "ManageUsers.h"
#include "BckEnd.h"




MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {

	wxPanel* panel = new wxPanel(this);

	// Query Cure
	//----------------------------------------------------------------------------------------
		
	// Displaying Database Connection Status

	bool isConnected = false;
	
	wxStaticText* connection = new wxStaticText(panel, wxID_ANY, "Database Connection Status : [Connected / Disconnected]", wxPoint(10, 10));

	if (isConnected)
	{
		connection->SetLabelText("Database Connection Status: Connected");
	}
	else
	{
		connection->SetLabelText("Database Connection Status: Disconnected");
	}

	// ---------------------------------------------------------------------------------------

	// Query Cure Title Text Code Starts Here
	wxStaticText* titleText = new wxStaticText(panel, wxID_ANY, "QueryCure", wxPoint(315, 50));
	titleText->Wrap(1000);

	// Set the font size to 24
	wxFont font(30, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	titleText->SetFont(font);

	// Query Cure Title Text Code Ends Here
	// ----------------------------------------------------------------------------------------


// ----------------------------------------------------------------------------------------

	// Drop down menu connection code starts here

	wxImage::AddHandler(new wxPNGHandler);

	// Loading the images (You have to download the photos and link to the path in your system)
	wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
	wxBitmap icon_1("C:/Users/hassa/Documents/CSCI317/oracle_3.png", wxBITMAP_TYPE_PNG);
	wxBitmap icon_2("C:/Users/hassa/Documents/CSCI317/diagnose.png", wxBITMAP_TYPE_PNG);
	wxBitmap icon_3("C:/Users/hassa/Documents/CSCI317/security.png", wxBITMAP_TYPE_PNG);


	wxStaticBitmap* iconOracle = new wxStaticBitmap(panel, wxID_ANY, icon_1);
	wxStaticBitmap* iconDiagnose = new wxStaticBitmap(panel, wxID_ANY, icon_2);
	wxStaticBitmap* iconSecurity = new wxStaticBitmap(panel, wxID_ANY, icon_3);

	// Setting the position
	iconOracle->SetPosition(wxPoint(230, 155));
	iconDiagnose->SetPosition(wxPoint(245, 250));
	iconSecurity->SetPosition(wxPoint(230, 355));

	wxFont usersFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	//users->SetFont(usersFont);

	wxButton* manageUserButton = new wxButton(panel, wxID_ANY, "Manage Users", wxPoint(325, 150), wxSize(200, 60));
	wxFont manageUserFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	manageUserButton->SetFont(manageUserFont);
	manageUserButton->Bind(wxEVT_BUTTON, &MainFrame::OnManageUserButtonClick, this);


	panel->SetSizer(hbox);

// --------------------------------------------------------------------------------------------------

	//Diagnosis Analysis Button Code starts


	wxButton* diagnosisButton = new wxButton(panel, wxID_ANY, "Diagnosis Analysis", wxPoint(325, 250), wxSize(200, 60));
	wxFont diagnosisButtonFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	diagnosisButton->SetFont(diagnosisButtonFont);
	diagnosisButton->Bind(wxEVT_BUTTON, &MainFrame::OnDiagnosisButtonClick, this);

	//Diagnosis Analysis Button Code ends here

// --------------------------------------------------------------------------------------------------

	// Security Button Code Starts Here

	wxButton* securityButton = new wxButton(panel, wxID_ANY, "Security", wxPoint(325, 350), wxSize(200, 60));
	wxFont securityButtonFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	securityButton->SetFont(securityButtonFont);
	securityButton->Bind(wxEVT_BUTTON, &MainFrame::OnSecurityButtonClick, this);

}

void MainFrame::OnSecurityButtonClick(wxCommandEvent& event)
{

	//Open the security page
	SecurityPage* securityPage = new SecurityPage("Security");
	securityPage->SetClientSize(800, 600);
	securityPage->Center();
	securityPage->Show();

}

void MainFrame::OnDiagnosisButtonClick(wxCommandEvent& event)
{

	//Open the DiagnosisAnalysis page
	DiagnosisAnalysis* diagnosis = new DiagnosisAnalysis("Diagnosis Analysis");
	diagnosis->SetClientSize(800, 600);
	diagnosis->Center();
	diagnosis->Show();

}

void MainFrame::OnManageUserButtonClick(wxCommandEvent& event)
{

	//Open the Manage Users page
	ManageUsers* manage = new ManageUsers("Manage Users");
	manage->SetClientSize(800, 600);
	manage->Center();
	manage->Show();

}





