/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  RTZroute Plugin
 * Author:   Mike Rossiter
 *
 ***************************************************************************
 *   Copyright (C) 2013 by Mike Rossiter                                   *
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

#include "RTZroutegui_impl.h"
#include "RTZroutegui.h"
#include "RTZroute_pi.h"
#include "icons.h"

#include <wx/progdlg.h>
#include <wx/wx.h>
#include "wx/dir.h"
#include <list>
#include <cmath>


#define FAIL(X) do { error = X; goto failed; } while(0)

Dlg::Dlg(wxWindow *parent, RTZroute_pi *ppi)
	: m_Dialog(parent)
{
	this->Fit();
	dbg = false; //for debug output set to true
	
	pPlugIn = ppi;
	pParent = parent;

	wxString blank_name = *GetpSharedDataLocation()
		+ _T("plugins/RTZroute_pi/data/blank.ico");

	wxIcon icon(blank_name, wxBITMAP_TYPE_ICO);
	SetIcon(icon);
	testing = false;
}

Dlg::~Dlg()
{
	
}

void Dlg::SetRadiusValue(wxScrollEvent& event) {

	turnRadius = this->m_sliderRadius->GetValue();
	turnRadius /= 1852;
	wxString string_radius = wxString::Format("%0.1f", turnRadius);
	this->m_getTurnRadius->SetValue(string_radius);

}



void Dlg::Addpoint(TiXmlElement* Route, wxString ptlat, wxString ptlon, wxString ptname, wxString ptsym, wxString pttype, wxString ptviz, wxString ptradius){
//add point
	
	
	TiXmlElement * RoutePoint = new TiXmlElement( "rtept" );
    RoutePoint->SetAttribute("lat", ptlat.mb_str());
    RoutePoint->SetAttribute("lon", ptlon.mb_str());


    TiXmlElement * Name = new TiXmlElement( "name" );
    TiXmlText * text = new TiXmlText( ptname.mb_str() );
    RoutePoint->LinkEndChild( Name );
    Name->LinkEndChild( text );

    TiXmlElement * Symbol = new TiXmlElement( "sym" );
    TiXmlText * text1 = new TiXmlText( ptsym.mb_str() );
    RoutePoint->LinkEndChild( Symbol );
    Symbol->LinkEndChild( text1 );

    TiXmlElement * Type = new TiXmlElement( "type" );
    TiXmlText * text2 = new TiXmlText( pttype.mb_str() );
    RoutePoint->LinkEndChild( Type );
    Type->LinkEndChild( text2 );
	
	TiXmlElement * Extensions2 = new TiXmlElement("extensions");	

	TiXmlElement * ExtensionsViz = new TiXmlElement("opencpn:viz");	
	TiXmlText * textViz = new TiXmlText(ptviz);
	ExtensionsViz->LinkEndChild(textViz);
	Extensions2->LinkEndChild(ExtensionsViz);
	
	
	TiXmlElement * ExtensionsRadius = new TiXmlElement("opencpn:radius");
	TiXmlText * textRadius = new TiXmlText(ptradius);
	ExtensionsRadius->LinkEndChild(textRadius);
	Extensions2->LinkEndChild(ExtensionsRadius);
	//RoutePoint->LinkEndChild(ExtensionsRadius);
    
	RoutePoint->LinkEndChild(Extensions2);
    Route->LinkEndChild( RoutePoint );


//done adding point
}


void Dlg::OnTestFunction(wxCommandEvent& event)
{
	/*
	my_points.clear();
	testing = true;
	
	wxString radius_string = this->m_textCtrlTurnRadius->GetValue();
	double value;
	if (!radius_string.ToDouble(&value)) { wxLogMessage("RTZroute error obtaining radius"); }
	radius = value;

	wxRealPoint rtt, rp, rn, rtpivot, pb, pa;
	rtt = { 51, -6 };
	rp = { 50.5, -5 };
	rn = { 51.5, -5 };

	double  internal_angle;
	wxString portstbdout;

	GetPivotInfo(rtt, rp, rn, radius, rtpivot, internal_angle, portstbdout, pb, pa);	

	//wxString value = wxString::Format("%f", distancePivot);
	//wxMessageBox(value);

	RequestRefresh(m_parent); // refresh main window
	*/
}



