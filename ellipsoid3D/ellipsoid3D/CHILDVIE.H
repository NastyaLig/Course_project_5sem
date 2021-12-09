// ChildView.h : interface of the CChildView class
//


#pragma once
#include "cmatrix.h"
#include "lib.h"
#include "MyGDI.h"
#include "CEllipsoid.h"

// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:
	
		CMatrix PView,PLight;
	int step,m;
	CEllipsoid* pp;
	COLORREF col;
	
	
// Operations
public:
	bool m_IsMousePressed;
	CRect *m_SelectedRect;
	bool m_IsSelectedRect;
	CPen pen;
	CPoint p1;
	CString m_saved_file;
	afx_msg void OnSave1();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT var, CPoint point);
	afx_msg void OnLButtonUp(UINT var, CPoint point);
	afx_msg void OnMouseMove(UINT var, CPoint point);
	CRect rw;
// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	afx_msg void OnKeyDown(UINT nChar,UINT nRepCount,UINT nFlags);


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSetcolor();
	afx_msg void OnSetsize();


};
int ClientToBmp (HWND hWnd, const char* filepath, CRect r);	
