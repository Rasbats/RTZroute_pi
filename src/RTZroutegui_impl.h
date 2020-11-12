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

#ifndef _CALCULATORGUI_IMPL_H_
#define _CALCULATORGUI_IMPL_H_

#ifdef WX_PRECOMP
#include "wx/wx.h"
#endif


#include "RTZroutegui.h"
#include "RTZroute_pi.h"

#include "NavFunc.h"
#include "tinyxml.h"
#include "tinyxml2.h"

#include <list>
#include <vector>
#include <wx/slider.h>
#include <wx/listbox.h>
#include <string.h>
#include <wx/arrstr.h>
#include <wx/textfile.h>
#include <wx/stdpaths.h>
#include <iostream>
#include <fstream>
#include <wx/tokenzr.h>
#include <wx/utils.h> 
#include "load-grammar-sax.h"
#include "load-grammar-dom.h"
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include "tinyxml2.h"


using namespace std;


template <typename T> class Vector2D
{
private:
	T x;
	T y;

public:
	explicit Vector2D(const T& x = 0, const T& y = 0) : x(x), y(y) {}
	Vector2D(const Vector2D<T>& src) : x(src.x), y(src.y) {}
	virtual ~Vector2D() {}

	// Accessors
	inline T X() const { return x; }
	inline T Y() const { return y; }
	inline T X(const T& x) { this->x = x; }
	inline T Y(const T& y) { this->y = y; }

	// Vector arithmetic
	inline Vector2D<T> operator-() const
	{
		return Vector2D<T>(-x, -y);
	}

	inline Vector2D<T> operator+() const
	{
		return Vector2D<T>(+x, +y);
	}

	inline Vector2D<T> operator+(const Vector2D<T>& v) const
	{
		return Vector2D<T>(x + v.x, y + v.y);
	}

	inline Vector2D<T> operator-(const Vector2D<T>& v) const
	{
		return Vector2D<T>(x - v.x, y - v.y);
	}

	inline Vector2D<T> operator*(const T& s) const
	{
		return Vector2D<T>(x*s, y*s);
	}

	// Dot product
	inline T operator*(const Vector2D<T>& v) const
	{
		return x * v.x + y * v.y;
	}

	// l-2 norm
	inline T norm() const { return sqrt(x*x + y * y); }

	// inner angle (radians)
	static T angle(const Vector2D<T>& v1, const Vector2D<T>& v2)
	{
		return acos((v1 * v2) / (v1.norm() * v2.norm()));
	}
};

static const wxChar *FILETYPESEXPORT = _T(
	"RTZ 1.0 files(*.rtz) | *.rtz |"
	"RTZ 1.1 files(*.rtz) | *.rtz |"
	" Transas .rt3 (*.rt3) | *.rt3 |"
	" Transas .rt4 (*.rt4) | *.rt4 |"
	" Sperry Visonmaster (*.route) | *.route"
	"All files|*.*"
);
static const wxChar *FILETYPESIMPORT = _T(
	"RTZ 1.0 files(*.rtz) | *.rtz |"
	"RTZ 1.1 files(*.rtz) | *.rtz |"
	" Transas .rt3 (*.rt3) | *.rt3 |"
	" Transas .rt4 (*.rt4) | *.rt4 |"
	" Sperry Visonmaster (*.route) | *.route"
	"All files|*.*"
);




class RTZroute_pi;
class Position;

class waypoint
{
public:
	wxString id;
	wxString name;
	wxString radius;

	wxString lat, lon;

};

class route
{
public:

	wxString routeName;
	std::vector<waypoint> waypoints;
	wxArrayString m_arrayPoints;
};

class Dlg : public m_Dialog
{
public:
	Dlg(wxWindow *parent, RTZroute_pi *ppi);
	~Dlg();
        
	wxWindow *pParent;
	RTZroute_pi *pPlugIn;

	void SetRadiusValue(wxScrollEvent& event);
	
	void OnEditGPX(wxCommandEvent& event);
	void OnImport(wxCommandEvent& event);
	void OnExport(wxCommandEvent& event);
	bool ImportGPX(wxString myFile);
	int ImportRTZ(wxString myFile);
	void ExportGPX(wxString myFile);
	int ExportRTZ(wxString myFile, wxString myFileName);

	void OnValidate(wxCommandEvent& event);
	void ValidateRTZ(string schema, string rtz);

	void GetPivotInfo(wxRealPoint rtt, wxRealPoint rtp, wxRealPoint rtn, double radius, wxRealPoint &rtpivot, double &internalAngle,  wxString &portstbd, wxRealPoint &pb, wxRealPoint &pa);
	void CalculateCurvePoints(wxRealPoint ac1, wxRealPoint ac2, wxRealPoint pivotPoint, double radius, double internalAngle, wxString portstbd);
	void OnGenerateRadiusGPX(wxCommandEvent& event);

	void OnUpdateTurn(wxCommandEvent& event);

	void OnSaveGPX(wxCommandEvent& event);
	bool OpenXML();
	void Update();
	void SaveGPX();
	// From RTZassist
	bool ReadGPX();
	void ReadRTZ(string schema, string rtz);
	int DomExportGPX();
	int ExportRT4();

	vector<Position> my_positions;
	vector<Position> my_points;
	vector<Position> draftPositions;

	void Calculate(wxCommandEvent& event);
	void Addpoint(TiXmlElement* Route, wxString ptlat, wxString ptlon, wxString ptname, wxString ptsym, wxString pttype, wxString ptviz, wxString ptradius);

	void FillWaypointListbox();
	void ClearTextboxes();
	void SetRTZversion(wxString version);
	void GetWaypointData(wxCommandEvent& event);

	wxString rte_start;
	wxString rte_end;

	double testX[16], testY[16];
	int wpt_num;
	wxString filename;

	bool XML_SUCCESS;
	wxString ERROR_MESSAGE;
	wxString rtz_version;

private:

	void OnClose(wxCloseEvent& event);
	double lat1, lon1, lat2, lon2;
	bool error_found;
	bool dbg;

	wxString     m_gpx_path;
	//double radius;
	wxRealPoint ac1, ac2, pivotPoint;
	wxString portstbd;
	double internal_angle;
	double distanceToWaypoint;
	int turnStep;
	wxString mySpeed;
	double turnRadius;


	wxArrayString waypointsList;

	tinyxml2::XMLNode* route_info;
	tinyxml2::XMLNode* waypoints;
	tinyxml2::XMLNode* waypt;
	tinyxml2::XMLNode* schedules;
	tinyxml2::XMLNode* schedule;

	route myRoute;
	vector<waypoint> m_waypointList;
};


class Position
{
public:

    wxString lat, lon, wpt_num, viz;
    Position *prev, *next; /* doubly linked circular list of positions */
    int routepoint;
	wxString routeName;
	wxString radius;
	wxString wpId;
	wxString wpName;
	wxString wpSym;
	wxString planned_speed;

	
};

#endif
