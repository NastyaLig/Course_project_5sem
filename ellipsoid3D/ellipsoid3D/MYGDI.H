#pragma once
#include "stdafx.h"
#include "math.h"
#include "cmatrix.h"
#include "lib.h"
#include "Athena2D.h"
#include "Athena3D.h"
//пересчет координат из видовой системы координат в оконную (ВСК->ОСК)
CMatrix SpaceToWindow(CRectD& rs, CRect& rw);
