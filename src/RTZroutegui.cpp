///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "RTZroutegui.h"

///////////////////////////////////////////////////////////////////////////

m_Dialog::m_Dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer9111;
	bSizer9111 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );

	m_panel0 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer1311;
	bSizer1311 = new wxBoxSizer( wxVERTICAL );

	m_staticText1511 = new wxStaticText( m_panel0, wxID_ANY, wxT("Options"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1511->Wrap( -1 );
	m_staticText1511->SetFont( wxFont( 20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer1311->Add( m_staticText1511, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	m_buttonTest = new wxButton( m_panel0, wxID_ANY, wxT("Testing Functions"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonTest->Hide();

	bSizer1311->Add( m_buttonTest, 0, wxALIGN_CENTER|wxALL, 5 );

	m_staticline2 = new wxStaticLine( m_panel0, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1311->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer14111112;
	bSizer14111112 = new wxBoxSizer( wxVERTICAL );


	bSizer1311->Add( bSizer14111112, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer14111111;
	bSizer14111111 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText32111111 = new wxStaticText( m_panel0, wxID_ANY, wxT("Turn with"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText32111111->Wrap( -1 );
	bSizer14111111->Add( m_staticText32111111, 0, wxALIGN_RIGHT|wxALL, 5 );

	wxString m_TurnStepChoices[] = { wxT("2"), wxT("5"), wxT("10"), wxT("20") };
	int m_TurnStepNChoices = sizeof( m_TurnStepChoices ) / sizeof( wxString );
	m_TurnStep = new wxChoice( m_panel0, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_TurnStepNChoices, m_TurnStepChoices, 0 );
	m_TurnStep->SetSelection( 0 );
	bSizer14111111->Add( m_TurnStep, 0, wxALL, 5 );

	m_staticText3311111 = new wxStaticText( m_panel0, wxID_ANY, wxT("degree steps"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3311111->Wrap( -1 );
	bSizer14111111->Add( m_staticText3311111, 0, wxALL, 5 );


	bSizer1311->Add( bSizer14111111, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText7 = new wxStaticText( m_panel0, wxID_ANY, wxT("Route / GPX   \nfile name     "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	bSizer14->Add( m_staticText7, 0, wxALL, 5 );

	m_Route = new wxTextCtrl( m_panel0, wxID_ANY, wxT("RTZ"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( m_Route, 0, wxALL, 5 );


	bSizer1311->Add( bSizer14, 0, wxEXPAND, 5 );

	m_staticline1 = new wxStaticLine( m_panel0, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1311->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer71;
	bSizer71 = new wxBoxSizer( wxVERTICAL );

	m_button3111 = new wxButton( m_panel0, wxID_ANY, wxT("Edit GPX"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer71->Add( m_button3111, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	m_staticText71 = new wxStaticText( m_panel0, wxID_ANY, wxT("... Edit an existing GPX file\n\n... update the waypoint information\n    for a radius turn\n... save the waypoint data in a GPX file\n... generate a GPX with the added\n    positions for the turns"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText71->Wrap( -1 );
	bSizer71->Add( m_staticText71, 0, wxALL, 5 );


	bSizer1311->Add( bSizer71, 0, wxEXPAND, 5 );


	m_panel0->SetSizer( bSizer1311 );
	m_panel0->Layout();
	bSizer1311->Fit( m_panel0 );
	bSizer9->Add( m_panel0, 0, wxEXPAND | wxALL, 5 );


	bSizer9111->Add( bSizer9, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );

	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );

	m_staticText11 = new wxStaticText( m_panel1, wxID_ANY, wxT("Waypoints"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	m_staticText11->SetFont( wxFont( 20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer12->Add( m_staticText11, 0, wxALL, 5 );

	m_listBoxWaypoints = new wxListBox( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_ALWAYS_SB|wxLB_SINGLE );
	bSizer12->Add( m_listBoxWaypoints, 5, wxALL|wxEXPAND, 5 );

	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( m_panel1, wxID_ANY, wxT("Waypoint Data") ), wxVERTICAL );

	gSizer1 = new wxGridSizer( 1, 2, 0, 0 );

	m_staticText81 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Latitude"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText81->Wrap( -1 );
	gSizer1->Add( m_staticText81, 0, wxALL, 5 );

	m_wptLat = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxT("1.0"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_wptLat, 0, wxALIGN_CENTER|wxALIGN_RIGHT, 0 );

	m_staticText811 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Longitude"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText811->Wrap( -1 );
	gSizer1->Add( m_staticText811, 0, wxALL, 5 );

	m_wptLon = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxT("1.0"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_wptLon, 0, wxALL, 5 );

	m_staticText812 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Turn radius (nm)     "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText812->Wrap( -1 );
	gSizer1->Add( m_staticText812, 0, wxALL, 5 );

	m_getTurnRadius = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxT("0.0"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_getTurnRadius, 0, wxALL, 5 );


	sbSizer1->Add( gSizer1, 1, 0, 5 );

	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxVERTICAL );

	m_sliderRadius = new wxSlider( sbSizer1->GetStaticBox(), wxID_ANY, 1852, 0, 3704, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer20->Add( m_sliderRadius, 1, wxALL|wxEXPAND, 5 );


	sbSizer1->Add( bSizer20, 0, wxEXPAND, 5 );

	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer( 0, 2, 0, 0 );

	m_staticText813 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Course"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText813->Wrap( -1 );
	m_staticText813->Hide();

	gSizer2->Add( m_staticText813, 1, wxALL, 5 );

	m_nextCourse = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxT("1.0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_nextCourse->Hide();

	gSizer2->Add( m_nextCourse, 0, wxALL, 5 );

	m_staticText8111 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Distance"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8111->Wrap( -1 );
	m_staticText8111->Hide();

	gSizer2->Add( m_staticText8111, 0, wxALL, 5 );

	m_nextDistance = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxT("1.0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_nextDistance->Hide();

	gSizer2->Add( m_nextDistance, 0, wxALL, 5 );


	sbSizer1->Add( gSizer2, 0, 0, 5 );


	bSizer12->Add( sbSizer1, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxHORIZONTAL );

	m_button31111 = new wxButton( m_panel1, wxID_ANY, wxT("Update"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer18->Add( m_button31111, 0, wxALL, 5 );

	m_button311112 = new wxButton( m_panel1, wxID_ANY, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer18->Add( m_button311112, 0, wxALL, 5 );

	m_button311111 = new wxButton( m_panel1, wxID_ANY, wxT("Generate GPX"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer18->Add( m_button311111, 0, wxALL, 5 );


	bSizer12->Add( bSizer18, 0, wxEXPAND, 5 );


	m_panel1->SetSizer( bSizer12 );
	m_panel1->Layout();
	bSizer12->Fit( m_panel1 );
	bSizer10->Add( m_panel1, 0, wxEXPAND | wxALL, 5 );


	bSizer9111->Add( bSizer10, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer9111 );
	this->Layout();
	bSizer9111->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( m_Dialog::OnClose ) );
	m_buttonTest->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_Dialog::OnTestFunction ), NULL, this );
	m_button3111->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_Dialog::OnEditGPX ), NULL, this );
	m_listBoxWaypoints->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( m_Dialog::GetWaypointData ), NULL, this );
	m_sliderRadius->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( m_Dialog::SetRadiusValue ), NULL, this );
	m_sliderRadius->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( m_Dialog::SetRadiusValue ), NULL, this );
	m_sliderRadius->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( m_Dialog::SetRadiusValue ), NULL, this );
	m_sliderRadius->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( m_Dialog::SetRadiusValue ), NULL, this );
	m_sliderRadius->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( m_Dialog::SetRadiusValue ), NULL, this );
	m_sliderRadius->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( m_Dialog::SetRadiusValue ), NULL, this );
	m_sliderRadius->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( m_Dialog::SetRadiusValue ), NULL, this );
	m_sliderRadius->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( m_Dialog::SetRadiusValue ), NULL, this );
	m_sliderRadius->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( m_Dialog::SetRadiusValue ), NULL, this );
	m_button31111->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_Dialog::OnUpdate ), NULL, this );
	m_button311112->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_Dialog::OnSaveGPX ), NULL, this );
	m_button311111->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_Dialog::OnPSGPX ), NULL, this );
}

m_Dialog::~m_Dialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( m_Dialog::OnClose ) );
	m_buttonTest->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_Dialog::OnTestFunction ), NULL, this );
	m_button3111->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_Dialog::OnEditGPX ), NULL, this );
	m_listBoxWaypoints->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( m_Dialog::GetWaypointData ), NULL, this );
	m_sliderRadius->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( m_Dialog::SetRadiusValue ), NULL, this );
	m_sliderRadius->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( m_Dialog::SetRadiusValue ), NULL, this );
	m_sliderRadius->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( m_Dialog::SetRadiusValue ), NULL, this );
	m_sliderRadius->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( m_Dialog::SetRadiusValue ), NULL, this );
	m_sliderRadius->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( m_Dialog::SetRadiusValue ), NULL, this );
	m_sliderRadius->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( m_Dialog::SetRadiusValue ), NULL, this );
	m_sliderRadius->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( m_Dialog::SetRadiusValue ), NULL, this );
	m_sliderRadius->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( m_Dialog::SetRadiusValue ), NULL, this );
	m_sliderRadius->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( m_Dialog::SetRadiusValue ), NULL, this );
	m_button31111->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_Dialog::OnUpdate ), NULL, this );
	m_button311112->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_Dialog::OnSaveGPX ), NULL, this );
	m_button311111->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_Dialog::OnPSGPX ), NULL, this );

}
