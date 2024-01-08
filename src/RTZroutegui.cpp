///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
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
	m_staticText1511->SetFont( wxFont( 16, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial") ) );

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

	m_staticText32111111 = new wxStaticText( m_panel0, wxID_ANY, wxT("Turn with       "), wxDefaultPosition, wxDefaultSize, 0 );
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

	m_staticText7 = new wxStaticText( m_panel0, wxID_ANY, wxT("Route name :"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	bSizer14->Add( m_staticText7, 0, wxALL, 5 );

	m_Route = new wxTextCtrl( m_panel0, wxID_ANY, wxT("myRoute"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( m_Route, 0, wxALL, 5 );


	bSizer1311->Add( bSizer14, 0, wxEXPAND, 5 );

	m_staticline1 = new wxStaticLine( m_panel0, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer1311->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );

	wxString m_choiceSchemaChoices[] = { wxT("RTZ_Schema_version_1_0"), wxT("RTZ_Schema_version_1_1"), wxT("RTZ_Schema_version_1_2"), wxEmptyString };
	int m_choiceSchemaNChoices = sizeof( m_choiceSchemaChoices ) / sizeof( wxString );
	m_choiceSchema = new wxChoice( m_panel0, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceSchemaNChoices, m_choiceSchemaChoices, 0 );
	m_choiceSchema->SetSelection( 0 );
	bSizer13->Add( m_choiceSchema, 0, wxALL, 5 );

	m_staticline3 = new wxStaticLine( m_panel0, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer13->Add( m_staticline3, 0, wxEXPAND | wxALL, 5 );


	bSizer1311->Add( bSizer13, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer71;
	bSizer71 = new wxBoxSizer( wxVERTICAL );

	m_button3111 = new wxButton( m_panel0, wxID_ANY, wxT("Edit GPX"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button3111->Hide();

	bSizer71->Add( m_button3111, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5 );

	m_staticText15111 = new wxStaticText( m_panel0, wxID_ANY, wxT("Files"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15111->Wrap( -1 );
	m_staticText15111->SetFont( wxFont( 16, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial") ) );

	bSizer71->Add( m_staticText15111, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	m_button31112 = new wxButton( m_panel0, wxID_ANY, wxT("Import"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer71->Add( m_button31112, 0, wxALL|wxEXPAND, 5 );

	m_button31113 = new wxButton( m_panel0, wxID_ANY, wxT("Export"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer71->Add( m_button31113, 0, wxALL|wxEXPAND, 5 );

	m_button311111 = new wxButton( m_panel0, wxID_ANY, wxT("         Export GPX with radius turns"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer71->Add( m_button311111, 0, wxALL, 5 );

	m_staticline7 = new wxStaticLine( m_panel0, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer71->Add( m_staticline7, 0, wxEXPAND | wxALL, 5 );

	m_button311131 = new wxButton( m_panel0, wxID_ANY, wxT("Validate RTZ"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer71->Add( m_button311131, 0, wxALL|wxEXPAND, 5 );


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
	m_staticText11->SetFont( wxFont( 16, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial") ) );

	bSizer12->Add( m_staticText11, 0, wxALL, 5 );

	m_listBoxWaypoints = new wxListBox( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_ALWAYS_SB|wxLB_SINGLE );
	bSizer12->Add( m_listBoxWaypoints, 6, wxALL|wxEXPAND, 5 );

	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( m_panel1, wxID_ANY, wxT("Waypoint Data") ), wxVERTICAL );

	gSizer1 = new wxGridSizer( 1, 2, 0, 0 );

	m_staticText81 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Latitude"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText81->Wrap( -1 );
	gSizer1->Add( m_staticText81, 0, wxALL, 5 );

	m_wptLat = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_wptLat, 0, wxALIGN_CENTER|wxALIGN_RIGHT, 0 );

	m_staticText811 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Longitude"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText811->Wrap( -1 );
	gSizer1->Add( m_staticText811, 0, wxALL, 5 );

	m_wptLon = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_wptLon, 0, wxALL, 5 );

	m_staticText812 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Turn radius (nm)     "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText812->Wrap( -1 );
	gSizer1->Add( m_staticText812, 0, wxALL, 5 );

	m_getTurnRadius = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
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
	m_button31111->Hide();

	bSizer18->Add( m_button31111, 0, wxALL, 5 );

	m_button311112 = new wxButton( m_panel1, wxID_ANY, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button311112->Hide();

	bSizer18->Add( m_button311112, 0, wxALL, 5 );


	bSizer12->Add( bSizer18, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer121;
	bSizer121 = new wxBoxSizer( wxVERTICAL );

	m_textCtrlShowResult = new wxTextCtrl( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlShowResult->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );
	m_textCtrlShowResult->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNFACE ) );

	bSizer121->Add( m_textCtrlShowResult, 0, wxEXPAND, 5 );


	bSizer12->Add( bSizer121, 1, wxEXPAND, 5 );


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
	m_button31112->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_Dialog::OnImport ), NULL, this );
	m_button31113->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_Dialog::OnExport ), NULL, this );
	m_button311111->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_Dialog::OnGenerateRadiusGPX ), NULL, this );
	m_button311131->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_Dialog::OnValidate ), NULL, this );
	m_listBoxWaypoints->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( m_Dialog::GetWaypointData ), NULL, this );
	m_getTurnRadius->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( m_Dialog::OnUpdateTurn ), NULL, this );
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
}

m_Dialog::~m_Dialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( m_Dialog::OnClose ) );
	m_buttonTest->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_Dialog::OnTestFunction ), NULL, this );
	m_button3111->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_Dialog::OnEditGPX ), NULL, this );
	m_button31112->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_Dialog::OnImport ), NULL, this );
	m_button31113->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_Dialog::OnExport ), NULL, this );
	m_button311111->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_Dialog::OnGenerateRadiusGPX ), NULL, this );
	m_button311131->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_Dialog::OnValidate ), NULL, this );
	m_listBoxWaypoints->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( m_Dialog::GetWaypointData ), NULL, this );
	m_getTurnRadius->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( m_Dialog::OnUpdateTurn ), NULL, this );
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

}
