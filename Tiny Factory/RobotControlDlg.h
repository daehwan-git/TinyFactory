#pragma once
#include "afxdialogex.h"
#include "RobotArmSP.h"


// RobotControlDlg 대화 상자

class RobotControlDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RobotControlDlg)

public:
	RobotControlDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~RobotControlDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ROBOT_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

private:
	bool isRecord = false;
	CString currentCommand = "";

	CListBox robotCommandListBox;
	CSliderCtrl aMotorSlider;
	CSliderCtrl bMotorSlider;
	CSliderCtrl cMotorSlider;
	CSliderCtrl dMotorSlider;

	RobotArmSP* robotArmSP;

public:
	virtual BOOL OnInitDialog();
	void SetRobotArmSP(RobotArmSP* robotArmSP);
};