void Dlg::GetPivotInfo(wxRealPoint rtt, wxRealPoint rtp, wxRealPoint rtn, double radius, wxRealPoint &rtpivot, double &internalAngle,  wxString &portstbd, wxRealPoint &pb, wxRealPoint &pa) {
	
	//wxString radius_string = this->m_textCtrlTurnRadius->GetValue();
	//double value;
	//if (!radius_string.ToDouble(&value)) { wxLogMessage("RTZroute error obtaining radius"); }
	//radius = value;

	double bfpc;   // bearing from previous point to the turn (centre)
	double bfnc;
	double bfcp;   // from centre to previous waypoint
	double bfcn; // from centre to next waypoint

	
	DistanceBearingMercator_Plugin(rtt.x, rtt.y,rtp.x, rtp.y,  &bfpc, &distanceToWaypoint);   // bearing from previous point to the turn (centre)
	DistanceBearingMercator_Plugin(rtt.x, rtt.y, rtn.x, rtn.y,  &bfnc, &distanceToWaypoint);
	DistanceBearingMercator_Plugin(rtp.x, rtp.y,rtt.x, rtt.y,  &bfcp, &distanceToWaypoint);   // from centre to previous waypoint
	DistanceBearingMercator_Plugin(rtn.x, rtn.y,rtt.x, rtt.y,  &bfcn, &distanceToWaypoint); // from centre to next waypoint

	double rlat, rlon;
	double halfangle;
	
	double directionPivot = calcCentreOfPivotDirection(bfpc, bfcn, portstbd, halfangle);

	//wxString twind = wxString::Format("%f", directionPivot);
	//wxMessageBox(twind);

	double distancePivot = radius / sin(halfangle * d2r);
	double rLat, rLon;
	PositionBearingDistanceMercator_Plugin(rtt.x, rtt.y, directionPivot, distancePivot, &rLat, &rLon);

	wxRealPoint rt;
	rt.x = rLat; // = { rLat, rLon };
	rt.y = rLon;

	pivotPoint = rt;

	double h = radius / tan(halfangle*d2r);

	wxRealPoint p1LatLon, p2LatLon;

	PositionBearingDistanceMercator_Plugin(rtt.x, rtt.y, bfcp, h, &p1LatLon.x, &p1LatLon.y);
	PositionBearingDistanceMercator_Plugin(rtt.x, rtt.y, bfcn, h, &p2LatLon.x, &p2LatLon.y);

	ac1 = p1LatLon;
	ac2 = p2LatLon;

	internal_angle = 2 * halfangle;
	
	//CalculateCurvePoints(ac1, ac2, pivotPoint, radius, internal_angle, portstbd);

}

