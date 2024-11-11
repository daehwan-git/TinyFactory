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
END_MESSAGE_MAP()




BOOL RobotControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	aMotorSlider.SetRange(ROBOT_ARM_MIN_RANGE,ROBOT_ARM_MAX_RANGE);
	bMotorSlider.SetRange(ROBOT_ARM_MIN_RANGE,ROBOT_ARM_MAX_RANGE);
	cMotorSlider.SetRange(ROBOT_ARM_MIN_RANGE,ROBOT_ARM_MAX_RANGE);
	dMotorSlider.SetRange(ROBOT_ARM_MIN_RANGE,ROBOT_ARM_MAX_RANGE);

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
	}
	else {
		isRecord = false;
		SetDlgItemText(ROBOT_RECORD_BTN, "녹화 시작");
		ResetCommand();
	}
}


void RobotControlDlg::AddCommand(CString command)
{
	this->currentCommand += command + ":";
	robotCommandListBox.ResetContent();
	robotCommandListBox.AddString(this->currentCommand);
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
	*pResult = 0;
}
