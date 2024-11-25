
// Tiny FactoryDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Tiny Factory.h"
#include "Tiny FactoryDlg.h"
#include "afxdialogex.h"
#include "Device.h"
#include <dbt.h>
#include "Carriage.h"
#include "FileManager.h"
#include "SplashScreen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "opencv2/opencv.hpp"
#include "DataManager.h"
using namespace cv;




// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTinyFactoryDlg 대화 상자



CTinyFactoryDlg::CTinyFactoryDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TINY_FACTORY_DIALOG, pParent), conveyorBeltSp(nullptr)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTinyFactoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, LOG_LIST_BOX, logListBox);
	DDX_Control(pDX, CAMERARECT, videoRect);
	DDX_Control(pDX, DERECTIONRECT, detectionRect);
	DDX_Control(pDX, STOP_BTN, stopBtn);
	DDX_Control(pDX, START_BTN, startBtn);
	DDX_Control(pDX, ROBOTCONTROLBTN, robotcontrolBtn);
}

BEGIN_MESSAGE_MAP(CTinyFactoryDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(START_BTN, &CTinyFactoryDlg::OnBnClickedStartBtn)
	ON_WM_DESTROY()
	ON_BN_CLICKED(STOP_BTN, &CTinyFactoryDlg::OnStopBtnClicked)
	ON_MESSAGE(ON_CONNECT_COMPLETE_MESSAGE, &CTinyFactoryDlg::OnConnectCompleteMessage)
	ON_MESSAGE(NORMAL_OBJECT_INC, &CTinyFactoryDlg::OnNormalObjectInc)
	ON_MESSAGE(WRONG_OBJECT_INC, &CTinyFactoryDlg::OnWrongObjectInc)
	ON_MESSAGE(DETECTIONFINISH, &CTinyFactoryDlg::OnDectionFinish)
	ON_MESSAGE(LOG_WRITE, &CTinyFactoryDlg::OnLogWrite)
	ON_MESSAGE(CONVEYORBELT_CONDITION_CHANGED, &CTinyFactoryDlg::OnConveyorBeltConditionChanged)
	ON_MESSAGE(ROBOTARM_CONDITION_CHANGED, &CTinyFactoryDlg::OnRobotArmConditionChanged)
	ON_WM_DEVICECHANGE()
	ON_BN_CLICKED(ROBOTCONTROLBTN, &CTinyFactoryDlg::OnBnClickedRobotcontrolbtn)
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_CTLCOLOR()
	ON_WM_ACTIVATE()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CTinyFactoryDlg 메시지 처리기

BOOL CTinyFactoryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ModifyStyle(WS_SIZEBOX, 0);

	btnFont.CreateFont(BASIC_FONT);
	stcFont.CreateFont(BASIC_FONT);

	listBoxBrush.CreateSolidBrush(BACKGROUND_BASE_COLOR);
	listBoxTextColor = WHITE_COLOR;

	comboBoxBrush.CreateSolidBrush(DARK_GRAY);
	comboBoxTextColor = WHITE_COLOR;

	if (startBtn)
	{
		startBtn.SetFont(&btnFont);
	}

	if (stopBtn)
	{
		stopBtn.SetFont(&btnFont);
	}

	if (robotcontrolBtn)
	{
		robotcontrolBtn.SetFont(&btnFont);
	}

	Init();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTinyFactoryDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTinyFactoryDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);

		CRect rect;
		GetClientRect(&rect);
		dc.FillSolidRect(&rect, BACKGROUND_BASE_COLOR);

		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTinyFactoryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CTinyFactoryDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	return;
}

void CTinyFactoryDlg::Init()
{
	InitDevicePort();

	LogManager::GetInstance()->InitLogControl(this);

	if (!robotControlDlg.GetSafeHwnd()) {
		robotControlDlg.Create(IDD_ROBOT_DLG, this);
		robotControlDlg.CenterWindow();
	}

	if (camera == nullptr)
	{
		camera = new Camera(&videoRect, &detectionRect, 0);
	}

	WorkManager::GetInstance()->SetMainHandle(m_hWnd);
	WorkManager::GetInstance()->InitObjectDetection(camera->GetObjectDetection());
	DataManager::GetInstance()->SetMainHandle(m_hWnd);
}


