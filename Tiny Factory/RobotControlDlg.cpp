// RobotControlDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Tiny Factory.h"
#include "afxdialogex.h"
#include "RobotControlDlg.h"


// RobotControlDlg 대화 상자

IMPLEMENT_DYNAMIC(RobotControlDlg, CDialogEx)

RobotControlDlg::RobotControlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ROBOT_DLG, pParent)
{

}

RobotControlDlg::~RobotControlDlg()
{
}

void RobotControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ROBOT_COMMAND_LISTBOX, robotFrameBox);
	DDX_Control(pDX, IDC_A_MOTOR_SLIDER, aMotorSlider);
	DDX_Control(pDX, IDC_B_MOTOR_SLIDER, bMotorSlider);
	DDX_Control(pDX, IDC_C_MOTOR_SLIDER, cMotorSlider);
	DDX_Control(pDX, IDC_D_MOTOR_SLIDER, dMotorSlider);
	DDX_Control(pDX, IDC_SLIDER5, carriageCountSlider);
}


BEGIN_MESSAGE_MAP(RobotControlDlg, CDialogEx)
	ON_BN_CLICKED(ROBOT_RECORD_BTN, &RobotControlDlg::OnBnClickedAddFrame)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_A_MOTOR_SLIDER, &RobotControlDlg::OnNMReleasedcaptureAMotorSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_B_MOTOR_SLIDER, &RobotControlDlg::OnNMReleasedcaputreBMotorSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_C_MOTOR_SLIDER, &RobotControlDlg::OnNMReleasedCaptureCMotorSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_D_MOTOR_SLIDER, &RobotControlDlg::OnNMReleasedcaptureDMotorSlider)
	ON_BN_CLICKED(ROBOT_SEND_COMMAND_BTN, &RobotControlDlg::OnBnClickedSendCommandBtn)
	ON_WM_DESTROY()
	ON_BN_CLICKED(ROBOT_TEST_BTN, &RobotControlDlg::OnBnClickedTestBtn)
	ON_BN_CLICKED(ROBOT_ARM_STOP_BTN, &RobotControlDlg::OnBnClickedArmStopBtn)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER5, &RobotControlDlg::OnNMReleasedcaptureCarriageCount)
	ON_BN_CLICKED(DELETE_FRAME_BTN, &RobotControlDlg::OnBnClickedFrameBtn)
	ON_CONTROL_RANGE(BN_CLICKED,IDC_RADIO1,IDC_RADIO2, &RobotControlDlg::OnRangedRadioRightWrong)
	ON_MESSAGE(ROBOT_FRAME_BOX_CURRENT_SEL_DBCLICK, &RobotControlDlg::CurrentSelCommandDBClicked)
	ON_WM_PAINT()
END_MESSAGE_MAP()




BOOL RobotControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	aMotorSlider.SetRange(AMOTOR_MIN_RANGE, AMOTOR_MAX_RANGE);
	bMotorSlider.SetRange(BMOTOR_MIN_RANGE, BMOTOR_MAX_RANGE);
	cMotorSlider.SetRange(CMOTOR_MIN_RANGE, CMOTOR_MAX_RANGE);
	dMotorSlider.SetRange(AMOTOR_MIN_RANGE, CMOTOR_MAX_RANGE);
	carriageCountSlider.SetRange(0,MAX_CARRIAGE_COUNT);

	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);

	return TRUE;  
}

void RobotControlDlg::SetRobotArmSP(RobotArmSP* robotArmSP)
{
	this->robotArmSP = robotArmSP;
}

void RobotControlDlg::SetCarriage(Carriage* carriage)
{
	this->carriage = carriage;
	carriageCountSlider.SetPos(carriage->GetCarriageCount());
	this->carriage->WaitCarriage();
}