void Dlg::CalculateCurvePoints(wxRealPoint ac1, wxRealPoint ac2, wxRealPoint pivotPoint, double radius, double internalAngle, wxString portstbd)
{

	Position my_point;
/*	my_point.radius = radius;
	my_point.lat = wxString::Format(wxT("%f"), pivotPoint.x);
	my_point.lon = wxString::Format(wxT("%f"), pivotPoint.y);
	my_point.routepoint = 0;
	my_point.viz = "1";
	my_point.wpt_num = "0";
	my_points.push_back(my_point);
*/


	wxRealPoint lonlatAc1, lonlatAc2, lonlatAcP;
	lonlatAcP.x = pivotPoint.y;
	lonlatAcP.y = pivotPoint.x;

	lonlatAc1.x = ac1.y;
	lonlatAc1.y = ac1.x;

	lonlatAc2.x = ac2.y;
	lonlatAc2.y = ac2.x;

	wxRealPoint xylonlatC, xylonlat1, xylonlat2, rlonlat;

	xylonlatC = ProjectPointToWebMercator(lonlatAcP);
	xylonlat1 = ProjectPointToWebMercator(lonlatAc1);
	xylonlat2 = ProjectPointToWebMercator(lonlatAc2);

	Vector2D<double> p1(xylonlatC.x, xylonlatC.y);
	Vector2D<double> p2(xylonlat1.x, xylonlat1.y);
	Vector2D<double> p3(xylonlat2.x, xylonlat2.y);

	double changeBearing = Vector2D<double>::angle(p2 - p1, p3 - p1);

	double firstBearing; //degrees
	double lastBearing; //degrees

	DistanceBearingMercator_Plugin(lonlatAc1.y, lonlatAc1.x,lonlatAcP.y, lonlatAcP.x,  &firstBearing, &distanceToWaypoint); //degrees
	DistanceBearingMercator_Plugin(lonlatAc2.y, lonlatAc2.x,lonlatAcP.y, lonlatAcP.x,  &lastBearing, &distanceToWaypoint); //degrees

	wxString value = wxString::Format("%f", changeBearing);
	//wxMessageBox(value);

	value = wxString::Format("%f", lastBearing);
	//wxMessageBox(value);

	double initVector = firstBearing * d2r;
	double lastVector = lastBearing * d2r;

	double rotate = turnStep;
	double angle = rotate * d2r;	

	double cs = cos(angle);
	double sn = sin(angle);

	int c = 0;
	int z = 0;

	double x = radius * sin(initVector);
	double y = radius * cos(initVector);
	double a = 0;


	for (c = 0; z <= 0; z++) {
		testX[z] = xylonlatC.x;  // shift origin to turning point
		testY[z] = xylonlatC.y;
	}

	testX[0] = 0;
	testY[0] = 0;

	testX[1] = radius * cos(initVector) + xylonlat1.x;
	testY[1] = radius * sin(initVector) + xylonlat1.y;

	wxRealPoint wpoint, rpoint, rllpoint, rpoint1;
	wpoint = { testX[1], testY[1] };
	rpoint1 = WebMercatorToLonLat(wpoint);

	//PlugIn_Waypoint * pPoint1 = new PlugIn_Waypoint(rpoint1.y, rpoint1.x,
		//"", "1", "");
	
	my_point.lat = wxString::Format(wxT("%f"), rpoint1.y);
	my_point.lon = wxString::Format(wxT("%f"), rpoint1.x);
	my_point.routepoint = 1;
	my_point.viz = "1";
	my_point.radius = 0;
	my_point.wpName = wxString::Format(wxT("%d"), wpt_num);
	my_points.push_back(my_point);

	wpt_num += 1;

	wxRealPoint p;
	p = wpoint;

	double totalAngle = angle;
	double Xnew;
	double Ynew;

	//for (int t = 1; t < 8; t++) {
		
		while (totalAngle < changeBearing) {
			double s = sin(angle);
			double c = cos(angle);
			
			// translate point back to origin:

			p.x -= xylonlatC.x;
			p.y -= xylonlatC.y;

			// rotate point
			if (portstbd == "P"){
				Xnew = p.x * c - p.y * s;
				Ynew = p.x * s + p.y * c;
			}
			else if (portstbd == "S") {
				Xnew = p.x * c + p.y * s;
				Ynew = -p.x * s + p.y * c;
			}
			// translate point back:
			p.x = Xnew + xylonlatC.x;
			p.y = Ynew + xylonlatC.y;

			rllpoint = WebMercatorToLonLat(p);

			//PlugIn_Waypoint * pPoint1 = new PlugIn_Waypoint(rllpoint.y, rllpoint.x,
				//"", "2", "");

			my_point.lat = wxString::Format(wxT("%f"), rllpoint.y);
			my_point.lon = wxString::Format(wxT("%f"), rllpoint.x);
			my_point.routepoint = 1;
			my_point.viz = "0";
			my_point.radius = 0;
			my_point.wpName = wxString::Format(wxT("%d"), wpt_num);
			my_points.push_back(my_point);

			wpt_num += 1;
			totalAngle = totalAngle + angle;			
		}
	//}
/*
	double fLat, fLon;

	DistanceBearingMercator(pivotPoint.x, pivotPoint.y, lastBearing, radius, &fLat, &fLon);

	value = wxString::Format("%f", radius);
	//wxMessageBox(value);

*/	

	my_point.lat = wxString::Format(wxT("%f"), ac2.x);
	my_point.lon = wxString::Format(wxT("%f"), ac2.y);	
	my_point.routepoint = 1;
	my_point.viz = "1";
	my_point.radius = 0;
	my_point.wpName = wxString::Format(wxT("%d"), wpt_num);
	my_points.push_back(my_point);

	

	if (testing) {
		
		my_point.lat = wxString::Format(wxT("%f"), pivotPoint.x);
		my_point.lon = wxString::Format(wxT("%f"), pivotPoint.y);
		my_point.routepoint = 1;
		my_point.wpt_num = wxString::Format(wxT("%d"), wpt_num);
		my_points.push_back(my_point);

		
		double lati, loni;
		double value1, value2;

		for (std::vector<Position>::iterator it = my_points.begin(); it != my_points.end(); it++) {

			if (!(*it).lat.ToDouble(&value1)) { /* error! */ }
			lati = value1;
			if (!(*it).lon.ToDouble(&value2)) { /* error! */ }
			loni = value2;

			PlugIn_Waypoint * pPoint1 = new PlugIn_Waypoint(lati, loni,
				"", "1", "");

			pPoint1->m_IconName = "Test";
			pPoint1->m_MarkDescription = "1";
			//pPoint->m_GUID = "1";
			AddSingleWaypoint(pPoint1, false);


		}

		testing = false;
		RequestRefresh(m_parent); // refresh main window

	}

}

