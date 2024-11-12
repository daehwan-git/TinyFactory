
// Tiny FactoryDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Tiny Factory.h"
#include "Tiny FactoryDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "FileManager.h"

#include "opencv2/opencv.hpp"
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
	: CDialogEx(IDD_TINY_FACTORY_DIALOG, pParent),conveyorBeltSp(nullptr)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTinyFactoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, LOG_LIST_BOX, logListBox);
	DDX_Control(pDX, START_BTN, startBtn);
	DDX_Control(pDX, CAMERARECT, videoRect);
	DDX_Control(pDX, DERECTIONRECT, detectionRect);
}

BEGIN_MESSAGE_MAP(CTinyFactoryDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(START_BTN, &CTinyFactoryDlg::OnBnClickedBtn)
	ON_WM_DESTROY()
	ON_BN_CLICKED(STOP_BTN, &CTinyFactoryDlg::OnStopBtnClicked)
	ON_MESSAGE(ON_CONNECT_COMPLETE_MESSAGE, &CTinyFactoryDlg::OnConnectCompleteMessage)
	ON_WM_TIMER()
	ON_BN_CLICKED(ROBOTCONTROLBTN, &CTinyFactoryDlg::OnBnClickedRobotcontrolbtn)
END_MESSAGE_MAP()


// CTinyFactoryDlg 메시지 처리기

BOOL CTinyFactoryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
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
	LogManager::GetInstance().InitLogControl(&logListBox);

	if (!robotControlDlg.GetSafeHwnd()) {
		robotControlDlg.Create(IDD_ROBOT_DLG, this);
		robotControlDlg.CenterWindow();
	}

	DisplayCamera();
}

void CTinyFactoryDlg::SaveLogData()
{
	int itemCount = logListBox.GetCount(); // 리스트박스 항목 개수 가져오기

	std::vector<CString> data;

	for (int i = 0; i < itemCount; ++i)
	{
		CString text;
		logListBox.GetText(i,text);
		data.push_back(text);
	}


	FileManager::GetInstance().SaveFile(data);
}

void CTinyFactoryDlg::DisplayCamera()
{
	capture = new VideoCapture(0);

	if (!capture->isOpened())
	{
		LogManager::GetInstance().WriteLog("카메라를 연결할 수 없습니다.");
		return;
	}
	else
	{
		LogManager::GetInstance().WriteLog("카메라를 연결 성공");
	}


	if (objectDetection == nullptr)
	{
		objectDetection = new ObjectDetection(&detectionRect);
	}


	capture->set(CAP_PROP_FRAME_WIDTH, CAMERA_WIDTH);

	capture->set(CAP_PROP_FRAME_HEIGHT, CAMERA_HEIGHT);

	SetTimer(CAMERA_EVENT, 30, NULL);
}



