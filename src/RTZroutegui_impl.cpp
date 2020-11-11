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

class waypoint;
class route;

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) {wxMessageBox("Error"); return a_eResult; }
#endif

#define FAIL(X) do { error = X; goto failed; } while(0)

Dlg::Dlg(wxWindow *parent, RTZroute_pi *ppi)
	: m_Dialog(parent)
{
	this->Fit();
	dbg = false; //for debug output set to true
	
	pPlugIn = ppi;
	pParent = parent;

	//wxString blank_name = *GetpSharedDataLocation()
	//	+ _T("plugins/RTZroute_pi/data/blank.ico");

	//wxIcon icon(blank_name, wxBITMAP_TYPE_ICO);
	//SetIcon(icon);
	m_choiceSchema->SetSelection(0);
	
}

Dlg::~Dlg()
{
	
}

void Dlg::SetRadiusValue(wxScrollEvent& event) {

	turnRadius = this->m_sliderRadius->GetValue();
	turnRadius /= 1852;
	wxString string_radius = wxString::Format("%0.1f", turnRadius);
	//wxMessageBox("set");
	this->m_getTurnRadius->SetValue(string_radius);

}



void Dlg::Addpoint(TiXmlElement* Route, wxString ptlat, wxString ptlon, wxString ptname, wxString ptsym, wxString pttype, wxString ptviz, wxString ptradius){

	
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
    
	RoutePoint->LinkEndChild(Extensions2);
    Route->LinkEndChild( RoutePoint );

}


bool Dlg::ReadGPX()
{
	int response = wxID_CANCEL;
	int my_count = 0;

	wxArrayString file_array;

	wxString m_gpx_path;
	wxFileDialog openDialog(this, _("Import GPX Route file"), m_gpx_path, wxT(""),
		wxT("GPX files (*.gpx)|*.gpx|All files (*.*)|*.*"),
		wxFD_OPEN);
	response = openDialog.ShowModal();
	if (response == wxID_OK) {
		openDialog.GetPaths(file_array);

		//    Record the currently selected directory for later use
		if (file_array.GetCount()) {
			wxFileName fn(file_array[0]);
			filename = file_array[0];
			m_gpx_path = fn.GetPath();
			return true;
		}
	}
	else if (response = wxID_CANCEL) {
		return false;
	}

}

void Dlg::ReadRTZ(string schema, string rtz)
{
	int argc = 1;
	const char* args[] = { schema.c_str(), rtz.c_str() };
	int r = 0;
	r = mainParser(argc, args);

	wxString result = wxString::Format("%i", r);
	wxMessageBox(result);

	wxString line = "";

	wxFileName f(wxStandardPaths::Get().GetExecutablePath());
	wxString appPath(f.GetPath());


	wxString domText = appPath + "/data/" + "dom_out.txt";

	wxFileInputStream input(domText);
	wxTextInputStream text(input, wxT("\x09"), wxConvUTF8);
	while (input.IsOk() && !input.Eof())
	{
		line += text.ReadLine();
		line += "\n";
		// do something with the string
	}

	m_textCtrlShowResult->SetValue(line);
}


