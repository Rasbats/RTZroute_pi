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

#include <list>
#include <vector>
#include <wx/slider.h>
#include <wx/listbox.h>

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


class RTZroute_pi;
class Position;

class Dlg : public m_Dialog
{
public:
	Dlg(wxWindow *parent, RTZroute_pi *ppi);
	~Dlg();
        
	wxWindow *pParent;
	RTZroute_pi *pPlugIn;

	void SetRadiusValue(wxScrollEvent& event);
	
	void OnTestFunction(wxCommandEvent& event);
	void GetPivotInfo(wxRealPoint rtt, wxRealPoint rtp, wxRealPoint rtn, double radius, wxRealPoint &rtpivot, double &internalAngle,  wxString &portstbd, wxRealPoint &pb, wxRealPoint &pa);
	void CalculateCurvePoints(wxRealPoint ac1, wxRealPoint ac2, wxRealPoint pivotPoint, double radius, double internalAngle, wxString portstbd);


	    void OnPSGPX( wxCommandEvent& event );	
		void OnEditGPX(wxCommandEvent& event);
		void OnUpdate(wxCommandEvent& event);
		void OnSaveGPX(wxCommandEvent& event);
		bool OpenXML();
		void Update();
		void SaveGPX();
		
		vector<Position> my_positions;
		vector<Position> my_points;

        void Calculate( wxCommandEvent& event, bool Export, int Pattern );
        void Addpoint(TiXmlElement* Route, wxString ptlat, wxString ptlon, wxString ptname, wxString ptsym, wxString pttype, wxString ptviz, wxString ptradius);

		void FillWaypointListbox();
		void GetWaypointData(wxCommandEvent& event);

		wxString rte_start;
	    wxString rte_end;

		double testX[16], testY[16];
		int wpt_num;		
		bool testing;
		

private:
	    void OnClose( wxCloseEvent& event );
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
};


class Position
{
public:

    wxString lat, lon, wpt_num, viz;
    Position *prev, *next; /* doubly linked circular list of positions */
    int routepoint;
	double radius;
	wxString wpName;
	wxString wpSym;
	wxString planned_speed;
	
};

#endif
