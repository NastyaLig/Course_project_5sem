
#pragma once
#include "stdafx.h"
#include "MyGDI.h"
//пересчет координат из видовой системы координат в оконную (ВСК->ОСК)
CMatrix SpaceToWindow(CRectD& rs, CRect& rw){
	CMatrix m(3,3);
	double kx=(rw.right-rw.left)/(rs.right-rs.left);
	double ky=(rw.bottom-rw.top)/(rs.top-rs.bottom);
	m(2,2)=1;
	m(0,0)=kx;
	m(1,1)=-ky;
	m(0,2)=rw.left-kx*rs.left;
	m(1,2)=rw.top-ky*rs.bottom;
	return m;
}
