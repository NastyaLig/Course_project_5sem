#pragma once
#include "STDAFX.H"
#include "CMATRIX.H"
#include "math.h"
#include "lib.h"
CMatrix Translate3D(double x,double y,double z);
CMatrix Rotate3Dx(double fi);
CMatrix Rotate3Dy(double fi);
CMatrix Rotate3Dz(double fi);
CMatrix VectorMult(CMatrix V1,CMatrix V2);
double ScalarMult(CMatrix V1,CMatrix V2);
double cosViV2(CMatrix V1,CMatrix V2);
CMatrix SphereToCart(CMatrix DView);
CMatrix CreateViewCoord(double theta,double fi,double R);