void CTinyFactoryDlg::InitDevicePort()
{
	std::vector<CString> portNames = Device::ListUsbPorts();
	CComboBox* beltComboBox = (CComboBox*)GetDlgItem(CONVEYORPORT);
	CComboBox* robotComboBox = (CComboBox*)GetDlgItem(ROBOTPORT);

	beltComboBox->ResetContent();
	robotComboBox->ResetContent();

	for (int i = 0; i < portNames.size(); i++)
	{
		beltComboBox->AddString(portNames[i]);
		robotComboBox->AddString(portNames[i]);
	}

}

void CTinyFactoryDlg::SaveLogData()
{
	int itemCount = logListBox.GetCount(); // 리스트박스 항목 개수 가져오기

	std::vector<CString> data;

	for (int i = 0; i < itemCount; ++i)
	{
		CString text;
		logListBox.GetText(i, text);
		data.push_back(text);
	}


	FileManager::GetInstance()->SaveFile(data);

}


void CTinyFactoryDlg::UpdateControl(CONTROLID controlID)
{
	CRect countRect;
	GetDlgItem(controlID)->GetWindowRect(&countRect);
	ScreenToClient(&countRect);

	InvalidateRect(&countRect, TRUE);
}

void CTinyFactoryDlg::OnBnClickedStartBtn()
{
	if (!isInit)
	{
		CString beltPort = "";
		GetDlgItemText(CONVEYORPORT, beltPort);

		CString robotArmPort = "";
		GetDlgItemText(ROBOTPORT, robotArmPort);


		CString carriageIP = "";
		GetDlgItemText(CARRIAGE_IP, carriageIP);

#ifndef _DEBUG
		if (beltPort == "" || robotArmPort == "" || carriageIP == "")
		{
			AfxMessageBox("포트가 유효하지 않음");
			return;
		}
#endif

		conveyorBeltSp = new ConveyorBeltSP();
		if (conveyorBeltSp->InitConveyorBeltSP(beltPort, this))
		{
			WorkManager::GetInstance()->InitConvayorBeltSP(conveyorBeltSp);
		}
		else delete conveyorBeltSp;


		RobotArmSP* robotArmSP = new RobotArmSP();
		if (robotArmSP->InitRobotArmSP(robotArmPort, this))
		{
			robotControlDlg.SetRobotArmSP(robotArmSP);
			WorkManager::GetInstance()->InitRobotArmSP(robotArmSP);
		}
		else delete robotArmSP;
		

		Carriage* carriage = new Carriage();
		if (carriage->InitCarriage(carriageIP))
		{
			WorkManager::GetInstance()->InitCarriage(carriage);
			robotControlDlg.SetCarriage(carriage);
		}
		else delete carriage;

		GetDlgItem(CONVEYORPORT)->EnableWindow(FALSE);
		GetDlgItem(CARRIAGE_IP)->EnableWindow(FALSE);
		GetDlgItem(ROBOTPORT)->EnableWindow(FALSE);

		isRun = true;
		isInit = true;
	}
	else {
		if (!isRun)
		{
			LogManager::GetInstance()->WriteLog("공장 재가동");
			conveyorBeltSp->StartConveyorBelt();
			isRun = true;
		}
	}
}


void CTinyFactoryDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (conveyorBeltSp != nullptr)
	{
		delete conveyorBeltSp;
	}


	if (robotControlDlg.GetSafeHwnd() != nullptr)
	{
		robotControlDlg.DestroyWindow();
	}

	if (camera != nullptr)
	{
		delete camera;
	}

	btnFont.DeleteObject();
	stcFont.DeleteObject();

	SaveLogData();
}


void CTinyFactoryDlg::OnStopBtnClicked()
{
	if (isRun)
	{
		if (conveyorBeltSp != nullptr)
		{
			conveyorBeltSp->StopConveyorBelt();
			GetDlgItem(START_BTN)->EnableWindow(TRUE);
			LogManager::GetInstance()->WriteLog("공장을 정지합니다.");
			isRun = false;
		}
	}
}

LRESULT CTinyFactoryDlg::OnConnectCompleteMessage(WPARAM wParam, LPARAM lParam)
{
	GetDlgItem(START_BTN)->EnableWindow(FALSE);
	return 0;
}

LRESULT CTinyFactoryDlg::OnDectionFinish(WPARAM wParam, LPARAM lParam)
{
	SetTimer(DETECTION_RESET, DETECTIONWAITTIME, NULL);
	return LRESULT();
}


