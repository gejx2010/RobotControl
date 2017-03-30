#if !defined(AFX_PATHPLANDLG_H__CEFC6C93_09D3_4C06_B3B8_D8B5616F390D__INCLUDED_)
#define AFX_PATHPLANDLG_H__CEFC6C93_09D3_4C06_B3B8_D8B5616F390D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PathPlanDlg.h : header file
//
#include "RobotControlView.h"
#include "LinerPlanSetDlg.h"
#include "AutoPlanSetDlg.h"
#include "HandControlDlg.h"
//#include "MainFrm.h"
//#include "RobotControlDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CPathPlanDlg dialog

class CPathPlanDlg : public CDialog
{
// Construction
public:
	CPathPlanDlg(CWnd* pParent = NULL);   // standard constructor
	CRobotControlView* view;
	CRobotControlDoc* doc;
	CLinerPlanSetDlg* pLinerPlanSetDlg;
	CAutoPlanSetDlg* pAutoPlanSetDlg;
	CHandControlDlg* pHandControlDlg;
	void SendMessageToJXB();
//	friend class CMainFrame;
// Dialog Data
	//{{AFX_DATA(CPathPlanDlg)
	enum { IDD = IDD_PATHPLAN };
	float	m_JNT0;
	float	m_JNT1;
	float	m_JNT2;
	float	m_JNT3;
	float	m_JNT4;
	float	m_JNT5;
	float	m_JNT6;
	float	m_JNT7;
	double	m_ts;
	int		m_time;
	float	m_dpx;
	float	m_dpy;
	float	m_dpz;
	float	m_daif;
	float	m_dbit;
	float	m_dgam;
	float	m_ini_j0;
	float	m_ini_j1;
	float	m_ini_j2;
	float	m_ini_j3;
	float	m_ini_j4;
	float	m_ini_j5;
	float	m_ini_j6;
	float	m_ini_j7;
	float	m_ini_j8;
	float	m_baspx;
	float	m_baspy;
	float	m_baspz;
	float	m_basaif;
	float	m_basbit;
	float	m_basgam;
	double CtsVel;
	
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPathPlanDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	//////////////////////////////////////////////////////////////////////////
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);    //消息处理函数---乐
	/////////////////////////////////////////////////////////////////////////


// Implementation
public:
	int kn,No;//kn规划总步数，NO当前规划步数
	int Planradio;//规划模式标志位
	int PreProgrammFlag;//预编程标志位
	int ControlMode;//模式标志位
	int numtime;//当前规划时间
	int CapOrientFlag;
	double GivenObj[6];
	double PreObj[3];
	float ceta[Ni][8];
	double VelCts;//导轨速度
	double PosCts;//导轨绝对位置
	TCHAR buf[255];
	int PMacdevice;
	clock_t start;
	clock_t end;


	void ShowJntVariable();
	void qmtomModule();
	bool deviceIsHalt();
//	void InitialSettingData();
	
	// Generated message map functions
	//{{AFX_MSG(CPathPlanDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnButtonSet();
	afx_msg void OnButtonReset();
	afx_msg void OnButtonInit();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRadioLinearplan();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonIniok();
	afx_msg void OnButtonRun();
	afx_msg void OnRadioAutoplan();
	afx_msg void OnButtonStop();
	afx_msg void OnRadioHandcontrol();
	afx_msg void OnRadioSumu();
	afx_msg void OnRadioJxb();
	afx_msg void OnButtonSavedata();
	afx_msg void OnRadioProgramm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	//////////////////////////////////////////////
	afx_msg void OnBnClickedButtonJoystick();  //添加手柄按钮消息函数---乐---自动添加
	afx_msg void OnDestroy();                  //添加释放函数---乐---手动添加
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PATHPLANDLG_H__CEFC6C93_09D3_4C06_B3B8_D8B5616F390D__INCLUDED_)