void RobotControlDlg::OnBnClickedAddFrame()
{
	int currentSel = robotFrameBox.GetCurSel();
	CString sPos;
	int pos = 0;

	if (currentSel < 0)currentSel = 0;
	
	if (aMotorMove)
	{
		pos = aMotorSlider.GetPos();
		sPos.Format("%s%d", MOTOR_A, pos);
		robotFrameBox.InsertString(currentSel,sPos);
	}
	if (bMotorMove)
	{
		pos = bMotorSlider.GetPos();
		sPos.Format("%s%d", MOTOR_B, pos);
		robotFrameBox.InsertString(currentSel, sPos);
	}
	if (cMotorMove)
	{
		pos =cMotorSlider.GetPos();
		sPos.Format("%s%d", MOTOR_C, pos);
		robotFrameBox.InsertString(currentSel, sPos);
	}
	if (dMotorMove)
	{
		pos = dMotorSlider.GetPos();
		sPos.Format("%s%d", MOTOR_D, pos);
		robotFrameBox.InsertString(currentSel, sPos);
	}
	ResetSliderPos();
}


void RobotControlDlg::AddCommand(CString command)
{
	robotFrameBox.InsertString(-1,command);
}

void RobotControlDlg::ResetCommand()
{
	robotFrameBox.ResetContent();
	this->currentCommand = "";
	ResetSliderPos();
}

void RobotControlDlg::ResetSliderPos()
{
	aMotorSlider.SetPos(ROBOT_ARM_MIN_RANGE);
	bMotorSlider.SetPos(ROBOT_ARM_MIN_RANGE);
	cMotorSlider.SetPos(ROBOT_ARM_MIN_RANGE);
	dMotorSlider.SetPos(ROBOT_ARM_MIN_RANGE);

	aMotorMove = false;
	bMotorMove = false;
	cMotorMove = false;
	dMotorMove = false;
}


void RobotControlDlg::OnNMReleasedcaptureAMotorSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	aMotorMove = true;

	*pResult = 0;
}


void RobotControlDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (robotArmSP != nullptr)
	{
		delete robotArmSP;
	}
}


void RobotControlDlg::OnNMReleasedcaputreBMotorSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	bMotorMove = true;
		 

	*pResult = 0;
}


void RobotControlDlg::OnNMReleasedCaptureCMotorSlider(NMHDR* pNMHDR, LRESULT* pResult)
{	
	cMotorMove = true;


	*pResult = 0;
}


void RobotControlDlg::OnNMReleasedcaptureDMotorSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	dMotorMove = true;

	
	*pResult = 0;
}


void RobotControlDlg::OnBnClickedSendCommandBtn()
{
	if (!isRecord)
	{
		CString command = "";
		for (int i = 0; i < robotFrameBox.GetCount(); i++)
		{
			CString item;
			robotFrameBox.GetText(i,item);
			command += item + ":";
		}

		if(command != "")
			robotArmSP->SendCommandList(command,rightOrWrong);
	}
}


void RobotControlDlg::OnBnClickedTestBtn()
{
	if (!isTest)
	{
		isTest = true;
		robotArmSP->SendCommand(ROBOTTEST + currentCommand);
	}
}


void RobotControlDlg::OnBnClickedArmStopBtn()
{
	robotFrameBox.ResetContent();
	robotArmSP->SendCommand(ROBOTSTOP);
}




void RobotControlDlg::OnNMReleasedcaptureCarriageCount(NMHDR* pNMHDR, LRESULT* pResult)
{
	int currentCount = carriageCountSlider.GetPos();
	carriage->SetCarriageCount(currentCount);
}


void RobotControlDlg::OnBnClickedFrameBtn()
{
	int currentSel = robotFrameBox.GetCurSel();

	if (currentSel != -1)
	{
		robotFrameBox.DeleteString(currentSel);
	}
}

void RobotControlDlg::OnRangedRadioRightWrong(UINT uid)
{
	switch (uid)
	{
	case IDC_RADIO1:
		rightOrWrong = true;
		break;
	case IDC_RADIO2:
		rightOrWrong = false;
		break;
	}
}


void RobotControlDlg::OnPaint()
{
	CPaintDC dc(this);

	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(&rect, BACKGROUND_BASE_COLOR);

}

LRESULT RobotControlDlg::CurrentSelCommandDBClicked(WPARAM wParam, LPARAM lParam)
{
	CString* currentSelCommand = reinterpret_cast<CString*>(lParam);

	if (currentSelCommand)
	{
		if (robotArmSP != nullptr)
		{
			robotArmSP->SendCommand(*currentSelCommand);
		}
	}

	delete currentSelCommand;

	return 0;
}
