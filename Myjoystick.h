// Myjoystick.h : main header file for the MYJOYSTICK application
//

#if !defined(AFX_MYJOYSTICK_H__FE2FF167_CFAE_4F1A_8863_D3D9B6A482BF__INCLUDED_)
#define AFX_MYJOYSTICK_H__FE2FF167_CFAE_4F1A_8863_D3D9B6A482BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyjoystickApp:
// See Myjoystick.cpp for the implementation of this class
//

class CMyjoystickApp : public CWinApp
{
public:
	CMyjoystickApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyjoystickApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyjoystickApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYJOYSTICK_H__FE2FF167_CFAE_4F1A_8863_D3D9B6A482BF__INCLUDED_)
