// PathPlanDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RobotControl.h"
#include "PathPlanDlg.h"
#include "MainFrm.h"
#include "Dynamic_spacerobot.h"
#include "math.h"
#include "m5apiw32.h"
#include "InitHardware.h"
#include "conio.h"

///////////////////////////////////////////////
#include "Myjoystick.h"
#include"Myjoystickdlg.h"
#include"mmsystem.h"
///////////////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


double ini_ang[8], basiniPE[6], PEint[6], PEmid[6], PEend[6], now_ang[8],now_PEca[6], qdes[8];
double next_ang[8], next_angvel[8], next_baspe[6], next_basvel[6];
double EndPE[Ni][6];
double VelocityLimit[6]={0,0,0,0,0,0};
#define CODEANGTRANS 22.7555555555555556
#define PI 3.14159265359
#define DIAMETER 0.058

// double size[6]={0,0.3,0.328,0.277,0.206,0.1};
// double dh[8][4]={{0,-PI/2,d1,0},{0,PI/2,d2,0},{0,-PI/2,0,0},{0,PI/2,d3,0},{0,-PI/2,0,0},{0,PI/2,d4,0},{0,-PI/2,0,0},{0,PI/2,d5,0}};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////�ֱ����Ƴ���/////////////////////////////////////////////////////////////////////////
bool ButtonJoystickFlag=true;
void CPathPlanDlg::OnBnClickedButtonJoystick()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int result;
	UINT message; WPARAM wParam;LPARAM lParam;int btnNum;
	if(ButtonJoystickFlag)
	{
		result=joySetCapture(CDialog::m_hWnd, JOYSTICKID1, 0, FALSE);   //����ҡ�˺�����������ֵ��ֵ��result---��
		
		AllocConsole();
		_cprintf("������""ButtonJoystickFlag=%d",ButtonJoystickFlag);

		MessageBox("ʵ�����»�ȡ��Ϸ��");

		if (result == JOYERR_NOCANDO)
		{           
			MessageBeep(MB_ICONEXCLAMATION);
			MessageBox("���ܲ�����Ϸ��", NULL, MB_OK | MB_ICONEXCLAMATION);
			//return -1;
		}
		if (result == JOYERR_UNPLUGGED)
		{    
			MessageBeep(MB_ICONEXCLAMATION);
			MessageBox("��Ϸ��δ��ϵͳ����", NULL, MB_OK | MB_ICONEXCLAMATION);
			//return -1;
		}
		if(result==JOYERR_NOERROR)
		{
			ButtonJoystickFlag=false;
		}
	}
	else
	{
		CPathPlanDlg::OnDestroy(); 
		ButtonJoystickFlag=true;
	}

	_cprintf("������222""ButtonJoystickFlag=%d",ButtonJoystickFlag);

}
/////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool flag = true;
double vel_JoyStick=0.5;
double velJoyStick=2;
//////////////////////////////////���Ժ���---��////////////////////////////////////////////////////////////////
void test(UINT message, WPARAM wParam, LPARAM lParam,int btnNum)    
{
	if (btnNum == 9)
	{
		AllocConsole();
		_cprintf("%dwParam=%d;", btnNum, wParam);
		_cprintf("%dmessage=%d;", btnNum, message);              
		_cprintf("%dy(H(lParam))=%d;%dx(L(lParam))=%d;\n", btnNum, HIWORD(lParam), btnNum, LOWORD(lParam)); 
	}
}

void test(UINT message, WPARAM wParam, LPARAM lParam)  
{
		AllocConsole();
		_cprintf("wParam=%d;", wParam);
		_cprintf("message=%d;",  message);              
		_cprintf("y(H(lParam))=%d;x(L(lParam))=%d;\n",  HIWORD(lParam), LOWORD(lParam)); 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

LRESULT CPathPlanDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch(message){	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////��������������---��/////////////////////////////////////////////////////
	case MM_JOY1MOVE : 
		test(message, wParam, lParam, 9);     //���Դ��ݵ���Ϣ������---��---�Լ���д
		if (flag)
		{
			for (int i=0; i <= 10; ++i)
			{
			    double btn = pow(2.0, i);
				if (wParam ==btn)
				{
					MessageBeep(MB_ICONEXCLAMATION); //����ϵͳ��Ч---��
					switch (i)
					{
					case 0:
						m_JNT0+=vel_JoyStick;
						UpdateData(FALSE);
						doc->m_Module[0].JntVar_trans=m_JNT0;
						view->InvalidateRect(NULL, FALSE);
						if(ControlMode==1)
						{
							CPathPlanDlg::OnButtonSet();
						}
						break;    //��Ӷ�������---��---�Լ���д
					case 1:
						m_JNT1+=velJoyStick;
						UpdateData(FALSE);
						doc->m_Module[1].JntVar_rot=m_JNT1;
						view->InvalidateRect(NULL, FALSE);
						if(ControlMode==1)
						{
							CPathPlanDlg::OnButtonSet();
						}
						break;
					case 2:
						m_JNT2+=velJoyStick; 
						UpdateData(FALSE);
						doc->m_Module[2].JntVar_rot=m_JNT2;
						view->InvalidateRect(NULL, FALSE);
						if(ControlMode==1)
						{
							CPathPlanDlg::OnButtonSet();
						}
						break;
					case 3:
						m_JNT3+=velJoyStick;
						UpdateData(FALSE);
						doc->m_Module[3].JntVar_rot=m_JNT3;
						view->InvalidateRect(NULL, FALSE);
						if(ControlMode==1)
						{
							CPathPlanDlg::OnButtonSet();
						}
						break;
					case 4:
						m_JNT4+=velJoyStick; 
						UpdateData(FALSE);
						doc->m_Module[4].JntVar_rot=m_JNT4;
						view->InvalidateRect(NULL, FALSE);
						if(ControlMode==1)
						{
							CPathPlanDlg::OnButtonSet();
						}
						break;
					case 5:
						m_JNT5+=velJoyStick;
						UpdateData(FALSE);
						doc->m_Module[5].JntVar_rot=m_JNT5;
						view->InvalidateRect(NULL, FALSE);
						if(ControlMode==1)
						{
							CPathPlanDlg::OnButtonSet();
						}
						break;
					case 6:
						m_JNT6+=velJoyStick;
						UpdateData(FALSE);
						doc->m_Module[6].JntVar_rot=m_JNT6;
						view->InvalidateRect(NULL, FALSE);
						if(ControlMode==1)
						{
							CPathPlanDlg::OnButtonSet();
						}
						break;
					case 7:
						m_JNT7+=velJoyStick;
						UpdateData(FALSE);
						doc->m_Module[7].JntVar_rot=m_JNT7;
						view->InvalidateRect(NULL, FALSE);
						if(ControlMode==1)
						{
							CPathPlanDlg::OnButtonSet();
						}
						break;
					case 8:
						velJoyStick*=-1;
						vel_JoyStick*=-1;
						break;
					}
					flag = false;
				}
				else
					/*null*/;							
				//_sleep(20);
			}
		}		
		if (wParam==0)
		{
			//test(message,wParam,lParam);
			flag = true;
		}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		WORD x, y;                                                 //�޷�����16λ������2byte��ȡֵ��Χ0--65535----��
		POINT pt;                                                 //����һ������������ֵ�ýṹ�������POINT�ṹ����windef.hͷ�ļ��ж���---��
//		UpdateData(TRUE);
		//��ȡ��ǰ��Ļ���λ��
		GetCursorPos(&pt);                                        //GetCursorPos()������Ҫһ���ṹ��ָ�룬��Ż�ȡ����ߵ���ֵ��x,y---��

		//��Ϸ���ڵ�ǰϵͳ�е�λ�����귶Χ��0 65535��λ�ñ�ʾ��Χ��0-31
		if (true){
			x = LOWORD(lParam)/2048;
			y = HIWORD(lParam)/2048;
			//�����Ϸ��������λ�õ����,�ƶ���굽��ߡ���֮��Ȼ
			if(x <= 12){
				pt.x = pt.x + x - 15;
			}
			else if(x >= 20)
				pt.x = pt.x + x - 15;
			//�����Ϸ��������λ�õ��±�,�ƶ���굽�±ߡ���֮��Ȼ
			if(y <= 12)
				pt.y = pt.y + y - 15;
			else if(y >= 20)
				pt.y = pt.y + y - 15;
		}
		else{
			CDC* pDC = GetDC();
			x=LOWORD(lParam);
			y=HIWORD(lParam);
			pt.x=(pDC->GetDeviceCaps(HORZRES)*x)/65536;
			pt.y=(pDC->GetDeviceCaps(VERTRES)*y)/65536;
			ReleaseDC(pDC);
		}
		/* Set the new cursor position.*/
		SetCursorPos(pt.x, pt.y);
		break;
	case MM_JOY1BUTTONUP :
		flag = true;
		break;
	}
	return CDialog::WindowProc(message, wParam, lParam);
}	
///////////////////////////////////////////////////////////////////////////
void CPathPlanDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	joyReleaseCapture(JOYSTICKID1);                                     //�ͷŻ�ȡ��ҡ��1---��
	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CPathPlanDlg dialog