int Dlg::DomExportGPX() {

	// temporary place holders
	route myRoute;
	waypoint myWaypoint;
	vector<waypoint> myVectorWaypoints;
	// end of placeholders

	wxString isExtension = "";

	string readFile = "dom_out.txt"; // intermediate file - make temporary?
	vector<string> myVector;

	ifstream ips;
	ips.open(readFile);
	string line;
	while (getline(ips, line))
	{
		std::string::iterator end_pos = std::remove(line.begin(), line.end(), ' ');
		line.erase(end_pos, line.end());

		myVector.push_back(line);  // hold lines of file, without white space
	}

	int c = myVector.size();

	for (int z = 0; z < c; z++) {

		if (myVector[z] == "tag:extensions") {
			break;
		}

		wxStringTokenizer tokenizer(myVector[z], ":");
		while (tokenizer.HasMoreTokens())
		{
			wxString token = tokenizer.GetNextToken();
			// process token here

			if (token == "routeName") {
				myRoute.routeName = tokenizer.GetNextToken();
			}

			if (token == "tag") {
				isExtension = tokenizer.GetNextToken();
				if (isExtension == "extension") {
					break;	// this eliminates RTZ refpoints, which have lat/lon and could be misinterpreted as waypoints.
				}
			}

			if (token == "id") {
				myWaypoint.id = tokenizer.GetNextToken();
			}

			if (token == "name") {
				myWaypoint.name = tokenizer.GetNextToken();
			}

			if (token == "lat") {
				myWaypoint.lat = tokenizer.GetNextToken();
			}

			if (token == "lon") {

				myWaypoint.lon = tokenizer.GetNextToken();
				//
				myRoute.waypoints.push_back(myWaypoint);
				//
			}
		}
	}

	int waypointCount = myRoute.waypoints.size();

	tinyxml2::XMLDocument doc;  // main document for writing file

	tinyxml2::XMLDeclaration* decl = doc.NewDeclaration();
	decl->SetValue("xml version=""\"1.0\"");
	doc.LinkEndChild(decl);

	tinyxml2::XMLElement* root = doc.NewElement("gpx");

	root->SetAttribute("xmlns", "test");
	root->SetAttribute("version", "1.1");
	root->SetAttribute("creator", "RTZassist_RTZ");
	root->SetAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
	root->SetAttribute("xmlns", "http://www.topografix.com/GPX/1/1");

	root->SetAttribute("xmlns:gpxx", "http://www.garmin.com/xmlschemas/GpxExtensions/v3");
	root->SetAttribute("xsi:schemaLocation", "http://www.topografix.com/GPX/1/1/gpx.xsd");
	root->SetAttribute("xmlns:opencpn", "http://www.opencpn.org");

	doc.InsertEndChild(root);

	tinyxml2::XMLElement* Route = doc.NewElement("rte");
	root->LinkEndChild(Route);

	tinyxml2::XMLElement* RouteName = doc.NewElement("name");
	Route->LinkEndChild(RouteName);
	RouteName->SetText(myRoute.routeName.mb_str());

	tinyxml2::XMLElement* Extensions = doc.NewElement("extensions");

	tinyxml2::XMLElement* StartN = doc.NewElement("opencpn:start");
	Extensions->LinkEndChild(StartN);
	StartN->SetText("Start");

	tinyxml2::XMLElement* EndN = doc.NewElement("opencpn:end");
	Extensions->LinkEndChild(EndN);
	EndN->SetText("End");

	Route->InsertEndChild(Extensions);


	// ************* Add waypoints to Route *******


	for (int i = 0; i < waypointCount; i++) {

		tinyxml2::XMLElement*m_waypoint = doc.NewElement("rtept");

		Route->InsertEndChild(m_waypoint);
		m_waypoint->SetAttribute("lat", myRoute.waypoints[i].lat.mb_str());
		m_waypoint->SetAttribute("lon", myRoute.waypoints[i].lon.mb_str());

		tinyxml2::XMLElement* name = doc.NewElement("name");
		m_waypoint->InsertFirstChild(name);
		name->SetText(myRoute.waypoints[i].name.mb_str());

		tinyxml2::XMLElement* symbol = doc.NewElement("sym");
		m_waypoint->InsertFirstChild(symbol);
		symbol->SetText("diamond");

		tinyxml2::XMLElement* type = doc.NewElement("type");
		m_waypoint->InsertFirstChild(type);
		type->SetText("WPT");

	}

	// done adding waypoints
	// Write doc into a file
	wxFileDialog dlg(this, _("Save in GPX format"), wxEmptyString, wxEmptyString, _T("GPX files (*.gpx)|*.gpx|All files (*.*)|*.*"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (dlg.ShowModal() == wxID_CANCEL) {
		//error_occured = true;     // the user changed idea...
		return 999;
	}
	else {

		//dlg.ShowModal();
		wxString fileName = dlg.GetPath();
		if (dlg.GetPath() == wxEmptyString) {
			wxMessageBox("Error");
			return 999;
		}
		doc.SaveFile(fileName);
	}

	return 0;
	//end of if no error occured

}


int Dlg::ExportRTZ(wxString myFile, wxString myFileName) {

	if (this->m_listBoxWaypoints->IsEmpty()) {
		wxMessageBox("No waypoints available for export");
		return 0;
	}
	
	wxString rtzFileName = myFileName;
	wxString fileName = myFile;	

	// put the correct version in the RTZ file
	wxString versn;

	int selection = m_choiceSchema->GetSelection();

	if (selection == 0) {
		versn = "1.0";
	}
	else
		if (selection == 1) {
			versn = "1.1";
		}


	// Create Main level XML container
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLDeclaration* decl = xmlDoc.NewDeclaration();

	if (selection == 0) {
		decl->SetValue("xml version=""\"1.0\" " "encoding=""\"UTF-8\" " "standalone=""\"no\"");
	}
	else
		if (selection == 1) {
			decl->SetValue("xml version=""\"1.0\" " "encoding=""\"UTF-8\"");
		}

	xmlDoc.LinkEndChild(decl);

	// Create XML root node called animals
	tinyxml2::XMLElement* pRoot = xmlDoc.NewElement("route");

	const char* value;
	if (selection == 0) {
		value = "http://www.cirm.org/RTZ/1/0";
	}
	else if (selection == 1) {
		value = "http://www.cirm.org/RTZ/1/1";
	}

	char* sv = (const_cast<char*>((const char*)versn.mb_str()));

	pRoot->SetAttribute("xmlns", value);
	pRoot->SetAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");

	if (selection == 0) {
		pRoot->SetAttribute("xmlns:xsd", "http://www.w3.org/2001/XMLSchema");
	}

	pRoot->SetAttribute("version", sv);

	if (selection == 1) {
		pRoot->SetAttribute("xmlns:stm", "http://stmvalidation.eu/STM/1/0/0");
	}

	// Add pRoot to xmlDoc after prolog
	xmlDoc.InsertEndChild(pRoot);

	// ************* Add routeInfo to root node *******

	tinyxml2::XMLElement* routeInfo = xmlDoc.NewElement("routeInfo");
	pRoot->InsertFirstChild(routeInfo);

	// Route name must be the same as the file name, without file extension

	int fl = rtzFileName.length();
	wxString rtzFileBit = rtzFileName.SubString(0, (fl - 5));

	char* rtzFN = (const_cast<char*>((const char*)rtzFileBit.mb_str()));
	routeInfo->SetAttribute("routeName", rtzFN);

	// Insert cat's name as first child of animal


	// ************* Add waypoints *******
	waypoints = xmlDoc.NewElement("waypoints");
	pRoot->InsertEndChild(waypoints);

	int idn = 0;

	for (std::vector<Position>::iterator itOut = my_positions.begin(); itOut != my_positions.end(); itOut++) {


		tinyxml2::XMLElement*m_waypoint = xmlDoc.NewElement("waypoint");
		waypoints->InsertEndChild(m_waypoint);
		
		m_waypoint->SetAttribute("id", (*itOut).wpId.mb_str());
		m_waypoint->SetAttribute("name", (*itOut).wpName.mb_str());
		m_waypoint->SetAttribute("radius", (*itOut).radius);

		tinyxml2::XMLElement* position = xmlDoc.NewElement("position");

		position->SetAttribute("lat", (*itOut).lat.mb_str());
		position->SetAttribute("lon", (*itOut).lon.mb_str());
		m_waypoint->InsertEndChild(position);

		idn++;

	}
	// done adding waypoints
	// Write xmlDoc into a file

	xmlDoc.SaveFile(fileName);


	m_listBoxWaypoints->Clear();
	my_positions.clear();
	ClearTextboxes();

	return 0;

}

int Dlg::ExportRT4() {

	wxString rtzFileName;
	wxString fileName;
	wxFileDialog dlg(this, _("Save in RT4 format"), wxEmptyString, wxEmptyString, _T("RT4 files (*.rt4)|*.rt4|All files (*.*)|*.*"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (dlg.ShowModal() == wxID_CANCEL) {
		//error_occured = true;     // the user changed idea...
		return 999;
	}
	else {

		//dlg.ShowModal();
		fileName = dlg.GetPath();
		rtzFileName = dlg.GetFilename();
		//  std::cout<<s<< std::endl;
		if (dlg.GetPath() == wxEmptyString) {
			wxMessageBox("Error");
			return 999;
		}
	}

	// Create Main level XML container
	tinyxml2::XMLDocument xmlDoc;


	// Create XML root node
	tinyxml2::XMLElement* pRoot = xmlDoc.NewElement("nsroute");
	xmlDoc.InsertFirstChild(pRoot);

	// ************* Add routeInfo to root node *******

	tinyxml2::XMLElement* m_route_info = xmlDoc.NewElement("route_info");
	wxString rtname = "testName";
	m_route_info->SetAttribute("route_name", rtname.mb_str());
	m_route_info->SetAttribute("next_wpt_id", "999");
	
	double wpsz = m_waypointList.size();
	wxString swpsz = wxString::Format("%i", wpsz);
	m_route_info->SetAttribute("waypoints_count", swpsz.mb_str());
	m_route_info->SetAttribute("total_length", "");

	wxString s_now = wxNow();
	wxMessageBox(s_now);

	pRoot->LinkEndChild(m_route_info);
	

	// ************* Add waypoints *******
	waypoints = xmlDoc.NewElement("waypoints");
	

	tinyxml2::XMLElement*m_defaults = xmlDoc.NewElement("defaults");
	m_defaults->SetAttribute("pxtd", "0.027");
	m_defaults->SetAttribute("sxtd", "0.027");
	m_defaults->SetAttribute("trad", "0");
	m_defaults->SetAttribute("sfcontour", "0");
	m_defaults->SetAttribute("sfdepth", "0");
	m_defaults->SetAttribute("gcleg", "0");

	waypoints->InsertEndChild(m_defaults);

	pRoot->InsertEndChild(waypoints);

	int nm = m_waypointList.size();
	if (nm == 0) {
		wxMessageBox("No waypoints available", "Warning");
		return 999;
	}

	int idn = 1;

	for (std::vector<waypoint>::iterator itOut = m_waypointList.begin(); itOut != m_waypointList.end(); itOut++) {


		waypt = xmlDoc.NewElement("waypoint");

		tinyxml2::XMLElement*m_waypoint = xmlDoc.NewElement("waypoint");
		waypoints->InsertEndChild(m_waypoint);

		wxString myIdn = wxString::Format(wxT("%i"), idn);
		m_waypoint->SetAttribute("id", myIdn.mb_str());
		m_waypoint->SetAttribute("lat", (*itOut).lat.mb_str());
		m_waypoint->SetAttribute("lon", (*itOut).lon.mb_str());
		m_waypoint->SetAttribute("trad", (*itOut).radius.mb_str());

		
		idn++;
	}
	pRoot->LinkEndChild(waypoints);
	
	schedules = xmlDoc.NewElement("schedules");
	tinyxml2::XMLElement*schedule = xmlDoc.NewElement("schedule");
	schedule->SetAttribute("name", "");
	

	tinyxml2::XMLElement*m_manual = xmlDoc.NewElement("manual");

	idn = 1;

	for (std::vector<waypoint>::iterator itOut = m_waypointList.begin(); itOut != m_waypointList.end(); itOut++) {
		tinyxml2::XMLElement*m_waypoint_sched = xmlDoc.NewElement("waypoint");
		m_manual->InsertEndChild(m_waypoint_sched);

		wxString myId = wxString::Format(wxT("%i"), idn);
		m_waypoint_sched->SetAttribute("id", myId.mb_str());

		m_waypoint_sched->SetAttribute("speed", "15.0");

		idn++;

	}
	schedule->LinkEndChild(m_manual);
	schedules->LinkEndChild(schedule);

	pRoot->LinkEndChild(schedules);

	// done adding waypoints
	// Write xmlDoc into a file

	xmlDoc.SaveFile(fileName);

	//m_listBoxWaypoints->Clear();
	ClearTextboxes();

	return 0;
}



void Dlg::OnImport(wxCommandEvent& event)
{	wxFileDialog dlg(this, "Select file", wxEmptyString, wxEmptyString, "GPX (*.gpx) | *.gpx;*.GPX | RTZ files(*.rtz) | *.rtz;*.RTZ | Transas .rt3 (*.rt3) | *.rt3;*.rt3 | Transas .rt4 (*.rt4) | *.rt4;*.rt4 | Sperry Visonmaster (*.route) | *.route;*.ROUTE", wxFD_OPEN);
	if (dlg.ShowModal() == wxID_OK) {

		if (dlg.GetPath() != wxEmptyString) {

			wxString show = dlg.GetPath();
			//wxMessageBox(show);

			if (dlg.GetPath().Right(3) == "gpx" || dlg.GetPath().Right(3) == "GPX") {
				int r = ImportGPX(dlg.GetPath());
				if (r != 1) { wxMessageBox("Parse Error"); }
			}
			else {
				if (dlg.GetPath().Right(3) == "rtz" || dlg.GetPath().Right(3) == "RTZ") {
					int r = ImportRTZ(dlg.GetPath());
					if (r != 1) { wxMessageBox("Parse Error");}
				}
				else {
					if (dlg.GetPath().Right(3) == "rt3" || dlg.GetPath().Right(3) == "RT3") {
						//plugin->ImportRT3(dlg.GetPath());
						wxMessageBox("Not yet implemented");
					}
					else {
						if (dlg.GetPath().Right(3) == "rt4" || dlg.GetPath().Right(3) == "RT4") {
							//plugin->ImportRT4(dlg.GetPath());
							wxMessageBox("Not yet implemented");
						}
						else {
							if (dlg.GetPath().Right(5) == "route" || dlg.GetPath().Right(5) == "ROUTE") {
								//plugin->ImportRT4(dlg.GetPath());
								wxMessageBox("Not yet implemented");
							}
						}
					}
				}
			}

		}
		else wxMessageBox(_("No file entered"));

		event.Skip();
	}
}

void Dlg::OnExport(wxCommandEvent& event)
{
	wxFileDialog dlg(this, "Select file", wxEmptyString, wxEmptyString, "GPX (*.gpx) | *.gpx;*.GPX | RTZ files(*.rtz) | *.rtz;*RTZ | Transas .rt3 (*.rt3) | *.rt3;*RT3 | Transas .rt4 (*.rt4) | *.rt4;*RT4| Sperry Visonmaster (*.route) | *.route;*ROUTE", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (dlg.ShowModal() == wxID_OK) {

		if (dlg.GetPath() != wxEmptyString) {

			wxString show = dlg.GetPath();
			//wxMessageBox(show);

			if (dlg.GetPath().Right(3) == "gpx" || dlg.GetPath().Right(3) == "GPX") {
				ExportGPX(dlg.GetPath());
			}
			else {
				if (dlg.GetPath().Right(3) == "rtz" || dlg.GetPath().Right(3) == "RTZ") {
					ExportRTZ(dlg.GetPath(), dlg.GetFilename());
				}
				else {
					if (dlg.GetPath().Right(3) == "rt3" || dlg.GetPath().Right(3) == "RT3") {
						//plugin->ImportRT3(dlg.GetPath());
						wxMessageBox("Not yet implemented");
					}
					else {
						if (dlg.GetPath().Right(3) == "rt4" || dlg.GetPath().Right(3) == "RT4") {
							//plugin->ImportRT4(dlg.GetPath());
							wxMessageBox("Not yet implemented");
						}
						else {
							if (dlg.GetPath().Right(5) == "route" || dlg.GetPath().Right(5) == "ROUTE") {
								//plugin->ImportRT4(dlg.GetPath());
								wxMessageBox("Not yet implemented");
							}
						}
					}
				}
			}

		}
		else wxMessageBox(_("No file entered"));

		event.Skip();
	}
}


void Dlg::GetPivotInfo(wxRealPoint rtt, wxRealPoint rtp, wxRealPoint rtn, double radius, wxRealPoint &rtpivot, double &internalAngle,  wxString &portstbd, wxRealPoint &pb, wxRealPoint &pa) {
	
	double bfpc;   // bearing from previous point to the turn (centre)
	double bfnc;
	double bfcp;   // from centre to previous waypoint
	double bfcn; // from centre to next waypoint

	
	DistanceBearingMercator_Plugin(rtt.x, rtt.y,rtp.x, rtp.y,  &bfpc, &distanceToWaypoint);   // bearing from previous point to the turn (centre)
	DistanceBearingMercator_Plugin(rtt.x, rtt.y, rtn.x, rtn.y,  &bfnc, &distanceToWaypoint);
	DistanceBearingMercator_Plugin(rtp.x, rtp.y,rtt.x, rtt.y,  &bfcp, &distanceToWaypoint);   // from centre to previous waypoint
	DistanceBearingMercator_Plugin(rtn.x, rtn.y,rtt.x, rtt.y,  &bfcn, &distanceToWaypoint); // from centre to next waypoint

	double halfangle;
	
	double directionPivot = calcCentreOfPivotDirection(bfpc, bfcn, portstbd, halfangle);

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
	
}

void Dlg::CalculateCurvePoints(wxRealPoint ac1, wxRealPoint ac2, wxRealPoint pivotPoint, double radius, double internalAngle, wxString portstbd)
{
	
	Position my_point;

	my_point.lat = wxString::Format(wxT("%f"), ac1.x);
	my_point.lon = wxString::Format(wxT("%f"), ac1.y);
	my_point.routepoint = 1;
	my_point.viz = "1";
	my_point.radius = "0.0";
	my_point.wpName = wxString::Format(wxT("%d"), wpt_num);
	my_points.push_back(my_point);

	wpt_num += 1;

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
	
	my_point.lat = wxString::Format(wxT("%f"), rpoint1.y);
	my_point.lon = wxString::Format(wxT("%f"), rpoint1.x);
	my_point.routepoint = 1;
	my_point.viz = "0";
	my_point.radius = "0.0";
	my_point.wpName = wxString::Format(wxT("%d"), wpt_num);
	my_points.push_back(my_point);

	wpt_num += 1;

	wxRealPoint p;
	p = wpoint;

	double totalAngle = angle;
	double Xnew;
	double Ynew;

	while (totalAngle < changeBearing) {
		double s = sin(angle);
		double c = cos(angle);

		// translate point back to origin:

		p.x -= xylonlatC.x;
		p.y -= xylonlatC.y;

		// rotate point
		if (portstbd == "P") {
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

		my_point.lat = wxString::Format(wxT("%f"), rllpoint.y);
		my_point.lon = wxString::Format(wxT("%f"), rllpoint.x);
		my_point.routepoint = 1;
		my_point.viz = "0";
		my_point.radius = "0.0";
		my_point.wpName = wxString::Format(wxT("%d"), wpt_num);
		my_points.push_back(my_point);

		wpt_num += 1;
		totalAngle = totalAngle + angle;
	}

	my_point.lat = wxString::Format(wxT("%f"), ac2.x);
	my_point.lon = wxString::Format(wxT("%f"), ac2.y);	
	my_point.routepoint = 1;
	my_point.viz = "1";
	my_point.radius = "0.0";
	my_point.wpName = wxString::Format(wxT("%d"), wpt_num);
	my_points.push_back(my_point);

}

void Dlg::OnGenerateRadiusGPX( wxCommandEvent& event )
{	
	Calculate(event, true, 1);
}

void Dlg::OnEditGPX(wxCommandEvent& event)
{
	OpenXML();	
}

void Dlg::OnUpdateTurn(wxCommandEvent& event)
{
	
	Update();
	
}

void Dlg::OnSaveGPX(wxCommandEvent& event)
{
	SaveGPX();
}

void Dlg::OnValidate(wxCommandEvent& event)
{
	wxFileDialog dlg(this, "Select RTZ file for validation", wxEmptyString, wxEmptyString, "RTZ 1.0 files(*.rtz) | *.rtz;*RTZ", wxFD_OPEN);
	if (dlg.ShowModal() == wxID_OK) {

		if (dlg.GetPath() != wxEmptyString) {

			//wxString show = dlg.GetPath();
			//wxMessageBox(show);

			if (dlg.GetPath().Right(3) == "rtz" || dlg.GetPath().Right(3) == "RTZ") {
			
				wxString schemaSelection = m_choiceSchema->GetStringSelection();
				if (schemaSelection == wxEmptyString) {
					wxMessageBox("Please select a schema");
					return;
				}

				//wxMessageBox(schemaSelection);

				string xschema, xpath;
				xschema = schemaSelection.mb_str();
				xpath = dlg.GetPath().mb_str();

				ValidateRTZ(xschema, xpath);
			}
		}
	}
	//wxMessageBox("Not yet implemented");
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
						my_position.radius = "0.0";  // dummy value to make sure there is an entry
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
								
										my_position.radius = radius_string;
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

bool Dlg::ImportGPX(wxString myFile)
{
	Position my_position;
	int n = 1;

	my_positions.clear();

	int response = wxID_CANCEL;
	int my_count = 0;

	
	wxString filename;
	
	wxFileName fn(myFile);
	filename = myFile;
	m_gpx_path = fn.GetPath();

	TiXmlDocument doc;
	wxString error;
	wxProgressDialog *progressdialog = NULL;


	if (!doc.LoadFile(filename.mb_str())) {
		FAIL(_("Failed to load file: ") + filename);
	}
	else {
		TiXmlElement *root = doc.RootElement();
		if (!strcmp(root->Value(), "rte"))
			FAIL(_("rte Invalid xml file"));

		int count = 0;
		for (TiXmlElement* e = root->FirstChildElement(); e; e = e->NextSiblingElement())
			count++;

		int i = 0;
		wxString planned_speed = "5.0";

		for (TiXmlElement* e = root->FirstChildElement(); e; e = e->NextSiblingElement(), i++) {
			if (progressdialog) {
				if (!progressdialog->Update(i))
					return true;
			}
			else {
				if (1) {
					progressdialog = new wxProgressDialog(
						_("Route"), _("Loading"), count, this,
						wxPD_CAN_ABORT | wxPD_ELAPSED_TIME | wxPD_REMAINING_TIME);
				}
			}

			for (TiXmlElement* f = e->FirstChildElement(); f; f = f->NextSiblingElement()) {

				if (!strcmp(f->Value(), "extensions")) {

					for (TiXmlElement* g = f->FirstChildElement(); g; g = g->NextSiblingElement()) {
						if (!strcmp(g->Value(), "opencpn:planned_speed")) {
							planned_speed = wxString::FromUTF8(g->GetText());
							mySpeed = planned_speed;
							//wxMessageBox(planned_speed);
						}
					}
				}

				
				
				if (!strcmp(f->Value(), "rtept")) {

					double value = 999;

					wxString wpViz = "1";
					

					my_position.viz = wpViz;   // dummy value to make sure there is an entry
					my_position.radius = "0.0";  // dummy value to make sure there is an entry
					my_position.planned_speed = planned_speed;  // dummy value to make sure there is an entry
					my_position.wpSym = "diamond";

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
									my_position.radius = radius_string;
								}

								if (!strcmp(h->Value(), "opencpn:viz")) {
									wpViz = wxString::FromUTF8(h->GetText());
									my_position.viz = wpViz;
								}
							}
						}
					}

					my_position.wpId = wxString::Format("%i", n);
					n++;
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

int Dlg::ImportRTZ(wxString myFile) {

	using namespace tinyxml2;
	rtz_version = "";
	Position my_position;
	my_positions.clear();

	wxString filename = myFile;

	tinyxml2::XMLDocument xmlDoc;
	xmlDoc.LoadFile(filename);
	
	XMLNode * pRoot = xmlDoc.FirstChild();
	if (pRoot == nullptr) return XML_ERROR_FILE_READ_ERROR;

	TiXmlDocument doc;
	wxString error;
	wxProgressDialog *progressdialog = NULL;

	my_position.viz = "1";   // dummy value to make sure there is an entry
	my_position.radius = "0.0";  // dummy value to make sure there is an entry
	my_position.planned_speed = "5";  // dummy value to make sure there is an entry
	my_position.routeName = "na";
	my_position.wpSym = "diamond";
	
	XMLElement* pRootElement = xmlDoc.RootElement();
	
	string nm = pRootElement->Attribute("version");
	rtz_version = nm;

	XMLElement* pRouteNameElement = xmlDoc.FirstChildElement("route")->FirstChildElement("routeInfo");

	if (pRouteNameElement == nullptr) return XML_ERROR_PARSING_ELEMENT;

	string s = pRouteNameElement->Attribute("routeName");
	my_position.routeName = s;
	bool exists = false;
	//wxMessageBox(s);


	XMLElement* pWaypointsElement = xmlDoc.FirstChildElement("route")->FirstChildElement("waypoints");
	if (pWaypointsElement == nullptr) return XML_ERROR_PARSING_ELEMENT;

	XMLElement * pListWaypointsElement = pWaypointsElement->FirstChildElement("waypoint");
	if (pListWaypointsElement == nullptr) return XML_ERROR_PARSING_ELEMENT;

	while (pListWaypointsElement != nullptr)
	{

		string sti = pListWaypointsElement->Attribute("id");
		my_position.wpId = sti;
		//wxMessageBox(sti);

		string stn = pListWaypointsElement->Attribute("name");
		my_position.wpName = stn;
		//wxMessageBox(stn);

		
		const char* value = pListWaypointsElement->Attribute("radius"); 
		wxString exists = value;

		if (exists == wxEmptyString){
			my_position.radius = "0.0";
			//wxMessageBox("not exists");
		}
		else {
			string str = pListWaypointsElement->Attribute("radius");
			my_position.radius = str;
			//wxMessageBox("exists");
		}

		XMLElement * pListPositionElement = pListWaypointsElement->FirstChildElement("position");
		if (pListPositionElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
		while (pListPositionElement != nullptr)
		{
			string stp = pListPositionElement->Attribute("lat");
			my_position.lat = stp;
			//wxMessageBox(stp);

			string stpl = pListPositionElement->Attribute("lon");
			my_position.lon = stpl;
			//wxMessageBox(stpl);

			pListPositionElement = pListPositionElement->NextSiblingElement("position");// stop the loop when position empty
		}
		
		pListWaypointsElement = pListWaypointsElement->NextSiblingElement("waypoint"); // stop the loop when waypoints empty

		
		my_positions.push_back(my_position);
	}

	FillWaypointListbox();
	SetRTZversion(rtz_version);
	
	return 1;
		
}



void Dlg::Calculate( wxCommandEvent& event, bool write_file, int Pattern  ){			

	if (my_positions.size() == 0) {
		wxMessageBox("No waypoints available for export");
		return;
	}

	int theStep = this->m_TurnStep->GetSelection();
	wxString step_string = this->m_TurnStep->GetString(theStep);
	double value;
	if (!step_string.ToDouble(&value)) { wxLogMessage("RTZroute: error obtaining turn step"); }
	turnStep = value;



	bool error_occured = false;
	double lat1, lon1;
	wxString defaultFileName;
	defaultFileName = this->m_Route->GetValue();

	lat1 = 0.0;
	lon1 = 0.0;

	wxString s = "";
	


	if (write_file) {
		wxFileDialog dlg(this, _("Export RTZroute Positions in GPX file as"), wxEmptyString, defaultFileName, _T("GPX files (*.gpx)|*.gpx|All files (*.*)|*.*"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		if (dlg.ShowModal() == wxID_CANCEL) {
			error_occured = true;     // the user changed idea...
			return;
		}

		//dlg.ShowModal();
		s = dlg.GetPath();
		if (dlg.GetPath() == wxEmptyString) { error_occured = true; if (dbg) printf("Empty Path\n"); }
	}

	//Validate input ranges
	if (!error_occured) {
		if (std::abs(lat1) > 90) { error_occured = true; }
		if (std::abs(lon1) > 180) { error_occured = true; }
		if (error_occured) wxMessageBox(_("error in input range validation"));
	}

	//Start GPX
	TiXmlDocument doc;
	TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "utf-8", "");
	doc.LinkEndChild(decl);
	TiXmlElement * root = new TiXmlElement("gpx");
	TiXmlElement * Route = new TiXmlElement("rte");
	TiXmlElement * RouteName = new TiXmlElement("name");
	TiXmlText * text4 = new TiXmlText(this->m_Route->GetValue().ToUTF8());




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

		interval += 1;

		speed = speed*(double)interval;

        int n=0;

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

			wxString rads = (*it).radius;
			rads.ToDouble(&value);			
			rad[n] = value;

			wpName[n] = (*it).wpName;

			n++;//0,1,2,3
		}
		
		//my_positions.clear();
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
			my_point.radius = "0";
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
					my_point.radius = "0";
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
		my_point.radius = "0.0";
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
		s_radius = (*itOut).radius;		

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

			wxLogMessage("RTZroute: " + s);
            wxCharBuffer buffer = s.ToUTF8();
            if (dbg) std::cout<< buffer.data()<<std::endl;
            doc.SaveFile( buffer.data() );}
    //} //end of if no error occured

	   this->m_listBoxWaypoints->Clear(); // prevent user making a second export of the same waypoints ????? 
	   my_positions.clear();
	   ClearTextboxes();

    if (error_occured==true)  {
        wxLogMessage(_("Error in calculation. Please check input!") );
        wxMessageBox(_("Error in calculation. Please check input!") );
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

		wxString thisWaypoint;

		int sl = this->m_listBoxWaypoints->GetSelection();
		if (sl == wxNOT_FOUND) {
		}
		else {
			thisWaypoint = this->m_listBoxWaypoints->GetStringSelection();
		}

		wxString radius_string = "0.0";

		for (std::vector<Position>::iterator it = my_positions.begin(); it != my_positions.end(); it++) {

			if (sl == wxNOT_FOUND) {
				this->m_wptLat->SetValue((*it).lat);
				this->m_wptLon->SetValue((*it).lon);

				this->m_getTurnRadius->SetValue((*it).radius);
			}
			else {

				if ((*it).wpName == thisWaypoint) {

					this->m_wptLat->SetValue((*it).lat);
					this->m_wptLon->SetValue((*it).lon);

					this->m_getTurnRadius->SetValue((*it).radius);

					event.Skip();
					break;
				}
			}

		}
	
}

void Dlg::Update() {

	
		if (my_positions.size() == 0) {			
			return;
		}


		Position draftPos;
		draftPositions.clear();

		wxString s_name = "";
		wxString thisRadius = "0.0";

		int sl = this->m_listBoxWaypoints->GetSelection();
		if (sl == wxNOT_FOUND) {
			return;
		}
		else {
			s_name = this->m_listBoxWaypoints->GetStringSelection();
		}
				
		draftPositions = my_positions;
		my_positions.clear();

		for (std::vector<Position>::iterator itOut = draftPositions.begin(); itOut != draftPositions.end(); itOut++) {

			//wxMessageBox((*it).lat, _T("*it.lat"));
			draftPos.lat = (*itOut).lat;
			draftPos.lon = (*itOut).lon;

			draftPos.radius = (*itOut).radius;

			if (s_name == (*itOut).wpName) {
				thisRadius = this->m_getTurnRadius->GetValue();
				draftPos.radius = thisRadius;				
			}
			

			draftPos.wpName = (*itOut).wpName;
			draftPos.wpId = (*itOut).wpId;

			wxString sViz = (*itOut).viz;
			if (sViz == wxEmptyString) {
				draftPos.viz = "1";
			}
			else {
				draftPos.viz = (*itOut).viz;
			}

			draftPos.wpSym = (*itOut).wpSym;

			draftPos.planned_speed = (*itOut).planned_speed;

			draftPos.routepoint = (*itOut).routepoint;

			my_positions.push_back(draftPos);
		}

}

void Dlg::SaveGPX() {

	if (this->m_listBoxWaypoints->IsEmpty()) {		
		wxMessageBox("No updates have been made");
		return;
	}

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
	wxString s_viz;

	for (std::vector<Position>::iterator itOut = my_positions.begin(); itOut != my_positions.end(); itOut++) {
		//wxMessageBox((*itOut).lat, _T("*itOut.lat"));

		double value, value1;
		if (!(*itOut).lat.ToDouble(&value)) { /* error! */ }
		lati = value;
		if (!(*itOut).lon.ToDouble(&value1)) { /* error! */ }
		loni = value1;

		s_radius =  (*itOut).radius;
		s_viz = (*itOut).viz;

		Addpoint(Route, wxString::Format(wxT("%f"), lati), wxString::Format(wxT("%f"), loni), (*itOut).wpName, (*itOut).wpSym, _T("WPT"),s_viz, s_radius);			

	}

	//my_positions.clear();

	root->LinkEndChild(Route);
	// check if string ends with .gpx or .GPX
	if (!s.EndsWith(_T(".gpx"))) {
		s = s + _T(".gpx");
	}
	wxCharBuffer buffer = s.ToUTF8();
	doc.SaveFile(buffer.data());	

}


void Dlg::ExportGPX(wxString myFile) {

	
	if (my_positions.size() == 0) {		
		wxMessageBox("No waypoints available for export");
		return;
	}	

	//wxMessageBox("here");
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
	wxString s_viz;

	for (std::vector<Position>::iterator itOut = my_positions.begin(); itOut != my_positions.end(); itOut++) {
		//wxMessageBox((*itOut).lat, _T("*itOut.lat"));

		double value, value1;
		if (!(*itOut).lat.ToDouble(&value)) { /* error! */ }
		lati = value;
		if (!(*itOut).lon.ToDouble(&value1)) { /* error! */ }
		loni = value1;

		s_radius =  (*itOut).radius;
		s_viz = (*itOut).viz;

		//wxMessageBox(s_viz);

		Addpoint(Route, wxString::Format(wxT("%f"), lati), wxString::Format(wxT("%f"), loni), (*itOut).wpName, (*itOut).wpSym, _T("WPT"), s_viz, s_radius);

	}

	//

	root->LinkEndChild(Route);	

	// check if string ends with .gpx or .GPX
	if (!myFile.EndsWith(_T(".gpx"))) {
		myFile = myFile + _T(".gpx");
	}
	wxCharBuffer buffer = myFile.ToUTF8();
	doc.SaveFile(buffer.data());
	//
    my_positions.clear();
	m_listBoxWaypoints->Clear();	
	ClearTextboxes();

}

void Dlg::ValidateRTZ(string schema, string rtz) {
	
	wxString mySchema(schema);
	mySchema += ".xsd";
	
	wxString schemaPlus = *GetpSharedDataLocation() +
		_T("plugins") + wxFileName::GetPathSeparator() +
		_T("RTZroute_pi") + wxFileName::GetPathSeparator()
		+ _T("data") + wxFileName::GetPathSeparator() 
		+ _T("schema") + wxFileName::GetPathSeparator() + mySchema;

	string s_schema = schemaPlus.mb_str();
	
	int argc = 2;
	const char* args[] = { s_schema.c_str(), rtz.c_str() };
	int error = 0;
	int r = 0;

	wxString startURI = "file:///";

	r = mainValidator(argc, args);

	wxString line = "";

	//wxString r_string = wxString::Format("%i", r);

	if (r != 0) {
		//wxMessageBox("Validation Errors", "myMessage");

		m_textCtrlShowResult->Clear();

		wxString line = "VALIDATION ERRORS FOUND";		
		m_textCtrlShowResult->SetValue(line);
	}
	else {

		line = "No Validation Errors";
		m_textCtrlShowResult->SetValue(line);
	}
}

void Dlg::ClearTextboxes() {

	m_wptLat->SetValue("");
	m_wptLon->SetValue("");
	m_getTurnRadius->SetValue("");

}

void Dlg::SetRTZversion(wxString version) {
	if (version == "1.0") {
		m_choiceSchema->SetSelection(0);
	}
	else if (version == "1.1") {
		m_choiceSchema->SetSelection(1);
	}
	else
		wxMessageBox("Error finding the schema", "Schema Settings");
}