LRESULT CTinyFactoryDlg::OnNormalObjectInc(WPARAM wParam, LPARAM lParam)
{
	int normalCount = static_cast<int>(wParam);

	CString intToStr;
	intToStr.Format("%d개", normalCount);

	SetDlgItemText(NORMAL_COUNT_TEXT, intToStr);
	
	UpdateControl(NORMAL_COUNT_TEXT);

	return LRESULT();
}

LRESULT CTinyFactoryDlg::OnWrongObjectInc(WPARAM wParam, LPARAM lParam)
{
	int wrongCount = static_cast<int>(wParam);
	CString intToStr;
	intToStr.Format("%d개", wrongCount);

	SetDlgItemText(WRONG_COUNT_TEXT, intToStr);

	UpdateControl(WRONG_COUNT_TEXT);

	return LRESULT();
}

LRESULT CTinyFactoryDlg::OnLogWrite(WPARAM wParam, LPARAM lParam)
{

	CString* data = reinterpret_cast<CString*>(lParam);
	
	logListBox.InsertString(-1, *data);

	delete data;

	return LRESULT();
}

LRESULT CTinyFactoryDlg::OnConveyorBeltConditionChanged(WPARAM wParam, LPARAM lParam)
{

	ConveyorBeltSP::Status currentStatus = (ConveyorBeltSP::Status)(wParam);

	if (ConveyorBeltSP::Status::ON == currentStatus)
	{
		SetDlgItemText(CONVEYOR_CONDITION_TEXT, "작동 중");
	}
	else if (ConveyorBeltSP::Status::OFF == currentStatus)
	{
		SetDlgItemText(CONVEYOR_CONDITION_TEXT, "정지");
	}

	UpdateControl(CONVEYOR_CONDITION_TEXT);

	return LRESULT();
}

LRESULT CTinyFactoryDlg::OnRobotArmConditionChanged(WPARAM wParam, LPARAM lParam)
{
	RobotArmSP::Status currentStatus = (RobotArmSP::Status)(wParam);
	if (RobotArmSP::Status::PLAYING == currentStatus)
	{
		SetDlgItemText(ROBOTARM_CONDITION_TEXT, "작동 중");
	}
	else if (RobotArmSP::Status::WAIT == currentStatus)
	{
		SetDlgItemText(ROBOTARM_CONDITION_TEXT, "대기 중");
	}

	UpdateControl(ROBOTARM_CONDITION_TEXT);

	return LRESULT();
}



void CTinyFactoryDlg::OnBnClickedRobotcontrolbtn()
{
	//if(isRun)
	robotControlDlg.ShowWindow(SW_SHOW);
}



void CTinyFactoryDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == DETECTION_RESET)
	{
		KillTimer(DETECTION_RESET);
		WorkManager::GetInstance()->ResetDetection();
	}
	else if (nIDEvent == ROBOT_TIMER)
	{
		KillTimer(ROBOT_TIMER);
		WorkManager::GetInstance()->ResetIsPlaying();
	}

	CDialogEx::OnTimer(nIDEvent);
}




BOOL CTinyFactoryDlg::OnDeviceChange(UINT nEventType, DWORD_PTR dwData)
{
	InitDevicePort();
	return 0;
}



void CTinyFactoryDlg::OnSize(UINT nType, int cx, int cy)
{

	CDialogEx::OnSize(nType, cx, cy);

}


void CTinyFactoryDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}
	


HBRUSH CTinyFactoryDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);


	if (pWnd->GetDlgCtrlID() == IDC_STATIC)
	{
		pDC->SetTextColor(WHITE_COLOR);

		pDC->SetBkMode(TRANSPARENT);
	}
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(WHITE_COLOR);

		pDC->SetBkMode(TRANSPARENT);

		pDC->SelectObject(&stcFont);
	}
	if (nCtlColor == CTLCOLOR_LISTBOX)
	{
		pDC->SetTextColor(listBoxTextColor);

		pDC->SetBkMode(OPAQUE);

		pDC->SetBkColor(BACKGROUND_BASE_COLOR);

		return listBoxBrush;
	}
	if (nCtlColor == CTLCOLOR_EDIT || nCtlColor == CTLCOLOR_LISTBOX)
	{
		pDC->SetTextColor(comboBoxTextColor);

		pDC->SetBkMode(OPAQUE);

		pDC->SetBkColor(DARK_GRAY);

		return comboBoxBrush;
	}

	static HBRUSH hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	return hbr, hbrBackground;
}




void CTinyFactoryDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


int CTinyFactoryDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	SplashScreen::ShowSplashScreen(this);

	return 0;
}
