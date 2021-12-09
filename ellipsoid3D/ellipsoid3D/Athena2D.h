#pragma once
#include "STDAFX.H"
#include "CMATRIX.H"
#include "math.h"
#include "lib.h"
CMatrix Translate2D(double x,double y);
CMatrix Rotate2D(double fi);
void SortPointsByX(CPoint* p,int len);