void Dlg::OnPSGPX( wxCommandEvent& event )
{	
	Calculate(event, true, 1);
}

void Dlg::OnEditGPX(wxCommandEvent& event)
{
	OpenXML();	
}

void Dlg::OnUpdate(wxCommandEvent& event)
{
	Update();
}

void Dlg::OnSaveGPX(wxCommandEvent& event)
{
	SaveGPX();
}


void Dlg::OnClose(wxCloseEvent& event)
{	
	pPlugIn->OnRTZrouteDialogClose();
}

bool Dlg::OpenXML()
{
    Position my_position;
	
    my_positions.clear();
	
	int response = wxID_CANCEL;
	int my_count = 0;
    
	wxArrayString file_array;
    wxString filename;
	wxFileDialog openDialog( this, _( "Import GPX Route file" ), m_gpx_path, wxT ( "" ),
                wxT ( "GPX files (*.gpx)|*.gpx|All files (*.*)|*.*" ),
                wxFD_OPEN | wxFD_MULTIPLE );
        response = openDialog.ShowModal();
        if( response == wxID_OK ) {
            openDialog.GetPaths( file_array );

            //    Record the currently selected directory for later use
            if( file_array.GetCount() ) {
                wxFileName fn( file_array[0] );
				filename = file_array[0];
                m_gpx_path = fn.GetPath();
            }
        }
		else if(response = wxID_CANCEL){
		return false;
		}
    
    TiXmlDocument doc;
    wxString error;
    wxProgressDialog *progressdialog = NULL;

    
	if(!doc.LoadFile(filename.mb_str())){
        FAIL(_("Failed to load file: ") + filename);
	}
    else {
        TiXmlElement *root = doc.RootElement();
        if(!strcmp(root->Value(), "rte"))
            FAIL(_("rte Invalid xml file"));

        int count = 0;
        for(TiXmlElement* e = root->FirstChildElement(); e; e = e->NextSiblingElement())
            count++;

        int i=0;
		wxString planned_speed = "5.0";

        for(TiXmlElement* e = root->FirstChildElement(); e; e = e->NextSiblingElement(), i++) {
            if(progressdialog) {
                if(!progressdialog->Update(i))
                    return true;
			}
			else {
				if (1) {
					progressdialog = new wxProgressDialog(
						_("Route"), _("Loading"), count, this,
						wxPD_CAN_ABORT | wxPD_ELAPSED_TIME | wxPD_REMAINING_TIME);
				}
			}
			             				
                for(TiXmlElement* f = e->FirstChildElement(); f; f = f->NextSiblingElement()) {

					if (!strcmp(f->Value(), "extensions")) {						

						for (TiXmlElement* g = f->FirstChildElement(); g; g = g->NextSiblingElement()) {
							if (!strcmp(g->Value(), "opencpn:planned_speed")) {
								planned_speed = wxString::FromUTF8(g->GetText());								
								mySpeed = planned_speed;
								//wxMessageBox(planned_speed);
							}
						}
					}
					
                    if(!strcmp(f->Value(), "rtept")) {

						double value = 999;
						
						wxString wpViz = "1";
						
						my_position.viz = wpViz;   // dummy value to make sure there is an entry
						my_position.radius = 0.0;  // dummy value to make sure there is an entry
						my_position.planned_speed = planned_speed;  // dummy value to make sure there is an entry

                        wxString rte_lat = wxString::FromUTF8(f->Attribute("lat"));
						wxString rte_lon = wxString::FromUTF8(f->Attribute("lon"));
						

						my_position.lat = rte_lat;
						my_position.lon = rte_lon;
						for (TiXmlElement* g = f->FirstChildElement(); g; g = g->NextSiblingElement()) {

							if (!strcmp(g->Value(), "name")) {
								wxString wpName = wxString::FromUTF8(g->GetText());
								my_position.wpName = wpName;
								//wxMessageBox(wpName);
							}

							if (!strcmp(g->Value(), "sym")) {
								wxString wpSym = wxString::FromUTF8(g->GetText());
								my_position.wpSym = wpSym;				
							}							

 							if (!strcmp(g->Value(), "extensions")) {
								for (TiXmlElement* h = g->FirstChildElement(); h; h = h->NextSiblingElement()) {
									if (!strcmp(h->Value(), "opencpn:radius")) {
										wxString radius_string = wxString::FromUTF8(h->GetText());
										//wxMessageBox(radius_string);
										double v;
										if (!radius_string.ToDouble(&v)) { wxLogMessage("RTZroute: error obtaining radius"); }
										double radius = v;
										my_position.radius = radius;
									}	

									if (!strcmp(h->Value(), "opencpn:viz")) {
										wpViz = wxString::FromUTF8(g->GetText());									
										my_position.viz = wpViz;
									}								
								}
							}															
						}	
						
						my_position.planned_speed = mySpeed;
						my_positions.push_back(my_position);	

					}  //else if(!strcmp(f->Value(), "extensions")) {
                        //rte_start = wxString::FromUTF8(f->Attribute("opencpn:start"));
						//rte_end = wxString::FromUTF8(f->Attribute("opencpn:end"));

                    //}				
                }

				FillWaypointListbox();
        }
    }

    delete progressdialog;
    return true;

failed:
    delete progressdialog;

    wxMessageDialog mdlg(this, error, _("RTZroute"), wxOK | wxICON_ERROR);
    mdlg.ShowModal();

    return false;
}


