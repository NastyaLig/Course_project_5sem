// SizeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "SizeDialog.h"


// SizeDialog dialog

IMPLEMENT_DYNAMIC(SizeDialog, CDialog)

SizeDialog::SizeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(SizeDialog::IDD, pParent)
{

	EnableAutomation();

}

SizeDialog::~SizeDialog()
{
}

void SizeDialog::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialog::OnFinalRelease();
}

void SizeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, xedit);
	DDX_Control(pDX, IDC_EDIT3, yedit);
	DDX_Control(pDX, IDC_EDIT2, zedit);
}


BEGIN_MESSAGE_MAP(SizeDialog, CDialog)
	ON_BN_CLICKED(IDOK, &SizeDialog::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &SizeDialog::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT3, &SizeDialog::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT2, &SizeDialog::OnEnChangeEdit2)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(SizeDialog, CDialog)
END_DISPATCH_MAP()

// Note: we add support for IID_ISizeDialog to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {140C0F47-65E4-4C40-9F5E-2B44453B3970}
static const IID IID_ISizeDialog =
{ 0x140C0F47, 0x65E4, 0x4C40, { 0x9F, 0x5E, 0x2B, 0x44, 0x45, 0x3B, 0x39, 0x70 } };

BEGIN_INTERFACE_MAP(SizeDialog, CDialog)
	INTERFACE_PART(SizeDialog, IID_ISizeDialog, Dispatch)
END_INTERFACE_MAP()


// SizeDialog message handlers

void SizeDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void SizeDialog::OnEnChangeEdit1()
{
	CString* s=new CString();
	xedit.GetWindowText(*s);
	a=atoi(s->GetBuffer());
}

void SizeDialog::OnEnChangeEdit3()
{
	CString* s=new CString();
	yedit.GetWindowText(*s);
	b=atoi(s->GetBuffer());
}

void SizeDialog::OnEnChangeEdit2()
{
	CString* s=new CString();
	zedit.GetWindowText(*s);
	c=atoi(s->GetBuffer());
}
int SizeDialog::GetX(){
	return a;
}
int SizeDialog::GetY(){
	return b;
}
int SizeDialog::GetZ(){
	return c;
}