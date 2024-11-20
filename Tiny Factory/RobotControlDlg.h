#pragma once
#include "afxdialogex.h"
#include "RobotArmSP.h"
#include "ConveyorBelt.h"
#include "Carriage.h"
#include "RobotFrameBox.h"
#include "CustomBtn.h"

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
	bool isTest = false;
	CString currentCommand = "";

	CSliderCtrl aMotorSlider;
	CSliderCtrl bMotorSlider;
	CSliderCtrl cMotorSlider;
	CSliderCtrl dMotorSlider;

	RobotArmSP* robotArmSP;
	ConveyorBeltSP* conveyorBeltSP;
	Carriage* carriage;

	RobotFrameBox robotFrameBox;

	CustomBtn robotTestBtn;
	CustomBtn robotAddFrameBtn;
	CustomBtn robotDeleteFrameBtn;
	CustomBtn robotSendCommanBtn;
	CustomBtn robotStopBtn;
	CustomBtn carTestBtn;
	CustomBtn carStopBtn;

	CFont carBtnFont;
	CFont robotBtnFont;

	CBrush listBoxBrush;
	COLORREF listBoxTextColor;

private:
	void AddCommand(CString command);
	void ResetCommand();
	void ResetSliderPos();
	void CustomDlg();

	bool rightOrWrong = true;

	bool aMotorMove = false;
	bool bMotorMove = false;
	bool cMotorMove = false;
	bool dMotorMove = false;

	int robotDelay = 10;

public:
	virtual BOOL OnInitDialog();
	void SetRobotArmSP(RobotArmSP* robotArmSP);
	void SetCarriage(Carriage* carriage);
	afx_msg void OnBnClickedAddFrame();
	afx_msg void OnNMReleasedcaptureAMotorSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnNMReleasedcaputreBMotorSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMReleasedCaptureCMotorSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMReleasedcaptureDMotorSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedSendCommandBtn();
	afx_msg void OnBnClickedTestBtn();
	afx_msg void OnBnClickedArmStopBtn();
	CSliderCtrl carriageCountSlider;
	afx_msg void OnNMReleasedcaptureCarriageCount(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedFrameBtn();
	afx_msg void OnRangedRadioRightWrong(UINT uid);
	afx_msg void OnPaint();

	afx_msg LRESULT CurrentSelCommandDBClicked(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