CPathPlanDlg::CPathPlanDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPathPlanDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPathPlanDlg)
	m_JNT0 = 0.375f;
	m_JNT1 = -20.0f;
	m_JNT2 = 25.0f;
	m_JNT3 = -45.0f;
	m_JNT4 = 71.0f;
	m_JNT5 = -20.0f;
	m_JNT6 = 20.0f;
	m_JNT7 = 0.0f;
	m_ts = 10;
	m_time = 80;
	m_ini_j0 = 0.0f;
	m_ini_j1 = 0.0f;
	m_ini_j2 = 0.0f;
	m_ini_j3 = 0.0f;
	m_ini_j4 = 0.0f;
	m_ini_j5 = 0.0f;
	m_ini_j6 = 0.0f;
	m_ini_j7 = 0.0f;
	m_baspx = 0.0f;
	m_baspy = 0.0f;
	m_baspz = 0.0f;
	m_basaif = 0.0f;
	m_basbit = 0.0f;
	m_basgam = 0.0f;
	kn=0;
	No=0;
	numtime=0;
	PreProgrammFlag=0;
	CtsVel=1;
	PMacdevice=0;
	
	//AllocConsole();
	//}}AFX_DATA_INIT
}


void CPathPlanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPathPlanDlg)
	DDX_Text(pDX, IDC_EDIT_JNT1, m_JNT1);
	DDX_Text(pDX, IDC_EDIT_JNT2, m_JNT2);
	DDX_Text(pDX, IDC_EDIT_JNT3, m_JNT3);
	DDX_Text(pDX, IDC_EDIT_JNT4, m_JNT4);
	DDX_Text(pDX, IDC_EDIT_JNT5, m_JNT5);
	DDX_Text(pDX, IDC_EDIT_JNT6, m_JNT6);
	DDX_Text(pDX, IDC_EDIT_JNT7, m_JNT7);
	DDX_Text(pDX, IDC_EDIT_ACCTIME, m_ts);
	DDX_Text(pDX, IDC_EDIT_PLANTIME, m_time);
	DDX_Text(pDX, IDC_EDIT_JNT0, m_JNT0);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPathPlanDlg, CDialog)
	//{{AFX_MSG_MAP(CPathPlanDlg)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_INIT, OnButtonInit)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_RADIO_LINEARPLAN, OnRadioLinearplan)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_INIOK, OnButtonIniok)
	ON_BN_CLICKED(IDC_BUTTON_RUN, OnButtonRun)
	ON_BN_CLICKED(IDC_RADIO_AUTOPLAN, OnRadioAutoplan)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_RADIO_HANDCONTROL, OnRadioHandcontrol)
	ON_BN_CLICKED(IDC_RADIO_SUMU, OnRadioSumu)
	ON_BN_CLICKED(IDC_RADIO_JXB, OnRadioJxb)
	ON_BN_CLICKED(IDC_BUTTON_SAVEDATA, OnButtonSavedata)
	ON_BN_CLICKED(IDC_RADIO_PROGRAMM, OnRadioProgramm)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_JOYSTICK, &CPathPlanDlg::OnBnClickedButtonJoystick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPathPlanDlg message handlers

BOOL CPathPlanDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT0))->SetRange(-1000,1000,true);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT0))->SetTicFreq(200);
    ((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT0))->SetPos(0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT1))->SetRange(-180,180,true);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT1))->SetTicFreq(36);
    ((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT1))->SetPos(0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT2))->SetRange(-90,90,true);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT2))->SetTicFreq(18);
    ((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT2))->SetPos(0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT3))->SetRange(-180,180,true);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT3))->SetTicFreq(36);
    ((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT3))->SetPos(0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT4))->SetRange(-120,120,true);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT4))->SetTicFreq(24);
    ((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT4))->SetPos(0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT5))->SetRange(-180,180,true);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT5))->SetTicFreq(36);
    ((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT5))->SetPos(0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT6))->SetRange(-150,150,true);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT6))->SetTicFreq(30);
    ((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT6))->SetPos(0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT7))->SetRange(-180,180,true);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT7))->SetTicFreq(36);
    ((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT7))->SetPos(0);
	
	ControlMode=0;
	((CButton*)GetDlgItem(IDC_RADIO_SUMU))->SetCheck(true);
	//��ʼ������
 //	init_robot_size(size);
 //	init_dh(dh);
