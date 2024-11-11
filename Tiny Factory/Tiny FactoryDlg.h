
// Tiny FactoryDlg.h: 헤더 파일
//

#pragma once

#include "ConveyorBelt.h"
#include "opencv2/opencv.hpp"
#include "DataProcessSP.h"
#include "ObjectDetection.h"


// CTinyFactoryDlg 대화 상자
class CTinyFactoryDlg : public CDialogEx
{
// 생성입니다.
public:
	CTinyFactoryDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TINY_FACTORY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CListBox logListBox;

private:
	void Init();
	void SaveLogData();
	void DisplayCamera();
	void CameraLogic();

private:
	VideoCapture* capture;
	Mat matFrame;
	CImage imageMfc;
	ConveyorBeltSP* conveyorBeltSp;
	DataProcessSP* dataProcessSp;
	ObjectDetection* objectDetection;
	
	CButton startBtn;
	CStatic videoRect;
	CStatic detectionRect;

public:
	afx_msg void OnBnClickedBtn();
	afx_msg void OnDestroy();
	afx_msg void OnStopBtnClicked();
	afx_msg LRESULT OnConnectCompleteMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