void Dlg::Calculate( wxCommandEvent& event, bool write_file, int Pattern  ){	
	
   if(OpenXML()){

	   m_listBoxWaypoints->Clear();
	   
	  int theStep = this->m_TurnStep->GetSelection();
	  wxString step_string = this->m_TurnStep->GetString(theStep);
	  double value;
	  if (!step_string.ToDouble(&value)) { wxLogMessage("RTZroute: error obtaining turn step"); }
	  turnStep = value;



		bool error_occured=false;
		double lat1,lon1;
		wxString defaultFileName;
		defaultFileName = this->m_Route->GetValue();
	
		lat1 = 0.0;
		lon1 = 0.0;

		wxString s;

		if (write_file){
			wxFileDialog dlg(this, _("Export RTZroute Positions in GPX file as"), wxEmptyString, defaultFileName, _T("GPX files (*.gpx)|*.gpx|All files (*.*)|*.*"), wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
			if (dlg.ShowModal() == wxID_CANCEL){
				error_occured=true;     // the user changed idea...
				return;
			}
			
			//dlg.ShowModal();
			s=dlg.GetPath();
			if (dlg.GetPath() == wxEmptyString){ error_occured=true; if (dbg) printf("Empty Path\n");}
		}

		//Validate input ranges
		if (!error_occured){
			if (std::abs(lat1)>90){ error_occured=true; }
			if (std::abs(lon1)>180){ error_occured=true; }
			if (error_occured) wxMessageBox(_("error in input range validation"));
		}

		//Start GPX
		TiXmlDocument doc;
		TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "utf-8", "" );
		doc.LinkEndChild( decl );
		TiXmlElement * root = new TiXmlElement( "gpx" );
		TiXmlElement * Route = new TiXmlElement( "rte" );
		TiXmlElement * RouteName = new TiXmlElement( "name" );
		TiXmlText * text4 = new TiXmlText( this->m_Route->GetValue().ToUTF8() );
		//TiXmlText * textSpeed = new TiXmlText(this->m_Speed_PS->GetValue().ToUTF8());
	
	

    if (write_file){
        doc.LinkEndChild( root );
        root->SetAttribute("version", "1.1");
        root->SetAttribute("creator", "RTZroute_pi by Rasbats");
        root->SetAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
		root->SetAttribute("xmlns", "http://www.topografix.com/GPX/1/1");
        root->SetAttribute("xmlns:gpxx","http://www.garmin.com/xmlschemas/GpxExtensions/v3" );
        root->SetAttribute("xsi:schemaLocation", "http://www.topografix.com/GPX/1/1 http://www.topografix.com/GPX/1/1/gpx.xsd");
        root->SetAttribute("xmlns:opencpn","http://www.opencpn.org");
        Route->LinkEndChild( RouteName );		
        RouteName->LinkEndChild( text4 );


        TiXmlElement * Extensions = new TiXmlElement( "extensions" );

        TiXmlElement * StartN = new TiXmlElement( "opencpn:start" );
        TiXmlText * text5 = new TiXmlText( "Start" );
        Extensions->LinkEndChild( StartN );
        StartN->LinkEndChild( text5 );

        TiXmlElement * EndN = new TiXmlElement( "opencpn:end" );
        TiXmlText * text6 = new TiXmlText( "End" );
        Extensions->LinkEndChild( EndN );
        EndN->LinkEndChild( text6 );

		TiXmlElement * Speed = new TiXmlElement("opencpn:planned_speed");
		TiXmlText * text7 = new TiXmlText(mySpeed);
		Extensions->LinkEndChild(Speed);	
	    Speed->LinkEndChild(text7);

        Route->LinkEndChild( Extensions );
    }

    switch ( Pattern ) {
    case 1:
        {		
        if (dbg) cout<<"RTZroute Calculation\n";      
        double speed=5;
		int    interval=1;


        		
	//	if(!this->m_Speed_PS->GetValue().ToDouble(&speed)){ speed=5.0;} // 5 kts default speed
		

		interval += 1;

		speed = speed*(double)interval;

        int n=0;
        //int multiplier=1;
        double lati, loni, latp, latn;
        double latN[100], lonN[100], rad[100]; // allow for up to 100 waypoints
		wxString wpName[100];				  // allow for up to 100 waypoints
		double latF, lonF;					  
		
		Position my_point;
		wpt_num = 1;
       
		double value, value1;
		
		for(std::vector<Position>::iterator it = my_positions.begin();  it != my_positions.end(); it++){
       
			if(!(*it).lat.ToDouble(&value)){ /* error! */ }
				lati = value;
			if(!(*it).lon.ToDouble(&value1)){ /* error! */ }
				loni = value1;


			latN[n] = lati;
			lonN[n] = loni;

			rad[n] = (*it).radius;
			wpName[n] = (*it).wpName;

			n++;//0,1,2,3
		}
		
		my_positions.clear();
		my_points.clear();

		n--;//n = 2,  0,1,2
		int routepoints = n+1; //3
		
		
		double myDist, myBrng, myDistForBrng;
		int count_pts;
		double remaining_dist, myLast, route_dist;
		remaining_dist = 0;
		route_dist= 0;
		myLast = 0;
		myDistForBrng =0;
		double total_dist = 0;
		int i,c;
		bool skip = false;
		bool inloop = false;
		bool setF = false;

		wxRealPoint rp, rn, rtt, rtpivot, pb, pa;
		double internal_angle;
		wxString portstbd;

		latF = latN[0];
		lonF = lonN[0];

		// Start of new logic
		for (i=0; i<n; i++){	// n is number of routepoints		
			
			
			if (i==0){ // First F is a routepoint
			// save the routepoint
			
			my_point.lat = wxString::Format(wxT("%f"),latN[i]);
			my_point.lon = wxString::Format(wxT("%f"),lonN[i]);
			my_point.routepoint = 1;
			my_point.viz = "1";
			my_point.radius = 0;
			my_point.wpName =  wpName[i];

			my_points.push_back(my_point);	
			wpt_num += 1;
  			
			}
			else {
				
				if (rad[i] > 0.0) {
					rtt.x = latN[i];
					rtt.y = lonN[i];

					rp.x = latN[i - 1];
					rp.y = lonN[i - 1];

					rn.x = latN[i + 1];
					rn.y = lonN[i + 1];

					//wxString r = wxString::Format("%f", rad[i]);
					//wxMessageBox(r);

					GetPivotInfo(rtt, rp, rn, rad[i], pivotPoint, internal_angle, portstbd, ac1, ac2);
					CalculateCurvePoints(ac1, ac2, pivotPoint, rad[i], internal_angle, portstbd);
				}
				else {
					my_point.lat = wxString::Format(wxT("%f"), latN[i]);
					my_point.lon = wxString::Format(wxT("%f"), lonN[i]);
					my_point.routepoint = 1;
					my_point.viz = "1";
					my_point.radius = 0;
					my_point.wpName = wpName[i];

					my_points.push_back(my_point);
					wpt_num += 1;
				}

				
			}
	
		}
		// print the last routepoint
		my_point.lat = wxString::Format(wxT("%f"),latN[i]);
		my_point.lon = wxString::Format(wxT("%f"),lonN[i]);
		my_point.routepoint = 1;
		my_point.viz = "1";
		my_point.radius = 0;
		my_point.wpName = wpName[i];
		
		my_points.push_back(my_point);
		//


		for(std::vector<Position>::iterator itOut = my_points.begin();  itOut != my_points.end(); itOut++){
			//wxMessageBox((*it).lat, _T("*it.lat"));
		
        double value, value1;
		if(!(*itOut).lat.ToDouble(&value)){ /* error! */ }
			lati = value;
		if(!(*itOut).lon.ToDouble(&value1)){ /* error! */ }
			loni = value1;

		wxString s_radius;
		s_radius = wxString::Format("%f", (*itOut).radius);
		//wxMessageBox(s_radius);
		
		if ((*itOut).routepoint == 1){
			if (write_file){Addpoint(Route, wxString::Format(wxT("%f"),lati), wxString::Format(wxT("%f"),loni), (*itOut).wpName ,_T("diamond"),_T("WPT"), (*itOut).viz, s_radius ) ;}
		}
		else{
			if ((*itOut).routepoint == 0){
				if (write_file){Addpoint(Route, wxString::Format(wxT("%f"),lati), wxString::Format(wxT("%f"),loni), (*itOut).wpName,_T("square"),_T("WPT"), (*itOut).viz, s_radius);}
			}
		}
		
		}
		
		my_points.clear();		
        break;
		
		}

    
      default:
      {            // Note the colon, not a semicolon
        cout<<"Error, bad input, quitting\n";
        break;
      }
    }

       if (write_file){
            root->LinkEndChild( Route );
            // check if string ends with .gpx or .GPX
			if (!s.EndsWith(_T(".gpx"))) {
                 s = s + _T(".gpx");
            }
            wxCharBuffer buffer=s.ToUTF8();
            if (dbg) std::cout<< buffer.data()<<std::endl;
            doc.SaveFile( buffer.data() );}
    //} //end of if no error occured

    if (error_occured==true)  {
        wxLogMessage(_("Error in calculation. Please check input!") );
        wxMessageBox(_("Error in calculation. Please check input!") );
    }
  }
}


