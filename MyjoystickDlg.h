// MyjoystickDlg.h : header file
//

#if !defined(AFX_MYJOYSTICKDLG_H__C0B3F220_B560_4CC0_AE7C_E41C6CCE2267__INCLUDED_)
#define AFX_MYJOYSTICKDLG_H__C0B3F220_B560_4CC0_AE7C_E41C6CCE2267__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyjoystickDlg dialog

class CMyjoystickDlg : public CDialog
{
// Construction
public:
	CMyjoystickDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMyjoystickDlg)
/*	enum { IDD = IDD_MYJOYSTICK_DIALOG };
	CButton	m_btn4;
	CButton	m_btn3;
	CButton	m_btn2;
	CButton	m_btn1;
	//}}AFX_DATA
*/
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyjoystickDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyjoystickDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_Absolute;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYJOYSTICKDLG_H__C0B3F220_B560_4CC0_AE7C_E41C6CCE2267__INCLUDED_)
