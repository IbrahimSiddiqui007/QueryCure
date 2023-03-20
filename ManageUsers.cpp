#include "ManageUsers.h"
#include "BckEnd.h"
#include "DiagnosisAnalysis.h"



ManageUsers::ManageUsers(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
    m_panel = new wxPanel(this, wxID_ANY);
    m_panel->SetBackgroundColour(wxColour(27, 28, 29));

    // Host input
    m_hostLabel = new wxStaticText(m_panel, wxID_ANY, "Host:");
    m_hostLabel->SetForegroundColour(wxColour(255, 255, 255));
    m_hostText = new wxTextCtrl(m_panel, wxID_ANY);

    // Port input
    m_portLabel = new wxStaticText(m_panel, wxID_ANY, "Port:");
    m_portLabel->SetForegroundColour(wxColour(255, 255, 255));
    m_portText = new wxTextCtrl(m_panel, wxID_ANY);

    // Service input
    m_serviceLabel = new wxStaticText(m_panel, wxID_ANY, "Service:");
    m_serviceLabel->SetForegroundColour(wxColour(255, 255, 255));
    wxString choices[] = { "Oracle VM", "Oracle Express Edition", "Other" }; // Create choices for the wxComboBox
    m_serviceComboBox = new wxComboBox(m_panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, WXSIZEOF(choices), choices, wxCB_DROPDOWN);
    m_otherServiceText = new wxTextCtrl(m_panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    m_otherServiceText->Hide(); // Hide the wxTextCtrl initially

    // Username input
    m_usernameLabel = new wxStaticText(m_panel, wxID_ANY, "Username:");
    m_usernameLabel->SetForegroundColour(wxColour(255, 255, 255));
    m_usernameText = new wxTextCtrl(m_panel, wxID_ANY);

    // Password input
    m_passwordLabel = new wxStaticText(m_panel, wxID_ANY, "Password:");
    m_passwordLabel->SetForegroundColour(wxColour(255, 255, 255));
    m_passwordText = new wxTextCtrl(m_panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);

    // Connect button
    m_connectButton = new wxButton(m_panel, wxID_ANY, "Connect");
    m_connectButton->SetBackgroundColour(wxColour(0, 177, 89));
    m_connectButton->SetForegroundColour(wxColour(255, 255, 255));

    // Create sizer for layout
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    
    // Add connect button to sizer
    sizer->AddSpacer(20);
    sizer->Add(m_connectButton, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT | wxBOTTOM, 20);

    // Add host input to sizer
    sizer->AddSpacer(20);
    sizer->Add(m_hostLabel, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT, 20);
    sizer->Add(m_hostText, 0, wxEXPAND | wxLEFT | wxRIGHT, 20);

    // Add port input to sizer
    sizer->AddSpacer(10);
    sizer->Add(m_portLabel, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT, 20);
    sizer->Add(m_portText, 0, wxEXPAND | wxLEFT | wxRIGHT, 20);

    // Add service input to sizer
    sizer->AddSpacer(10);
    sizer->Add(m_serviceLabel, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT, 20);
    sizer->Add(m_serviceComboBox, 0, wxEXPAND | wxLEFT | wxRIGHT, 20); // Add the wxComboBox instead of wxTextCtrl
    sizer->Add(m_otherServiceText, 0, wxEXPAND | wxLEFT | wxRIGHT, 20); // Add the wxTextCtrl for "Other" option

    // Add username input to sizer
    sizer->AddSpacer(10);
    sizer->Add(m_usernameLabel, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT, 20);
    sizer->Add(m_usernameText, 0, wxEXPAND | wxLEFT | wxRIGHT, 20);

    // Add password input to sizer
    sizer->AddSpacer(10);
    sizer->Add(m_passwordLabel, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT, 20);
    sizer->Add(m_passwordText, 0, wxEXPAND | wxLEFT | wxRIGHT, 20);

    sizer->AddSpacer(50);

    // Set sizer for panel and frame
    m_panel->SetSizer(sizer);
    sizer->Fit(m_panel);

    wxBoxSizer* outerSizer = new wxBoxSizer(wxVERTICAL);
    outerSizer->AddSpacer(20);
    outerSizer->Add(m_panel, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 20);

    SetSizer(outerSizer);

    // Bind event handler for service combo box
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
            m_panel->Layout();
        });

    // Bind event handler for connect button
    m_connectButton->Bind(wxEVT_BUTTON, [=](wxCommandEvent&) {
        wxString host = m_hostText->GetValue();
        wxString port = m_portText->GetValue();
        wxString service = m_serviceComboBox->GetValue(); // Get the value from the wxComboBox instead of wxTextCtrl
        if (service == "Other")
        {
            service = m_otherServiceText->GetValue();
        }
        wxString username = m_usernameText->GetValue();
        wxString password = m_passwordText->GetValue();



        });
}


