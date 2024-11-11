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
}


BEGIN_MESSAGE_MAP(RobotControlDlg, CDialogEx)
END_MESSAGE_MAP()


// RobotControlDlg 메시지 처리기
