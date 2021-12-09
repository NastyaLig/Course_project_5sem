// ChildView.cpp : implementation of the CChildView class


#include "stdafx.h"
#include "ellipsoid3D.h"
#include "ChildVie.h"
#include "SizeDialog.h"
#include <atlwin.h>
using namespace ATL;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	step=10;
	m=0;
	PView.RedimMatrix(3);
	//начальное положение наблюдателя
	PView(0)=450;PView(1)=0;PView(2)=0;
	PLight.RedimMatrix(3);
	//начальное положение источника света
	PLight(0)=450;PLight(1)=0;PLight(2)=0;
	pp=new CEllipsoid();
	//флаги нажатия мыши и выделения рамкой
	m_IsMousePressed = 0;
	m_IsSelectedRect = 0;
	m_SelectedRect = new CRect();
	//перо для прорисовки рамки выделения
	pen.CreatePen(PS_DOT,1,RGB(255,0,0));
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_COMMANDS_SETCOLOR, &CChildView::OnSetcolor)
	ON_COMMAND(ID_COMMANDS_SETSIZE, &CChildView::OnSetsize)
	ON_COMMAND(ID_FILE_SAVE_AS, &CChildView::OnSave1)
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); 
	//прорисовка эллипсоида
	pp->DrawEnlighted(dc,PView,PLight,CRect(200,200,500,500),col,m);
	//прорисовки рамки выделения
	if(m_IsSelectedRect )

	{
		dc.SelectObject(pen);
		dc.MoveTo(m_SelectedRect->left,m_SelectedRect->top);
		dc.LineTo(m_SelectedRect->right,m_SelectedRect->top);
		dc.LineTo(m_SelectedRect->right,m_SelectedRect->bottom);
		dc.LineTo(m_SelectedRect->left,m_SelectedRect->bottom);
		dc.LineTo(m_SelectedRect->left,m_SelectedRect->top);
	}
}

void CChildView::OnLButtonDown(UINT var, CPoint point)
{
	//начало выделения области мышью
	p1=point;
	m_IsSelectedRect = m_IsMousePressed=true;
}

void CChildView::OnLButtonUp(UINT var, CPoint p2)
{
	//окончание выделения области мышью
	m_IsMousePressed = 0;
	m_SelectedRect=new CRect(min(p1.x,p2.x),min(p1.y,p2.y),max(p1.x,p2.x),max(p1.y,p2.y));
}

void CChildView::OnMouseMove(UINT var, CPoint p2)
{
	//прорисовка рамки при выделении
	if(m_IsSelectedRect && m_IsMousePressed)
	{
		m_SelectedRect=new CRect(min(p1.x,p2.x),min(p1.y,p2.y),max(p1.x,p2.x),max(p1.y,p2.y));
		Invalidate(1);
	}
}

void CChildView::OnKeyDown(UINT nChar,UINT nRepCount,UINT nFlags){
	//поворот наблюдателя
	if(nChar==37){		//влево
		PView(1)+=step;
		if (PView(1)>360) 
			PView(1)-=360;
		Invalidate();
	}
	else if(nChar==39){	//вправо
		PView(1)-=step;
		if (PView(1)<0) 
			PView(1)+=360;
		Invalidate();
	}
	else if(nChar==38){	//вверх
		PView(2)+=step;
		if (PView(2)>360) 
			PView(2)-=360;
		Invalidate();
	}
	else if(nChar==40){ //вниз
		PView(2)-=step;
		if (PView(2)<0) 
			PView(2)+=360;
		Invalidate();
	}
	//поворот источника света
	else if(nChar==65){	//A
		PLight(1)-=step;
		if (PLight(1)<0) 
			PLight(1)+=360;
		Invalidate();
	}
	else if(nChar==68){	//D
		PLight(1)+=step;
		if (PLight(1)>360) 
			PLight(1)-=360;
		Invalidate();
	}
	else if(nChar==87){	//W
		PLight(2)-=step;
		if (PLight(2)<0) 
			PLight(2)+=360;
		Invalidate();
	}
	else if(nChar==83){ //S
		PLight(2)+=step;
		if (PLight(2)>360) 
			PLight(2)-=360;
		Invalidate();
	}
	//переключение модели освещения
	else if(nChar==79){	//O
		m=1;
		Invalidate();
	}
	else if(nChar==80){ //P
		m=0;
		Invalidate();
	}

}

