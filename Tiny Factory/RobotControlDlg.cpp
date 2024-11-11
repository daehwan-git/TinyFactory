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