// 	R0c[0][0]=T0C[0][0]=1;/*�任����*/
// 	R0c[0][1]=T0C[0][1]=0;
// 	R0c[0][2]=T0C[0][2]=0;
// 	R0c[1][0]=T0C[1][0]=0;
// 	R0c[1][1]=T0C[1][1]=1;
// 	R0c[1][2]=T0C[1][2]=0;
// 	R0c[2][0]=T0C[2][0]=0;
// 	R0c[2][1]=T0C[2][1]=0;
// 	R0c[2][2]=T0C[2][2]=1;
// 	T0C[3][0]=0;
// 	T0C[3][1]=0;
// 	T0C[3][2]=0;
// 	
// 	rca0[0]=0; rca0[1]=0; rca0[2]=0;
// 	T0C[0][3]=0; T0C[1][3]=0; T0C[2][3]=0; T0C[3][3]=1;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPathPlanDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	CMainFrame *pframe;
	pframe=(CMainFrame*)::AfxGetApp()->GetMainWnd();
	view=(CRobotControlView*)pframe->GetActiveView(); //�õ���ǰ����Ӵ�ָ��
	doc=view->GetDocument()->doc_delay;                          //�õ��Ӵ��������ָ��
	int ID=((CSliderCtrl*)pScrollBar)->GetDlgCtrlID();
	switch(ID)
	{
	case IDC_SLIDER_JNT0:
		m_JNT0=((float)((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT0))->GetPos())/1000;
		UpdateData(FALSE);
		doc->m_Module[0].JntVar_trans=m_JNT0;
		view->InvalidateRect(NULL, FALSE);
		break;
	case IDC_SLIDER_JNT1:
		m_JNT1=(float)((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT1))->GetPos();
		UpdateData(FALSE);
		doc->m_Module[1].JntVar_rot=m_JNT1;
		view->InvalidateRect(NULL, FALSE);
		break;
	case IDC_SLIDER_JNT2:
		m_JNT2=(float)((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT2))->GetPos();
		UpdateData(FALSE);
		doc->m_Module[2].JntVar_rot=m_JNT2;
		view->InvalidateRect(NULL, FALSE);
		break;
	case IDC_SLIDER_JNT3:
		m_JNT3=(float)((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT3))->GetPos();
		UpdateData(FALSE);
		doc->m_Module[3].JntVar_rot=m_JNT3;
		view->InvalidateRect(NULL, FALSE);
		break;
	case IDC_SLIDER_JNT4:
		m_JNT4=(float)((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT4))->GetPos();
		UpdateData(FALSE);
		doc->m_Module[4].JntVar_rot=m_JNT4;
		view->InvalidateRect(NULL, FALSE);
		break;
	case IDC_SLIDER_JNT5:
		m_JNT5=(float)((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT5))->GetPos();
		UpdateData(FALSE);
		doc->m_Module[5].JntVar_rot=m_JNT5;
		view->InvalidateRect(NULL, FALSE);
		break;
	case IDC_SLIDER_JNT6:
		m_JNT6=(float)((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT6))->GetPos();
		UpdateData(FALSE);
		doc->m_Module[6].JntVar_rot=m_JNT6;
		view->InvalidateRect(NULL, FALSE);
		break;
	case IDC_SLIDER_JNT7:
		m_JNT7=(float)((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT7))->GetPos();
		UpdateData(FALSE);
		doc->m_Module[7].JntVar_rot=m_JNT7;
		view->InvalidateRect(NULL, FALSE);
		break;
	default:break;
	}
/*	doc->jnt0=m_JNT0;
	doc->jnt1=m_JNT1;
	doc->jnt2=m_JNT2;
	doc->jnt3=m_JNT3;
	doc->jnt4=m_JNT4;
	doc->jnt5=m_JNT5;
	doc->jnt6=m_JNT6;
	doc->jnt7=m_JNT7;*/
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

}

void CPathPlanDlg::OnButtonSet() 
{
	// TODO: Add your control notification handler code here

	UpdateData(true);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT0))->SetPos(int(m_JNT0));
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT1))->SetPos(int(m_JNT1));
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT2))->SetPos(int(m_JNT2));
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT3))->SetPos(int(m_JNT3));
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT4))->SetPos(int(m_JNT4));
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT5))->SetPos(int(m_JNT5));
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT6))->SetPos(int(m_JNT6));
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT7))->SetPos(int(m_JNT7));

	CMainFrame* frame=(CMainFrame*)AfxGetApp()->GetMainWnd();
	view=(CRobotControlView*)frame->GetActiveView();
	doc=view->GetDocument()->doc_delay; 
	doc->m_Module[0].JntVar_trans=m_JNT0;
	doc->m_Module[1].JntVar_rot=m_JNT1;
	doc->m_Module[2].JntVar_rot=m_JNT2;
	doc->m_Module[3].JntVar_rot=m_JNT3;
	doc->m_Module[4].JntVar_rot=m_JNT4;
	doc->m_Module[5].JntVar_rot=m_JNT5;
	doc->m_Module[6].JntVar_rot=m_JNT6;
	doc->m_Module[7].JntVar_rot=m_JNT7;
	doc->jnt0=m_JNT0;
	doc->jnt1=m_JNT1;
	doc->jnt2=m_JNT2;
	doc->jnt3=m_JNT3;
	doc->jnt4=m_JNT4;
	doc->jnt5=m_JNT5;
	doc->jnt6=m_JNT6;
	doc->jnt7=m_JNT7;
	doc->angelset[0]=m_JNT0;
	doc->angelset[1]=m_JNT1;
	doc->angelset[2]=m_JNT2;
	doc->angelset[3]=m_JNT3;
	doc->angelset[4]=m_JNT4;
	doc->angelset[5]=m_JNT5;
	doc->angelset[6]=m_JNT6;
	doc->angelset[7]=m_JNT7;
	

	view->InvalidateRect(NULL, FALSE);
	if(ControlMode==1)
	{
		int device=frame->pSiderBar->pCtrlTab->pInitHardware->m_device;
		int PmacStateValue=frame->pSiderBar->pCtrlTab->pInitHardware->PmacstateValue;
		if(PmacStateValue)
		{
			PosCts=(360*30*CODEANGTRANS*(-m_JNT0))/(PI*DIAMETER);
			char PosStr[100];
			char outstr[256]="#1j=";  
			_gcvt(PosCts,50,PosStr);
			strcat(outstr,PosStr);
			//	AfxMessageBox(outstr);
			PmacGetResponseA(PMacdevice,buf,255,outstr);
				float p,v;
			PmacGetResponseA(PMacdevice,buf,255,"p");
			p=atof(buf);
			PmacGetResponseA(PMacdevice,buf,255,"v");
			v=atof(buf);
			while(abs(p-PosCts)>50||v!=0)
			{
					PmacGetResponseA(PMacdevice,buf,255,"p");
					p=atof(buf);
					PmacGetResponseA(PMacdevice,buf,255,"v");
					v=atof(buf);

					PmacGetResponseA(PMacdevice,buf,255,"?"); 
        			char b=buf[9];
					if(b=='C')
					{
						b=12;
					}
					if(b&8)
					{

						PmacGetResponseA(PMacdevice,buf,255,"k");
						break;
					}

			}

			PmacGetResponseA(PMacdevice,buf,255,"k");
//			Sleep(60000);
//			PmacGetResponseA(1,buf,255,"k");
	
		}
		SetTimer(3, 100, NULL);
		start = clock();
		for(int i=1;i<8;i++)
		{
			::PCube_resetModule(device,i);
		}
		::PCube_moveRamp(device,1,-m_JNT1*PI/180,2*PI/180,4*PI/180);
		//Sleep(2000);
		::PCube_moveRamp(device,2,m_JNT2*PI/180,2*PI/180,4*PI/180);
		//Sleep(2000);
		::PCube_moveRamp(device,3,-m_JNT3*PI/180,2*PI/180,4*PI/180);
		//Sleep(2000);
		::PCube_moveRamp(device,4,m_JNT4*PI/180,2*PI/180,4*PI/180);
		//Sleep(2000);
		::PCube_moveRamp(device,5,-m_JNT5*PI/180,2*PI/180,4*PI/180);
		//Sleep(2000);
		::PCube_moveRamp(device,6,m_JNT6*PI/180,2*PI/180,4*PI/180);
		//sSleep(2000);
		::PCube_moveRamp(device,7,-m_JNT7*PI/180,2*PI/180,4*PI/180);


//		Sleep(4000);
//		PmacGetResponseA(0,buf,255,"k");


	}
	}

