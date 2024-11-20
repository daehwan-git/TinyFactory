#pragma once
#include "afxdialogex.h"
#include "RobotArmSP.h"
#include "ConveyorBelt.h"
#include "Carriage.h"
#include "RobotFrameBox.h"

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

private:
	void AddCommand(CString command);
	void ResetCommand();
	void ResetSliderPos();

	bool rightOrWrong = true;

	bool aMotorMove = false;
	bool bMotorMove = false;
	bool cMotorMove = false;
	bool dMotorMove = false;

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
	afx_msg void OnBnClickedFrameBtn();
	afx_msg void OnRangedRadioRightWrong(UINT uid);
	afx_msg void OnPaint();
};