void Dlg::FillWaypointListbox()
{
	wxString wpName;
	std::vector<wxString> wpItems;
	for (std::vector<Position>::iterator it = my_positions.begin(); it != my_positions.end(); it++) {

		wpName = (*it).wpName;
		wpItems.push_back(wpName);
			
	}

	this->m_listBoxWaypoints->Set(wpItems);

}


void Dlg::GetWaypointData(wxCommandEvent& event) {

	this->m_getTurnRadius->SetValue("0.0");
	wxString thisWaypoint = this->m_listBoxWaypoints->GetStringSelection();	

	//wxMessageBox(thisWaypoint);
	wxString radius_string = "0.0";


	for (std::vector<Position>::iterator it = my_positions.begin(); it != my_positions.end(); it++) {
			
		if ((*it).wpName == thisWaypoint) {
			
			this->m_wptLat->SetValue((*it).lat);
			this->m_wptLon->SetValue((*it).lon);
			
			radius_string = wxString::Format("%f", (*it).radius);
			this->m_getTurnRadius->SetValue(radius_string);	

			event.Skip();
			break;
		}
	}
	
}

void Dlg::Update() {

	vector<Position> draftPositions;
	Position draftPos;

	draftPositions = my_positions;
	
	my_positions.clear();
	
	double d_radius = 0.0;

	wxString thisRadius = this->m_getTurnRadius->GetValue();
	thisRadius.ToDouble(&d_radius);

	wxString thisWaypoint = this->m_listBoxWaypoints->GetStringSelection();

	for (std::vector<Position>::iterator itOut = draftPositions.begin(); itOut != draftPositions.end(); itOut++) {


		//wxMessageBox((*it).lat, _T("*it.lat"));
		draftPos.lat = (*itOut).lat;
		draftPos.lon = (*itOut).lon;

		if ((*itOut).wpName == thisWaypoint) {
			draftPos.radius = d_radius;
		}
		else {
			draftPos.radius = (*itOut).radius;
		}

		draftPos.wpName = (*itOut).wpName;

		wxString sViz = (*itOut).viz;
		if (sViz == wxEmptyString) {
			draftPos.viz = "1";
		}
		else {
			draftPos.viz = (*itOut).viz;
		}

		draftPos.wpSym = (*itOut).wpSym;

		draftPos.planned_speed= (*itOut).planned_speed;

		draftPos.routepoint = (*itOut).routepoint;

		my_positions.push_back(draftPos);
	}
		

}