void CPathPlanDlg::OnButtonReset() 
{
	// TODO: Add your control notification handler code here
	m_JNT0=0;
	m_JNT1=-7.5;
	m_JNT2=0;
	m_JNT3=0;
	m_JNT4=0;
	m_JNT5=0;
	m_JNT6=0;
	m_JNT7=0;
	UpdateData(false);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT0))->SetPos(0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT1))->SetPos(-7.5);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT2))->SetPos(0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT3))->SetPos(0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT4))->SetPos(0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT5))->SetPos(0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT6))->SetPos(0);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_JNT7))->SetPos(0);

	CMainFrame* frame=(CMainFrame*)AfxGetApp()->GetMainWnd();
	view=(CRobotControlView*)frame->GetActiveView();
	doc=view->GetDocument()->doc_delay; 
	doc->jnt0=m_JNT0;
	doc->jnt1=m_JNT1;
	doc->jnt2=m_JNT2;
	doc->jnt3=m_JNT3;
	doc->jnt4=m_JNT4;
	doc->jnt5=m_JNT5;
	doc->jnt6=m_JNT6;
	doc->jnt7=m_JNT7;
	doc->m_Module[0].JntVar_trans=m_JNT0;
	doc->m_Module[1].JntVar_rot=m_JNT1;
	doc->m_Module[2].JntVar_rot=m_JNT2;
	doc->m_Module[3].JntVar_rot=m_JNT3;
	doc->m_Module[4].JntVar_rot=m_JNT4;
	doc->m_Module[5].JntVar_rot=m_JNT5;
	doc->m_Module[6].JntVar_rot=m_JNT6;
	doc->m_Module[7].JntVar_rot=m_JNT7;
	doc->angelset[0]=m_JNT0;
	doc->angelset[1]=m_JNT1;
	doc->angelset[2]=m_JNT2;
	doc->angelset[3]=m_JNT3;
	doc->angelset[4]=m_JNT4;
	doc->angelset[5]=m_JNT5;
	doc->angelset[6]=m_JNT6;
	doc->angelset[7]=m_JNT7;
	view->InvalidateRect(NULL, FALSE);
	if(ControlMode==1)
	{
		int device=frame->pSiderBar->pCtrlTab->pInitHardware->m_device;
		int PmacStateValue=frame->pSiderBar->pCtrlTab->pInitHardware->PmacstateValue;
		if(PmacStateValue)
		{
//			PmacGetResponseA(1,buf,255,"#1HM");//��Ϊ���û��㰴ť
			frame->pSiderBar->pCtrlTab->pInitHardware->GetDlgItem(IDC_BUTTON_ZERO)->SendMessage(BM_CLICK,1,1);
		}

		for(int i=7;i>0;i--)
		{
			::PCube_moveRamp(device,
				i,
				0,
				2*PI/180,
				4*PI/180);
			Sleep(2000);
		}
//		::PCube_moveRamp(device,1,-7.5*PI/180 ,4*PI/180,16*PI/180);
//		Sleep(200);
//		PmacGetResponseA(0,buf,255,"k");
	}
}

void CPathPlanDlg::OnButtonInit() 
{
	// TODO: Add your control notification handler code here
	CMainFrame* frame=(CMainFrame*)AfxGetApp()->GetMainWnd();
	view=(CRobotControlView*)frame->GetActiveView();
	doc=view->GetDocument()->doc_delay; 
	((CButton*)GetDlgItem(IDC_RADIO_LINEARPLAN))->EnableWindow(true);
	((CButton*)GetDlgItem(IDC_RADIO_AUTOPLAN))->EnableWindow(true);
	((CButton*)GetDlgItem(IDC_RADIO_PROGRAMM))->EnableWindow(true);
	((CButton*)GetDlgItem(IDC_RADIO_HANDCONTROL))->EnableWindow(true);
	((CButton*)GetDlgItem(IDC_BUTTON_RUN))->EnableWindow(true);
	((CButton*)GetDlgItem(IDC_BUTTON_STOP))->EnableWindow(true);

	double PEI[6];
	double basepe[6]={m_baspx,m_baspy,m_baspz,m_basaif*PI/180,m_basbit*PI/180,m_basgam*PI/180};
	////��ʼ�ؽڽ�
	ini_ang[0]=m_JNT0;
	ini_ang[1]=m_JNT1*PI/180;
	ini_ang[2]=m_JNT2*PI/180;
	ini_ang[3]=m_JNT3*PI/180;
	ini_ang[4]=m_JNT4*PI/180;
	ini_ang[5]=m_JNT5*PI/180;
	ini_ang[6]=m_JNT6*PI/180;
	ini_ang[7]=m_JNT7*PI/180;
 
	Forwardkine_static(ini_ang, PEI ); //�õ���ʼĩ��λ��
  
    for(int i=0; i<6; i++)  { if(fabs(PEI[i])<10e-6) PEI[i]=0;   }
	
    UpdateData(false);		
	//����ʼĩ��λ�˸���DOC��
	doc->ini_px=PEI[0];
	doc->ini_py=PEI[1];
	doc->ini_pz=PEI[2];
	
    doc->ini_aif=PEI[3]*180/PI;
	doc->ini_bit=PEI[4]*180/PI;
	doc->ini_gam=PEI[5]*180/PI;
	doc->No=No=0;
	doc->numtime=numtime=0;
	doc->Lineartestflag=false;
	PreProgrammFlag=0;
	UpdateData(true);
	//��ʼ������
	if (ControlMode==1)
	{
		PmacGetResponseA(PMacdevice,buf,255,"j/");
		PmacGetResponseA(PMacdevice,buf,255,"&1");
		PmacGetResponseA(PMacdevice,buf,255,"CLOSE");
		PmacGetResponseA(PMacdevice,buf,255,"#1->X");	
		PmacGetResponseA(PMacdevice,buf,255,"&1 DEFINE ROT 200");
		PmacGetResponseA(PMacdevice,buf,255,"OPEN ROT");
		PmacGetResponseA(PMacdevice,buf,255,"CLEAR");
		PmacGetResponseA(PMacdevice,buf,255,"LINEAR");
		PmacGetResponseA(PMacdevice,buf,255,"ABS");
		PmacGetResponseA(PMacdevice,buf,255,"TA10");
		PmacGetResponseA(PMacdevice,buf,255,"TS0");
		PmacGetResponseA(PMacdevice,buf,255,"F150000");
		PmacGetResponseA(PMacdevice,buf,255,"CLOSE");
	}
	view->InvalidateRect(NULL, FALSE);
	
}



int CPathPlanDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	pLinerPlanSetDlg=new CLinerPlanSetDlg();
	pLinerPlanSetDlg->Create(IDD_LINERPLANSETTING,this);
	pAutoPlanSetDlg=new CAutoPlanSetDlg();
	pAutoPlanSetDlg->Create(IDD_AUTOPLANSETTING,this);
	pHandControlDlg=new CHandControlDlg();
	pHandControlDlg->Create(IDD_HANDCONTROL,this);
	
	return 0;
}

void CPathPlanDlg::OnRadioLinearplan() 
{
	// TODO: Add your control notification handler code here
	((CButton*)GetDlgItem(IDC_RADIO_LINEARPLAN))->SetCheck(BST_CHECKED);
	Planradio=IDC_RADIO_LINEARPLAN;
	pLinerPlanSetDlg->MoveWindow(350, 150, 300, 260);
	pLinerPlanSetDlg->ShowWindow(SW_SHOW);
	((CButton*)GetDlgItem(IDC_BUTTON_INIOK))->EnableWindow(true);
	///////
//	COMPlanradio=0x00;
	
}

void CPathPlanDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	int SingularFlag=0;
	double wcm[3]={0, 0, 0};
	double now_baspe[6],now_basvel[6], now_angvel[8];
    int i,j;
	CString str;

	if(nIDEvent==0)
	{
		////////////////�������ò���
		for(i=0; i<8; i++)
		{
			now_ang[i]=next_ang[i];
			now_angvel[i]=next_angvel[i];
		
		}
		for(i=0; i<6; i++)
		{
			now_baspe[i]=next_baspe[i];
			now_basvel[i]=next_basvel[i];
		}

		LinearMotionplan(now_ang, now_baspe, PEint, PEend, m_time, m_ts, No+1, 0, next_baspe, next_basvel, next_ang, next_angvel);
		if (SingularFlag==1)
		{
			KillTimer(0);
			AfxMessageBox("�˶�ѧ����");
		}
		qmtomModule();
		ShowJntVariable();

		if (next_ang[1]<-PI||next_ang[1]>PI)
		{
			KillTimer(0);
			AfxMessageBox("�ؽ�1Խ��");
		}
		if (next_ang[2]<-PI/2||next_ang[2]>PI/2)
		{
			KillTimer(0);
			AfxMessageBox("�ؽ�2Խ��");
		}
		if (next_ang[3]<-PI||next_ang[3]>PI)
		{
			KillTimer(0);
			AfxMessageBox("�ؽ�3Խ��");
		}
		if (next_ang[4]<-2*PI/3||next_ang[4]>2*PI/3)
		{
			KillTimer(0);
			AfxMessageBox("�ؽ�4Խ��");
		}
		if (next_ang[5]<-PI||next_ang[5]>PI)
		{
			KillTimer(0);
			AfxMessageBox("�ؽ�5Խ��");
		}
		if (next_ang[6]<-5*PI/6||next_ang[6]>5*PI/6)
		{
			KillTimer(0);
			AfxMessageBox("�ؽ�6Խ��");
		}
		if (next_ang[7]<-PI||next_ang[7]>PI)
		{
			KillTimer(0);
			AfxMessageBox("�ؽ�7Խ��");
		}
		No++;
		numtime++;
		for(i=0;i<8;i++)
		{	
	   		ceta[No+1][i]=next_ang[i];//����������
		}
		if (ControlMode==1)
		{
			SendMessageToJXB();
		}

		//////////////��ֹ�жϼ���ͼ���ݲ���
		if(No>kn-1) 
		{   
			KillTimer(0);
		}
	}
	if(nIDEvent==1)
	{

		for(i=0; i<8; i++)
		{
			now_ang[i]=next_ang[i];
			now_angvel[i]=next_angvel[i];
		}
		for(i=0; i<6; i++)
		{
			now_baspe[i]=next_baspe[i];
			now_basvel[i]=next_basvel[i];
		}
//		if (HandEyeFlag==1)
//		{
//			Auto_PEdesUpdate(); 
//		}
        CaptureCommand=AutoMotionPlan_line(now_ang, now_baspe, GivenObj, wcm, VelocityLimit, CapOrientFlag, No+1,0,next_baspe, next_basvel, next_ang, next_angvel);
		if (SingularFlag==1)
		{
			KillTimer(1);
			AfxMessageBox("�˶�ѧ����");
		}
		if (next_ang[1]<-PI||next_ang[1]>PI)
		{
			KillTimer(1);
			AfxMessageBox("�ؽ�1Խ��");
		}
		if (next_ang[2]<-PI/2||next_ang[2]>PI/2)
		{
			KillTimer(1);
			AfxMessageBox("�ؽ�2Խ��");
		}
		if (next_ang[3]<-PI||next_ang[3]>PI)
		{
			KillTimer(1);
			AfxMessageBox("�ؽ�3Խ��");
		}
		if (next_ang[4]<-2*PI/3||next_ang[4]>2*PI/3)
		{
			KillTimer(1);
			AfxMessageBox("�ؽ�4Խ��");
		}
		if (next_ang[5]<-PI||next_ang[5]>PI)
		{
			KillTimer(1);
			AfxMessageBox("�ؽ�5Խ��");
		}
		if (next_ang[6]<-5*PI/6||next_ang[6]>5*PI/6)
		{
			KillTimer(1);
			AfxMessageBox("�ؽ�6Խ��");
		}
		if (next_ang[7]<-PI||next_ang[7]>PI)
		{
			KillTimer(1);
			AfxMessageBox("�ؽ�7Խ��");
		}
		qmtomModule();
		ShowJntVariable();
		No++;
		numtime++;
		for(i=0;i<8;i++)
		{	
			ceta[No+1][i]=next_ang[i];//����������
		}
		if (ControlMode==1)
		{
			SendMessageToJXB();
		}
       //////////////��ֹ�жϼ���ͼ���ݲ���
		//////������ֹ�ж�
        if(CaptureCommand==1 || No>Ni-1) 
		{   
			KillTimer(1);  
			kn=No;
		}
	}
	if(nIDEvent==2)
	{
		doc->m_Module[0].JntVar_trans=ceta[No][0];
		for (i=1;i<8;i++)
		{
			doc->m_Module[i].JntVar_rot=ceta[No][i]*180/PI;
		}
		UpdateData(false);

		if (ControlMode==1)
		{
			CMainFrame *pframe;
			pframe=(CMainFrame*)::AfxGetApp()->GetMainWnd();
			int device=pframe->pSiderBar->pCtrlTab->pInitHardware->m_device;
			double send_ang[8];
			send_ang[1]=-ceta[No][1];
			send_ang[2]=ceta[No][2];
			send_ang[3]=-ceta[No][3];
			send_ang[4]=ceta[No][4];
			send_ang[5]=-ceta[No][5];
			send_ang[6]=ceta[No][6];
			send_ang[7]=-ceta[No][7];
			for(int i=1;i<8;i++)
			{
				::PCube_moveRamp(device,
					i,
					send_ang[i],
					4*PI/180,
					16*PI/180);
			}
		}
			No++;
			numtime++;
			if (No>kn-1)
			{
				KillTimer(2);
			}
		
	}

	// added by gjx
	if (nIDEvent == 3)
	{
		CMainFrame *pframe;
		pframe=(CMainFrame*)::AfxGetApp()->GetMainWnd();
		
		int device=pframe->pSiderBar->pCtrlTab->pInitHardware->m_device;
		float ff;

		//int test_1 = ::PCube_getPos(device, 1, &ff);
		//_cprintf("ff*180/PI is: %f\n", ff);
		
		float cons;
		if (::PCube_getPos(device, 1, &ff) == 0)
		{
			cons = -ff*180/PI;
			doc->m_Module[1].JntVar_rot = cons;
			doc->jnt1 = cons;
			doc->angelset[1] = cons;
			m_JNT1 = cons;
		}
		if (::PCube_getPos(device, 2, &ff) == 0)
		{
			cons = ff*180/PI;
			doc->m_Module[2].JntVar_rot = cons;
			doc->jnt2 = cons;
			doc->angelset[2] = cons;
			m_JNT2 = cons;
		}
		if (::PCube_getPos(device, 3, &ff) == 0)
		{
			cons = -ff*180/PI;
			doc->m_Module[3].JntVar_rot = cons;
			doc->jnt3 = cons;
			doc->angelset[3] = cons;
			m_JNT3 = cons;
		}
		if (::PCube_getPos(device, 4, &ff) == 0)
		{
			cons = ff*180/PI;
			doc->m_Module[4].JntVar_rot = cons;
			doc->jnt4 = cons;
			doc->angelset[4] = cons;
			m_JNT4 = cons;
		}
		if (::PCube_getPos(device, 5, &ff) == 0)
		{
			cons = -ff*180/PI;
			doc->m_Module[5].JntVar_rot = cons;
			doc->jnt5 = cons;
			doc->angelset[5] = cons;
			m_JNT5 = cons;
		}
		if (::PCube_getPos(device, 6, &ff) == 0)
		{
			cons = ff*180/PI;
			doc->m_Module[6].JntVar_rot = cons;
			doc->jnt6 = cons;
			doc->angelset[6] = cons;
			m_JNT6 = cons;
		}
		if (::PCube_getPos(device, 7, &ff) == 0)
		{
			cons = -ff*180/PI;
			doc->m_Module[7].JntVar_rot = cons;
			doc->jnt7 = cons;
			doc->angelset[7] = cons;
			m_JNT7 = cons;
		}
		end = clock();
		
		if (end - start > 30000 && deviceIsHalt())
		{
			KillTimer(3);
		}
		UpdateData(FALSE);
		view->InvalidateRect(NULL, FALSE);
	}
	view->InvalidateRect(NULL, FALSE);
	CDialog::OnTimer(nIDEvent);
}

