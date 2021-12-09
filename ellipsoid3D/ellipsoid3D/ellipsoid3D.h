// ellipsoid3D.h : main header file for the ellipsoid3D application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Cellipsoid3DApp:
// See ellipsoid3D.cpp for the implementation of this class
//

class Cellipsoid3DApp : public CWinApp
{
public:
	Cellipsoid3DApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Cellipsoid3DApp theApp;