void Dlg::SaveGPX() {

	m_listBoxWaypoints->Clear();
	
	wxString defaultFileName = "RTZ";
	wxString s;

	wxFileDialog dlg(this, _("Export RTZroute Positions in GPX file as"), wxEmptyString, defaultFileName, _T("GPX files (*.gpx)|*.gpx|All files (*.*)|*.*"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (dlg.ShowModal() == wxID_CANCEL) {
		return;
	}
	//dlg.ShowModal();
	s = dlg.GetPath();
	if (dlg.GetPath() == wxEmptyString) {
		wxMessageBox("Empty Path");
		return;
	}

	TiXmlDocument doc;
	TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "utf-8", "");
	doc.LinkEndChild(decl);
	TiXmlElement * root = new TiXmlElement("gpx");
	TiXmlElement * Route = new TiXmlElement("rte");
	TiXmlElement * RouteName = new TiXmlElement("name");
	TiXmlText * text4 = new TiXmlText(this->m_Route->GetValue().ToUTF8());
	//TiXmlText * textSpeed = new TiXmlText(this->m_Speed_PS->GetValue().ToUTF8());


	doc.LinkEndChild(root);
	root->SetAttribute("version", "1.1");
	root->SetAttribute("creator", "RTZroute_pi by Rasbats");
	root->SetAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
	root->SetAttribute("xmlns", "http://www.topografix.com/GPX/1/1");
	root->SetAttribute("xmlns:gpxx", "http://www.garmin.com/xmlschemas/GpxExtensions/v3");
	root->SetAttribute("xsi:schemaLocation", "http://www.topografix.com/GPX/1/1 http://www.topografix.com/GPX/1/1/gpx.xsd");
	root->SetAttribute("xmlns:opencpn", "http://www.opencpn.org");
	Route->LinkEndChild(RouteName);
	RouteName->LinkEndChild(text4);


	TiXmlElement * Extensions = new TiXmlElement("extensions");

	TiXmlElement * StartN = new TiXmlElement("opencpn:start");
	TiXmlText * text5 = new TiXmlText("Start");
	Extensions->LinkEndChild(StartN);
	StartN->LinkEndChild(text5);

	TiXmlElement * EndN = new TiXmlElement("opencpn:end");
	TiXmlText * text6 = new TiXmlText("End");
	Extensions->LinkEndChild(EndN);
	EndN->LinkEndChild(text6);

	TiXmlElement * Speed = new TiXmlElement("opencpn:planned_speed");
	TiXmlText * text7 = new TiXmlText(mySpeed);
	Extensions->LinkEndChild(Speed);
	Speed->LinkEndChild(text7);

	Route->LinkEndChild(Extensions);

	double lati, loni;
	double latN[100], lonN[100];

	Position my_point;

	wxString s_radius;

	for (std::vector<Position>::iterator itOut = my_positions.begin(); itOut != my_positions.end(); itOut++) {
		//wxMessageBox((*itOut).lat, _T("*itOut.lat"));

		double value, value1;
		if (!(*itOut).lat.ToDouble(&value)) { /* error! */ }
		lati = value;
		if (!(*itOut).lon.ToDouble(&value1)) { /* error! */ }
		loni = value1;

		s_radius = wxString::Format("%f", (*itOut).radius);

		Addpoint(Route, wxString::Format(wxT("%f"), lati), wxString::Format(wxT("%f"), loni), (*itOut).wpName, (*itOut).wpSym, _T("WPT"), (*itOut).viz, s_radius);			

	}

	my_positions.clear();

	root->LinkEndChild(Route);
	// check if string ends with .gpx or .GPX
	if (!s.EndsWith(_T(".gpx"))) {
		s = s + _T(".gpx");
	}
	wxCharBuffer buffer = s.ToUTF8();
	doc.SaveFile(buffer.data());

}