void CTinyFactoryDlg::CameraLogic()
{
	capture->read(matFrame);


	if(objectDetection != nullptr)
		objectDetection->YoloDataFrame(matFrame);

#pragma region DrawCam

	int bpp = 8 * matFrame.elemSize();
	assert((bpp == 8 || bpp == 24 || bpp == 32));

	int padding = 0;

	if (bpp < 32)
		padding = 4 - (matFrame.cols % 4);

	if (padding == 4)
		padding = 0;

	int border = 0;

	if (bpp < 32)
	{
		border = 4 - (matFrame.cols % 4);
	}


	Mat mat_temp;
	if (border > 0 || matFrame.isContinuous() == false)
	{
		cv::copyMakeBorder(matFrame, mat_temp, 0, 0, 0, border, cv::BORDER_CONSTANT, 0);
	}
	else
	{
		mat_temp = matFrame;
	}

	//here


	RECT r;
	videoRect.GetClientRect(&r);
	cv::Size winSize(r.right, r.bottom);

	imageMfc.Create(winSize.width, winSize.height, 24);


	BITMAPINFO* bitInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));
	bitInfo->bmiHeader.biBitCount = bpp;
	bitInfo->bmiHeader.biWidth = mat_temp.cols;
	bitInfo->bmiHeader.biHeight = -mat_temp.rows;
	bitInfo->bmiHeader.biPlanes = 1;
	bitInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitInfo->bmiHeader.biCompression = BI_RGB;
	bitInfo->bmiHeader.biClrImportant = 0;
	bitInfo->bmiHeader.biClrUsed = 0;
	bitInfo->bmiHeader.biSizeImage = 0;
	bitInfo->bmiHeader.biXPelsPerMeter = 0;
	bitInfo->bmiHeader.biYPelsPerMeter = 0;


	if (mat_temp.cols == winSize.width && mat_temp.rows == winSize.height)
	{
		SetDIBitsToDevice(imageMfc.GetDC(),
			0, 0, winSize.width, winSize.height,
			0, 0, 0, mat_temp.rows,
			mat_temp.data, bitInfo, DIB_RGB_COLORS);
	}
	else
	{
		int destx = 0, desty = 0;
		int destw = winSize.width;
		int desth = winSize.height;

		int imgx = 0, imgy = 0;
		int imgWidth = mat_temp.cols - border;
		int imgHeight = mat_temp.rows;

		StretchDIBits(imageMfc.GetDC(),
			destx, desty, destw, desth,
			imgx, imgy, imgWidth, imgHeight,
			mat_temp.data, bitInfo, DIB_RGB_COLORS, SRCCOPY);
	}


	HDC dc = ::GetDC(videoRect.m_hWnd);
	imageMfc.BitBlt(dc, 0, 0);


	::ReleaseDC(videoRect.m_hWnd, dc);
	imageMfc.ReleaseDC();
	imageMfc.Destroy();
#pragma endregion
}


void CTinyFactoryDlg::OnBnClickedBtn()
{
	CString beltPort = "";
	GetDlgItemText(BELT_PORT, beltPort);

	if (conveyorBeltSp == nullptr)
	{
		conveyorBeltSp = new ConveyorBeltSP(beltPort, this);
		WorkManager::GetInstance().InitConvayorBeltSP(conveyorBeltSp);
	}

	conveyorBeltSp->StartConveyorBelt();

	CString dataPort = "";
	GetDlgItemText(DATAPORT, dataPort);

	if (dataProcessSp == nullptr)
	{
		dataProcessSp = new DataProcessSP(dataPort, this);
		WorkManager::GetInstance().InitDataProcessSP(dataProcessSp);
	}


	dataProcessSp->StartDataProcess();

	CString robotArmPort = "";
	GetDlgItemText(ROBOT_ARM_PORT, robotArmPort);

	RobotArmSP* robotArmSP = new RobotArmSP(robotArmPort, this);
	robotControlDlg.SetRobotArmSP(robotArmSP);
}


void CTinyFactoryDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (conveyorBeltSp != nullptr)
	{
		delete conveyorBeltSp;
	}

	if (dataProcessSp != nullptr)
	{
		delete dataProcessSp;
	}

	if (objectDetection != nullptr)
	{
		delete objectDetection;
	}

	if (robotControlDlg.GetSafeHwnd() != nullptr)
	{
		robotControlDlg.DestroyWindow();
	}

	SaveLogData();
}


void CTinyFactoryDlg::OnStopBtnClicked()
{
	if (conveyorBeltSp != nullptr)
	{
		conveyorBeltSp->StopConveyorBelt();
		GetDlgItem(START_BTN)->EnableWindow(TRUE);
		LogManager::GetInstance().WriteLog("공장을 정지합니다.");
	}
	conveyorBeltSp->StopConveyorBelt();
	GetDlgItem(START_BTN)->EnableWindow(TRUE);
	LogManager::GetInstance().WriteLog("공장을 정지합니다.");
}

LRESULT CTinyFactoryDlg::OnConnectCompleteMessage(WPARAM wParam, LPARAM lParam)
{
	GetDlgItem(START_BTN)->EnableWindow(FALSE);
	return 0;
}



void CTinyFactoryDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{
	case CAMERA_EVENT:
		CameraLogic();
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CTinyFactoryDlg::OnBnClickedRobotcontrolbtn()
{
	robotControlDlg.ShowWindow(SW_SHOW);
}
