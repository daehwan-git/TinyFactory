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
	bool isTest = false;
	CString currentCommand = "";

	CListBox robotCommandListBox;
	CSliderCtrl aMotorSlider;
	CSliderCtrl bMotorSlider;
	CSliderCtrl cMotorSlider;
	CSliderCtrl dMotorSlider;

	RobotArmSP* robotArmSP;

private:
	void AddCommand(CString command);
	void ResetCommand();
	void ResetSliderPos();

public:
	virtual BOOL OnInitDialog();
	void SetRobotArmSP(RobotArmSP* robotArmSP);
	afx_msg void OnBnClickedRecordBtn();
	afx_msg void OnNMReleasedcaptureAMotorSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnNMReleasedcaputreBMotorSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawCMotorSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMReleasedcaptureDMotorSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedSendCommandBtn();
	afx_msg void OnBnClickedTestBtn();
	afx_msg void OnBnClickedArmStopBtn();
};