bool CPathPlanDlg::deviceIsHalt()
{
	CMainFrame *pframe;
	pframe=(CMainFrame*)::AfxGetApp()->GetMainWnd();
	int device=pframe->pSiderBar->pCtrlTab->pInitHardware->m_device;
	float vel;
	
	float min_speed = 0.000001;
	::PCube_getVel(device, 1, &vel);
	if (min_speed < abs(vel))
		return false;
	::PCube_getVel(device, 2, &vel);
	if (min_speed < abs(vel))
		return false;
	::PCube_getVel(device, 3, &vel);
	if (min_speed < abs(vel))
		return false;
	::PCube_getVel(device, 4, &vel);
	if (min_speed < abs(vel))
		return false;
	::PCube_getVel(device, 5, &vel);
	if (min_speed < abs(vel))
		return false;
	::PCube_getVel(device, 6, &vel);
	if (min_speed < abs(vel))
		return false;
	::PCube_getVel(device, 7, &vel);
	if (min_speed < abs(vel))
		return false;
	return true;
}

void CPathPlanDlg::qmtomModule() 
{
	doc->m_Module[0].JntVar_trans=next_ang[0];
	doc->m_Module[1].JntVar_rot=next_ang[1]*180/PI;
	doc->m_Module[2].JntVar_rot=next_ang[2]*180/PI;
	doc->m_Module[3].JntVar_rot=next_ang[3]*180/PI;
	doc->m_Module[4].JntVar_rot=next_ang[4]*180/PI;
	doc->m_Module[5].JntVar_rot=next_ang[5]*180/PI;
	doc->m_Module[6].JntVar_rot=next_ang[6]*180/PI;
	doc->m_Module[7].JntVar_rot=next_ang[7]*180/PI;
	doc->No=No;
	doc->numtime=numtime;
	doc->jnt0=next_ang[0];
	doc->jnt1=next_ang[1]*180/PI;
	doc->jnt2=next_ang[2]*180/PI;
	doc->jnt3=next_ang[3]*180/PI;
    doc->jnt4=next_ang[4]*180/PI;
	doc->jnt5=next_ang[5]*180/PI;
	doc->jnt6=next_ang[6]*180/PI;
	doc->jnt7=next_ang[7]*180/PI;
	UpdateData(false); 
}

void CPathPlanDlg::ShowJntVariable()
{
	int i;	
	double PEI[6], petemp[3];
	Forwardkine_static(now_ang, PEI ); 
	
	////��ʾ���ݴ���
	for(i=0; i<3; i++)  
	{
		doc->EndPE[i]=EndPE[No][i]=PEI[i];   //ĩ��λ��
		doc->EndPE[i+3]=EndPE[No][i+3]=PEI[i+3]*180/PI; 
//		doc->EndVW[i]=Ve[No][i];   //ĩ���ٶ�
//		doc->EndVW[i+3]=We[No][i]*180/PI;
	}

	for(i=0; i<8; i++)
	{
		doc->JntW[i]= next_angvel[i]*180/PI;  //�ؽڽ��ٶ�
//		doc->JntTau[i]= FbTau[No][i+6];
	}
		
	UpdateData(false);
}

