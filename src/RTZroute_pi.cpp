/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  RTZroute Plugin
 * Author:   Mike Rossiter
 *
 ***************************************************************************
 *   Copyright (C) 2013 by Mike Rossiter                                *
 *   $EMAIL$                                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************
 */

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

#include "RTZroute_pi.h"
#include "RTZroutegui_impl.h"
#include "RTZroutegui.h"


// the class factories, used to create and destroy instances of the PlugIn

extern "C" DECL_EXP opencpn_plugin* create_pi(void *ppimgr)
{
    return new RTZroute_pi(ppimgr);
}

extern "C" DECL_EXP void destroy_pi(opencpn_plugin* p)
{
    delete p;
}

//---------------------------------------------------------------------------------------------------------
//
//    RTZroute PlugIn Implementation
//
//---------------------------------------------------------------------------------------------------------

#include "icons.h"

//---------------------------------------------------------------------------------------------------------
//
//          PlugIn initialization and de-init
//
//---------------------------------------------------------------------------------------------------------

RTZroute_pi::RTZroute_pi(void *ppimgr)
      :opencpn_plugin_17 (ppimgr)
{
      // Create the PlugIn icons
      initialize_images();

	  wxString shareLocn = *GetpSharedDataLocation() +
		  _T("plugins") + wxFileName::GetPathSeparator() +
		  _T("RTZroute_pi") + wxFileName::GetPathSeparator()
		  + _T("data") + wxFileName::GetPathSeparator();
	  wxImage panelIcon(shareLocn + _T("RTZroute_pi_panel_icon.png"));
	  if (panelIcon.IsOk())
		  m_panelBitmap = wxBitmap(panelIcon);
	  else
		  wxLogMessage(_T("    RTZroute_pi panel icon NOT loaded"));
	  m_bShowRTZroute = false;
}

RTZroute_pi::~RTZroute_pi(void)
{
     delete _img_RTZroute_pi;
     delete _img_RTZroute;
     
}

int RTZroute_pi::Init(void)
{
      AddLocaleCatalog( _T("opencpn-RTZroute_pi") );

      // Set some default private member parameters
      m_route_dialog_x = 0;
      m_route_dialog_y = 0;
      ::wxDisplaySize(&m_display_width, &m_display_height);

      //    Get a pointer to the opencpn display canvas, to use as a parent for the POI Manager dialog
      m_parent_window = GetOCPNCanvasWindow();

      //    Get a pointer to the opencpn configuration object
      m_pconfig = GetOCPNConfigObject();

      //    And load the configuration items
      LoadConfig();

      //    This PlugIn needs a toolbar icon, so request its insertion
	if(m_bRTZrouteShowIcon)

#ifdef RTZroute_USE_SVG
		m_leftclick_tool_id = InsertPlugInToolSVG(_T("RTZroute"), _svg_RTZroute, _svg_RTZroute, _svg_RTZroute_toggled,
			wxITEM_CHECK, _("RTZroute"), _T(""), NULL, CALCULATOR_TOOL_POSITION, 0, this);
#else
		m_leftclick_tool_id = InsertPlugInTool(_T(""), _img_RTZroute, _img_RTZroute, wxITEM_CHECK,
			_("RTZroute"), _T(""), NULL,
			CALCULATOR_TOOL_POSITION, 0, this);
#endif
    

      m_pDialog = NULL;

      return (WANTS_OVERLAY_CALLBACK |
              WANTS_OPENGL_OVERLAY_CALLBACK |
		  
		      WANTS_CURSOR_LATLON      |
              WANTS_TOOLBAR_CALLBACK    |
              INSTALLS_TOOLBAR_TOOL     |
              WANTS_CONFIG             |
			  WANTS_PLUGIN_MESSAGING

           );
}

bool RTZroute_pi::DeInit(void)
{
      //    Record the dialog position
      if (NULL != m_pDialog)
      {
            //Capture dialog position
            wxPoint p = m_pDialog->GetPosition();
            SetCalculatorDialogX(p.x);
            SetCalculatorDialogY(p.y);
            m_pDialog->Close();
            delete m_pDialog;
            m_pDialog = NULL;

			m_bShowRTZroute = false;
			SetToolbarItemState( m_leftclick_tool_id, m_bShowRTZroute );

      }	
    
    SaveConfig();

    RequestRefresh(m_parent_window); // refresh main window

    return true;
}

