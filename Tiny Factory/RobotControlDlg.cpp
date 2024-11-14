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
	DDX_Control(pDX, ROBOT_COMMAND_LISTBOX, robotCommandListBox);
	DDX_Control(pDX, IDC_A_MOTOR_SLIDER, aMotorSlider);
	DDX_Control(pDX, IDC_B_MOTOR_SLIDER, bMotorSlider);
	DDX_Control(pDX, IDC_C_MOTOR_SLIDER, cMotorSlider);
	DDX_Control(pDX, IDC_D_MOTOR_SLIDER, dMotorSlider);
}


BEGIN_MESSAGE_MAP(RobotControlDlg, CDialogEx)
	ON_BN_CLICKED(ROBOT_RECORD_BTN, &RobotControlDlg::OnBnClickedRecordBtn)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_A_MOTOR_SLIDER, &RobotControlDlg::OnNMReleasedcaptureAMotorSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_B_MOTOR_SLIDER, &RobotControlDlg::OnNMCustomdrawBMotorSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_C_MOTOR_SLIDER, &RobotControlDlg::OnNMCustomdrawCMotorSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_D_MOTOR_SLIDER, &RobotControlDlg::OnNMReleasedcaptureDMotorSlider)
	ON_BN_CLICKED(ROBOT_SEND_COMMAND_BTN, &RobotControlDlg::OnBnClickedSendCommandBtn)
	ON_WM_DESTROY()
	ON_BN_CLICKED(ROBOT_TEST_BTN, &RobotControlDlg::OnBnClickedTestBtn)
END_MESSAGE_MAP()




BOOL RobotControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	aMotorSlider.SetRange(AMOTOR_MIN_RANGE, AMOTOR_MAX_RANGE);
	bMotorSlider.SetRange(BMOTOR_MIN_RANGE, BMOTOR_MAX_RANGE);
	cMotorSlider.SetRange(CMOTOR_MIN_RANGE, CMOTOR_MAX_RANGE);
	dMotorSlider.SetRange(AMOTOR_MIN_RANGE, CMOTOR_MAX_RANGE);

	return TRUE;  
}

void RobotControlDlg::SetRobotArmSP(RobotArmSP* robotArmSP)
{
	this->robotArmSP = robotArmSP;
}


void RobotControlDlg::OnBnClickedRecordBtn()
{
	if(!isRecord)
	{
		isRecord = true;
		SetDlgItemText(ROBOT_RECORD_BTN,"녹화 종료");
		GetDlgItem(ROBOT_SEND_COMMAND_BTN)->EnableWindow(FALSE);
		GetDlgItem(ROBOT_TEST_BTN)->EnableWindow(FALSE);
	}
	else {
		isRecord = false;
		SetDlgItemText(ROBOT_RECORD_BTN, "녹화 시작");
		GetDlgItem(ROBOT_SEND_COMMAND_BTN)->EnableWindow(TRUE);
		GetDlgItem(ROBOT_TEST_BTN)->EnableWindow(TRUE);
	}

	ResetSliderPos();
}


void RobotControlDlg::AddCommand(CString command)
{
	robotCommandListBox.InsertString(-1,command);
}

void RobotControlDlg::ResetCommand()
{
	robotCommandListBox.ResetContent();
	this->currentCommand = "";
	ResetSliderPos();
}

void RobotControlDlg::ResetSliderPos()
{
	aMotorSlider.SetPos(ROBOT_ARM_MIN_RANGE);
	bMotorSlider.SetPos(ROBOT_ARM_MIN_RANGE);
	cMotorSlider.SetPos(ROBOT_ARM_MIN_RANGE);
	dMotorSlider.SetPos(ROBOT_ARM_MIN_RANGE);
}


void RobotControlDlg::OnNMReleasedcaptureAMotorSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (!isRecord)return;

	int pos = aMotorSlider.GetPos();
	CString sPos;
	sPos.Format("%d", pos);

	AddCommand(MOTOR_A + sPos);
	robotArmSP->SendCommand(MOTOR_A + sPos);
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


void RobotControlDlg::OnNMCustomdrawBMotorSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (!isRecord)return;

	int pos = bMotorSlider.GetPos();
	CString sPos;
	sPos.Format("%d", pos);

	AddCommand(MOTOR_B + sPos);
	robotArmSP->SendCommand(MOTOR_B + sPos);
	*pResult = 0;
}


void RobotControlDlg::OnNMCustomdrawCMotorSlider(NMHDR* pNMHDR, LRESULT* pResult)
{	
	if (!isRecord)return;

	int pos = cMotorSlider.GetPos();
	CString sPos;
	sPos.Format("%d", pos);

	AddCommand(MOTOR_C+ sPos);
	robotArmSP->SendCommand(MOTOR_C + sPos);

	*pResult = 0;
}


void RobotControlDlg::OnNMReleasedcaptureDMotorSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (!isRecord)return;

	int pos = dMotorSlider.GetPos();
	CString sPos;
	sPos.Format("%d", pos);

	AddCommand(MOTOR_D + sPos);
	robotArmSP->SendCommand(MOTOR_D + sPos);
	
	*pResult = 0;
}


void RobotControlDlg::OnBnClickedSendCommandBtn()
{
	if (!isRecord)
	{
		CString command = "";
		for (int i = 0; i < robotCommandListBox.GetCount(); i++)
		{
			CString item;
			robotCommandListBox.GetText(i,item);
			command += item + ":";
		}

		if(command != "")
			robotArmSP->SendCommandList(command);
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