void CPathPlanDlg::OnButtonIniok() 
{
	// TODO: Add your control notification handler code here
	double Tmd[4][4];
    UpdateData(true);		
	Forwardkine_static(ini_ang, PEint);
	
	if(Planradio==IDC_RADIO_LINEARPLAN )
	{	
		m_dpx=doc->des_px;
		m_dpy=doc->des_py;
		m_dpz=doc->des_pz;
		m_daif=doc->des_aif;
		m_dbit=doc->des_bit;
		m_dgam=doc->des_gam;

		PEend[0]=m_dpx;  PEend[1]=m_dpy;  PEend[2]=m_dpz;
		PEend[3]=m_daif*PI/180;  PEend[4]=m_dbit*PI/180;  PEend[5]=m_dgam*PI/180;

		doc->Lineartestflag=true;
		UpdateData(FALSE);
	}

	if(Planradio==IDC_RADIO_AUTOPLAN)
	{
//		AutoPlanObjFlag=doc->AutoPlanObjFlag;
		CapOrientFlag=doc->CapOrientFlag;
/*		HandEyeFlag=pAutoPlanSetDlg->HandEyeFlag;
		if (HandEyeFlag==1)
		{
			int i;
			CMainFrame* frame=(CMainFrame*)AfxGetApp()->GetMainWnd();
			view=(CRobotControlView*)frame->GetActiveView();
			doc=view->GetDocument(); 
			double plan_PEend_des[6], plan_Tmd[4][4];
			plan_PEend_des[0]=(float)(frame->cam_xd);
			plan_PEend_des[1]=(float)(frame->cam_yd);
			plan_PEend_des[2]=1.588;//(float)(frame->cam_zd)
			plan_PEend_des[3]=frame->cam_theta1d;
			plan_PEend_des[4]=frame->cam_theta2d;
			plan_PEend_des[5]=frame->cam_theta3d;
			for (i=0; i<3; i++)
			{
				doc->EndPE[i]=plan_PEend_des[i];
				doc->EndPE[i+3]=plan_PEend_des[i+3]*RAD_TO_DEG;
			}
			doc->des_px=plan_PEend_des[0];
			doc->des_py=plan_PEend_des[1];
			doc->des_pz=plan_PEend_des[2];
			doc->des_aif=plan_PEend_des[3]*RAD_TO_DEG;
			doc->des_bit=plan_PEend_des[4]*RAD_TO_DEG;
			doc->des_gam=plan_PEend_des[5]*RAD_TO_DEG;
			for (i=0; i<6; i++)
			{
				GivenObj[i]=plan_PEend_des[i];
			}
			PE2T(plan_PEend_des, plan_Tmd);
			for(i=0; i<3; i++)
				doc->PreObj[i]=plan_Tmd[i][3]-ds1*plan_Tmd[i][2];
			PEend_des_ori[0]=plan_PEend_des[0];
			PEend_des_ori[1]=plan_PEend_des[1];
			PEend_des_ori[2]=plan_PEend_des[2];
			PEend_des_ori[3]=plan_PEend_des[3];
			PEend_des_ori[4]=plan_PEend_des[4];
			PEend_des_ori[5]=plan_PEend_des[5];
			
		}*/
		ds1=0.1;
		m_dpx=doc->des_px;
		m_dpy=doc->des_py;
		m_dpz=doc->des_pz;
		m_daif=doc->des_aif;
		m_dbit=doc->des_bit;
		m_dgam=doc->des_gam;
		GivenObj[0]=m_dpx;  GivenObj[1]=m_dpy; 	GivenObj[2]=m_dpz; 
		GivenObj[3]=m_daif*PI/180; GivenObj[4]=m_dbit*PI/180;  GivenObj[5]=m_dgam*PI/180;
		PE2T(GivenObj, Tmd);
			if(CapOrientFlag<4)
			{
				PreObj[0]=Tmd[0][3]-ds1*Tmd[0][CapOrientFlag-1];
				PreObj[1]=Tmd[1][3]-ds1*Tmd[1][CapOrientFlag-1];
				PreObj[2]=Tmd[2][3]-ds1*Tmd[2][CapOrientFlag-1];
			}
			else
			{
				PreObj[0]=Tmd[0][3]+ds1*Tmd[0][CapOrientFlag-4];
				PreObj[1]=Tmd[1][3]+ds1*Tmd[1][CapOrientFlag-4];
				PreObj[2]=Tmd[2][3]+ds1*Tmd[2][CapOrientFlag-4];
			}
			doc->PreObj[0]=PreObj[0];
			doc->PreObj[1]=PreObj[1];
			doc->PreObj[2]=PreObj[2];
			doc->AutoPlanFlag=true;

//		doc->AutoPlanFlag=true;

		UpdateData(FALSE);
	}	
	kn=m_time/t0;
/*	if(ControlMode==1)
	{
		PmacGetResponseA(PMacdevice,buf,255,"j/");
		PmacGetResponseA(PMacdevice,buf,255,"&1");
		PmacGetResponseA(PMacdevice,buf,255,"CLOSE");
		PmacGetResponseA(PMacdevice,buf,255,"#1->X");
		PmacGetResponseA(PMacdevice,buf,255,"OPEN PROG1");
		PmacGetResponseA(PMacdevice,buf,255,"CLEAR");
		PmacGetResponseA(PMacdevice,buf,255,"LINEAR");
		PmacGetResponseA(PMacdevice,buf,255,"ABS");
		PmacGetResponseA(PMacdevice,buf,255,"TA50");
		PmacGetResponseA(PMacdevice,buf,255,"TS0");
	}*/
	view->InvalidateRect(NULL, FALSE);
}


void CPathPlanDlg::OnButtonRun() 
{
	// TODO: Add your control notification handler code here
	double wcm[3]={0,0,0};

	
	if( Planradio==IDC_RADIO_LINEARPLAN)
	{
		LinearMotionplan(ini_ang, basiniPE, PEint, PEend, m_time, m_ts, No, 0, next_baspe, next_basvel, next_ang, next_angvel);

		for(int i=0;i<8;i++)
		{	
			ceta[0][i]=ini_ang[i];
			ceta[1][i]=next_ang[i];//����������
		 }
		SetTimer(0,100,NULL);

	}
  if( Planradio==IDC_RADIO_AUTOPLAN) 
	{
		CaptureCommand=AutoMotionPlan_line(ini_ang, basiniPE, GivenObj, wcm, VelocityLimit, CapOrientFlag, No+1,0,next_baspe, next_basvel, next_ang, next_angvel);
		for(int i=0;i<8;i++)
		{	
			ceta[0][i]=ini_ang[i];
			ceta[1][i]=next_ang[i];//����������
		 }
		SetTimer(1,100,NULL);
    }
	if (Planradio==IDC_RADIO_PROGRAMM)
	{
//		No=0;
//		numtime=0;
		UpdateData(false); 
		SetTimer(2,50,NULL);

	}

	
}

void CPathPlanDlg::OnRadioAutoplan() 
{
	// TODO: Add your control notification handler code here
	((CButton*)GetDlgItem(IDC_RADIO_AUTOPLAN))->SetCheck(BST_CHECKED);
    Planradio=IDC_RADIO_AUTOPLAN;
	pAutoPlanSetDlg->MoveWindow(350, 150, 330, 350);
	pAutoPlanSetDlg->ShowWindow(SW_SHOW);
	((CButton*)GetDlgItem(IDC_BUTTON_INIOK))->EnableWindow(true);
	
}

void CPathPlanDlg::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	CString str;
	CMainFrame *pframe;
	pframe=(CMainFrame*)::AfxGetApp()->GetMainWnd();
	int device=pframe->pSiderBar->pCtrlTab->pInitHardware->m_device;
	if(GetDlgItemText(IDC_BUTTON_STOP,str),str=="�� ͣ")
    {	
		if(Planradio==IDC_RADIO_AUTOPLAN)
		{
			KillTimer(1);
		}
		else if(Planradio==IDC_RADIO_LINEARPLAN)
		{
			KillTimer(0);
		}
		else
		{
			KillTimer(2);
		}
		if (ControlMode==1)
		{	
//			PmacSetIVariableDouble(0,122,0);
			PmacGetResponseA(PMacdevice,buf,255,"q");
			PmacGetResponseA(PMacdevice,buf,255,"k");
			for (int i=1;i<8;i++)
			{	
				PCube_setRampVel(device,i,1);
			}
		}
		SetDlgItemText(IDC_BUTTON_STOP,"�� ��");
	}
	else 
	{  
		if(Planradio==IDC_RADIO_AUTOPLAN)
		{
			SetTimer(1,100,NULL);
		}
		else if(Planradio==IDC_RADIO_LINEARPLAN)
		{
			SetTimer(0,100,NULL);
		}
		else
		{
			SetTimer(2,100,NULL);
		}
		if (ControlMode==1)
		{
//			PmacSetIVariableDouble(0,122,32);
			PmacGetResponseA(PMacdevice,buf,255,"&1 R");
			for (int i=1;i<8;i++)
			{
				PCube_setRampVel(device,i,2*PI/180);
			}
		}
		SetDlgItemText(IDC_BUTTON_STOP,"�� ͣ");}
	}