int RTZroute_pi::GetAPIVersionMajor()
{
      return MY_API_VERSION_MAJOR;
}

int RTZroute_pi::GetAPIVersionMinor()
{
      return MY_API_VERSION_MINOR;
}

int RTZroute_pi::GetPlugInVersionMajor()
{
      return PLUGIN_VERSION_MAJOR;
}

int RTZroute_pi::GetPlugInVersionMinor()
{
      return PLUGIN_VERSION_MINOR;
}

wxBitmap *RTZroute_pi::GetPlugInBitmap()
{
      return &m_panelBitmap;
}

wxString RTZroute_pi::GetCommonName()
{
      return _("RTZroute");
}


wxString RTZroute_pi::GetShortDescription()
{
      return _("RTZroute Positions using GPX files");
}

wxString RTZroute_pi::GetLongDescription()
{
      return _("Creates GPX files with\n\
RTZroute Positions");
}

int RTZroute_pi::GetToolbarToolCount(void)
{
      return 1;
}

void RTZroute_pi::SetColorScheme(PI_ColorScheme cs)
{
      if (NULL == m_pDialog)
            return;

      DimeWindow(m_pDialog);
}

void RTZroute_pi::OnToolbarToolCallback(int id)
{
    
	if(NULL == m_pDialog)
      {
            m_pDialog = new Dlg(m_parent_window, this);
            m_pDialog->Move(wxPoint(m_route_dialog_x, m_route_dialog_y));
      }

	  m_pDialog->Fit();
	  //Toggle 
	  m_bShowRTZroute = !m_bShowRTZroute;	  

      //    Toggle dialog? 
      if(m_bShowRTZroute) {
          m_pDialog->Show();         
      } else
          m_pDialog->Hide();
     
      // Toggle is handled by the toolbar but we must keep plugin manager b_toggle updated
      // to actual status to ensure correct status upon toolbar rebuild
      SetToolbarItemState( m_leftclick_tool_id, m_bShowRTZroute );

      RequestRefresh(m_parent_window); // refresh main window
}

bool RTZroute_pi::LoadConfig(void)
{
      wxFileConfig *pConf = (wxFileConfig *)m_pconfig;

      if(pConf)
      {
            pConf->SetPath ( _T( "/Settings/RTZroute_pi" ) );
			 pConf->Read ( _T( "ShowRTZrouteIcon" ), &m_bRTZrouteShowIcon, 1 );
           
            m_route_dialog_x =  pConf->Read ( _T ( "DialogPosX" ), 20L );
            m_route_dialog_y =  pConf->Read ( _T ( "DialogPosY" ), 20L );
         
            if((m_route_dialog_x < 0) || (m_route_dialog_x > m_display_width))
                  m_route_dialog_x = 5;
            if((m_route_dialog_y < 0) || (m_route_dialog_y > m_display_height))
                  m_route_dialog_y = 5;
            return true;
      }
      else
            return false;
}

bool RTZroute_pi::SaveConfig(void)
{
      wxFileConfig *pConf = (wxFileConfig *)m_pconfig;

      if(pConf)
      {
            pConf->SetPath ( _T ( "/Settings/RTZroute_pi" ) );
			pConf->Write ( _T ( "ShowRTZrouteIcon" ), m_bRTZrouteShowIcon );
          
            pConf->Write ( _T ( "DialogPosX" ),   m_route_dialog_x );
            pConf->Write ( _T ( "DialogPosY" ),   m_route_dialog_y );
            
            return true;
      }
      else
            return false;
}

void RTZroute_pi::OnRTZrouteDialogClose()
{
    m_bShowRTZroute = false;
    SetToolbarItemState( m_leftclick_tool_id, m_bShowRTZroute );
    m_pDialog->Hide();
    SaveConfig();

    RequestRefresh(m_parent_window); // refresh main window

}


