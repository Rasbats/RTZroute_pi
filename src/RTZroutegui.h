///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statline.h>
#include <wx/sizer.h>
#include <wx/choice.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/listbox.h>
#include <wx/slider.h>
#include <wx/statbox.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class m_Dialog
///////////////////////////////////////////////////////////////////////////////
class m_Dialog : public wxDialog
{
	private:

	protected:
		wxPanel* m_panel0;
		wxStaticText* m_staticText1511;
		wxStaticLine* m_staticline2;
		wxStaticText* m_staticText32111111;
		wxStaticText* m_staticText3311111;
		wxStaticText* m_staticText7;
		wxStaticLine* m_staticline1;
		wxStaticLine* m_staticline3;
		wxButton* m_button3111;
		wxStaticText* m_staticText15111;
		wxButton* m_button31112;
		wxButton* m_button31113;
		wxButton* m_button311111;
		wxStaticLine* m_staticline7;
		wxButton* m_button311131;
		wxPanel* m_panel1;
		wxStaticText* m_staticText11;
		wxStaticText* m_staticText81;
		wxStaticText* m_staticText811;
		wxStaticText* m_staticText812;
		wxStaticText* m_staticText813;
		wxStaticText* m_staticText8111;
		wxButton* m_button31111;
		wxButton* m_button311112;

		// Virtual event handlers, override them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnTestFunction( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEditGPX( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnImport( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnExport( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGenerateRadiusGPX( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnValidate( wxCommandEvent& event ) { event.Skip(); }
		virtual void GetWaypointData( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateTurn( wxCommandEvent& event ) { event.Skip(); }
		virtual void SetRadiusValue( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnUpdate( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSaveGPX( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxButton* m_buttonTest;
		wxChoice* m_TurnStep;
		wxTextCtrl* m_Route;
		wxChoice* m_choiceSchema;
		wxListBox* m_listBoxWaypoints;
		wxStaticBoxSizer* sbSizer1;
		wxGridSizer* gSizer1;
		wxTextCtrl* m_wptLat;
		wxTextCtrl* m_wptLon;
		wxTextCtrl* m_getTurnRadius;
		wxSlider* m_sliderRadius;
		wxTextCtrl* m_nextCourse;
		wxTextCtrl* m_nextDistance;
		wxTextCtrl* m_textCtrlShowResult;

		m_Dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("RTZroute"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );

		~m_Dialog();

};