void CPathPlanDlg::OnRadioHandcontrol() 
{
	// TODO: Add your control notification handler code here
	((CButton*)GetDlgItem(IDC_RADIO_HANDCONTROL))->SetCheck(BST_CHECKED);
    Planradio=IDC_RADIO_HANDCONTROL;
	pHandControlDlg->MoveWindow(750, 150, 330, 410);
	pHandControlDlg->ShowWindow(SW_SHOW);
	((CButton*)GetDlgItem(IDC_BUTTON_INIOK))->EnableWindow(true);
}

void CPathPlanDlg::OnRadioSumu() 
{
	// TODO: Add your control notification handler code here
	ControlMode=0;
	
}

void CPathPlanDlg::OnRadioJxb() 
{
	// TODO: Add your control notification handler code here
	ControlMode=1;
	
}

void CPathPlanDlg::SendMessageToJXB()
{	
	CMainFrame *pframe;
	pframe=(CMainFrame*)::AfxGetApp()->GetMainWnd();
	int device=pframe->pSiderBar->pCtrlTab->pInitHardware->m_device;
	double send_ang[8];
	send_ang[0]=-next_ang[0];
	send_ang[1]=-next_ang[1];
	send_ang[2]=next_ang[2];
	send_ang[3]=-next_ang[3];
	send_ang[4]=next_ang[4];
	send_ang[5]=-next_ang[5];
	send_ang[6]=next_ang[6];
	send_ang[7]=-next_ang[7];
	for(int i=1;i<8;i++)
	{
		::PCube_moveRamp(device,
				i,
				send_ang[i],
				1*PI/180,
				1*PI/180);
			::PCube_moveStep(device,
				i,
				send_ang[i],
				4000);
	}
/////////////////////�������//////////////////////////////
//	VelCts=m_velocity*61440/270;
//	PosCts=m_position*61440/270;
/*	VelCts=20;
	PosCts=(360*30*CODEANGTRANS*send_ang[0])/(PI*DIAMETER);
	PmacSetIVariableDouble(0,122,VelCts);
	char PosStr[100];
	char outstr[256]="#1j=";  //�����˶�ָ��ȵ������
	_gcvt(PosCts,50,PosStr);
	strcat(outstr,PosStr);
	//	AfxMessageBox(outstr);
	PmacGetResponseA(PMacdevice,buf,255,outstr);    */ 

//	char strbita[50];
//	char outstr2[100]="X";
//	char stralpha[50];
//	char outstr1[100]="F";


/*	if (int(No/10)==No/10)
	{
		PosCts=(360*30*CODEANGTRANS*send_ang[0])/(PI*DIAMETER);
		_gcvt(PosCts,45,strbita);
		strcat(outstr2,strbita);
		//	VelCts=(360*30*CODEANGTRANS*100)/(PI*DIAMETER*1000);
		//	_gcvt(VelCts,45,stralpha);
		//	strcat(outstr1,stralpha);


		PmacGetResponseA(PMacdevice,buf,255,"OPEN ROT");
		PmacGetResponseA(PMacdevice,buf,255,"CLEAR");
		//	PmacGetResponseA(PMacdevice,buf,255,"LINEAR");
		//	PmacGetResponseA(PMacdevice,buf,255,outstr1);
		PmacGetResponseA(PMacdevice,buf,255,"F150000");
		PmacGetResponseA(PMacdevice,buf,255,outstr2);
		PmacGetResponseA(PMacdevice,buf,255,"CLOSE");
		PmacGetResponseA(PMacdevice,buf,255,"&1 R");
	}*/
	

/*	float p,v;
	PmacGetResponseA(PMacdevice,buf,255,"p");
	p=atof(buf);
	PmacGetResponseA(PMacdevice,buf,255,"v");
	v=atof(buf);
	while(abs(p-PosCts)>50||v!=0)
	{
			PmacGetResponseA(PMacdevice,buf,255,"p");
			p=atof(buf);
			PmacGetResponseA(PMacdevice,buf,255,"v");
			v=atof(buf);

			PmacGetResponseA(PMacdevice,buf,255,"?"); 
        	char b=buf[9];
			if(b=='C')
			{
				b=12;
			}
	        if(b&8)
			{

				PmacGetResponseA(PMacdevice,buf,255,"k");
				break;
			}

	}

			PmacGetResponseA(PMacdevice,buf,255,"k");*/
}

void CPathPlanDlg::OnButtonSavedata() 
{
	// TODO: Add your control notification handler code here
	int i;
	FILE *fp;
	CString filename; 
	CFileDialog dlg(false);
	if(dlg.DoModal()==IDOK) 
		filename=dlg.GetFileName();
	CMainFrame* frame=(CMainFrame*)AfxGetApp()->GetMainWnd();
	view=(CRobotControlView*)frame->GetActiveView();
	doc=view->GetDocument()->doc_delay; 
 //   doc->filename=filename; 

	fp=fopen(filename+"Ԥ��̹ؽڻ�������.txt","w");
	if(fp==NULL)	exit(1);
	else
	{
		fprintf(fp,"%d\n",kn);
		for(i=0; i<kn; i++)
			fprintf(fp,"%f %f %f %f %f %f %f %f\n",ceta[i][0],ceta[i][1],ceta[i][2],ceta[i][3],ceta[i][4],ceta[i][5],ceta[i][6],ceta[i][7]);
	}
	fclose(fp); 
	
}

void CPathPlanDlg::OnRadioProgramm() 
{
	// TODO: Add your control notification handler code here
	CString t1="NULL";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"txt File(*.txt)|*.txt||All Files (*.*)|*.*||",NULL);
	if(dlg.DoModal()==IDOK)
		t1=dlg.GetFileName();
	int i,j;  
    float theta[7];
	double PEI[6];
	//////////////////////////////////////////////
    FILE *inputfile;
	if(t1=="NULL") t1="NULLNAME.txt";
	inputfile=fopen(t1,"r");
	if(t1=="NULLNAME.txt")
	{	
		//exit(1);
		MessageBox("������һ���ļ���!");
		//		fclose(inputfile1); 
	}
	else
	{
		fscanf(inputfile,"%d\n",&kn);
		for(i=0; i<kn; i++)
		{
			fscanf(inputfile,"%f %f %f %f %f %f %f %f\n",&theta[0],&theta[1],&theta[2],&theta[3],&theta[4],&theta[5],&theta[6],&theta[7]);
			for(j=0; j<8; j++) 
			{
				ceta[i][j]=theta[j]; 
			}
		}
		fclose(inputfile); 
	}
	No=0;
	numtime=0;
	Planradio=IDC_RADIO_PROGRAMM;

}