//диалог установки цвета эллипсоида
void CChildView::OnSetcolor()
{
	CColorDialog ccd;
	if(ccd.DoModal()==IDOK){
		col=ccd.GetColor();
		Invalidate();
	}
}
//диалоги установки размеров эллипсоида
void CChildView::OnSetsize()
{
	SizeDialog sd;
	if(sd.DoModal()==IDOK){
		int a=sd.GetX(),b=sd.GetY(),c=sd.GetZ();
		pp=new CEllipsoid(a,b,c);
		Invalidate();
	}
}
//диалог сохранения выделенной области в файл
void CChildView::OnSave1()
{
	CFileDialog fOpenDlg(FALSE, _T("fif"), 0, NULL, _T("Image File (*.bmp)|*.bmp|"), this);

	// заголовок диалога
	fOpenDlg.m_pOFN->lpstrTitle=_T("Select BMP File");

	// отображение диалога
	if(fOpenDlg.DoModal()==IDOK)
	{
		m_saved_file = fOpenDlg.GetPathName();
		Invalidate();
		Sleep(1000);
		ClientToBmp(GetSafeHwnd(), m_saved_file, *m_SelectedRect  );
	}
	m_IsSelectedRect = false;

}
//сохранение выделенной области в файл
int ClientToBmp (HWND hWnd, const char* filepath, CRect r)
{
	//открытие фвйла для записи
	HANDLE fh = CreateFile (filepath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (fh == INVALID_HANDLE_VALUE)
		return 2;
	//информационный заголовок
	BITMAPINFOHEADER bi;
	ZeroMemory (&bi, sizeof (BITMAPINFOHEADER));
	bi.biSize = sizeof (BITMAPINFOHEADER);
	bi.biWidth = r.right - r.left;
	bi.biHeight = r.bottom - r.top;
	bi.biPlanes = 1;
	bi.biBitCount = 24; //16;
	bi.biSizeImage = (bi.biWidth * bi.biBitCount + 31)/32*4*bi.biHeight;
	//файловый заголовок
	BITMAPFILEHEADER bmfHdr;
	ZeroMemory (&bmfHdr, sizeof (BITMAPFILEHEADER));
	bmfHdr.bfType = ('M'<<8)|'B'; //0x4D42; //BM
	bmfHdr.bfSize = bi.biSizeImage + sizeof (BITMAPFILEHEADER) + bi.biSize;
	bmfHdr.bfReserved1 = bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)bi.biSize;
	//получение в hBitmap выделенной области изображения
	HDC hDC = GetDC (hWnd);
	HDC hDCMem = CreateCompatibleDC (hDC);
	HBITMAP hBitmap = CreateCompatibleBitmap (hDC, bi.biWidth, bi.biHeight);
	HBITMAP oldBitmap = (HBITMAP)SelectObject (hDCMem, hBitmap);
	BitBlt (hDCMem, 0,0, bi.biWidth, bi.biHeight, hDC, r.left, r.top, SRCCOPY);
	hBitmap = (HBITMAP)SelectObject (hDCMem, oldBitmap);

	HANDLE hDIB = GlobalAlloc (GHND, bi.biSizeImage);
	char* lp = (char*)GlobalLock (hDIB);
	//получение изображения в аппаратно-независимом формате
	GetDIBits (hDC, hBitmap, 0, bi.biHeight, lp, (LPBITMAPINFO)&bi, DIB_RGB_COLORS);
	DWORD dwWritten = sizeof (BITMAPFILEHEADER);
	//запись файлового заголовка
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	dwWritten = sizeof (BITMAPINFOHEADER);
	//запись информационного заголовка
	WriteFile (fh, (LPSTR)&bi, sizeof (BITMAPINFOHEADER), &dwWritten, NULL);
	dwWritten = bi.biSizeImage;
	//запись изображения в аппаратно-независимом формате
	WriteFile (fh, lp, bi.biSizeImage, &dwWritten, NULL);

	GlobalUnlock(hDIB);   
	GlobalFree(hDIB);

	DeleteObject(hBitmap);
	lp = NULL;
	CloseHandle (fh);
	ReleaseDC (hWnd, hDCMem);
	ReleaseDC (hWnd, hDC);
	DeleteDC (hDCMem);
	DeleteDC (hDC);
	if (dwWritten == 2) return 2;
	return 0;


} 


void CChildView::OnSize(UINT nType, int cx, int cy) {
	CWnd::OnSize(nType, cx, cy);
	CPaintDC dc(this);

	pp->DrawEnlighted(dc, PView, PLight, CRect(200, 200, 500, 500), col, m);
	//cWindow.SetRect(200, 200, cx - 100, cy - 100);
}

