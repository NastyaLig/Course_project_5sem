#pragma once
#include "CMATRIX.H"
#include "Athena3D.h"
#include "Athena2D.h"
#include "MyGDI.h"
#include "LIB.H"
class CEllipsoid
{
public:
	const static int NoV=450;
	CRectD rs;
	CMatrix Verticles;
	void DrawEnlighted(CDC& dc,CMatrix& PView,CMatrix& PLight,CRect& RW,COLORREF col,int m);
	CEllipsoid(void);
	CEllipsoid(int a,int b,int c);
	~CEllipsoid(void);
};

