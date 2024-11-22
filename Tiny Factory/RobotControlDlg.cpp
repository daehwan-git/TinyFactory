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

	DDX_Control(pDX, ROBOT_TEST_BTN, robotTestBtn);
	DDX_Control(pDX, ROBOT_ADD_FRAME_BTN, robotAddFrameBtn);
	DDX_Control(pDX, ROBOT_DELETE_FRAME_BTN, robotDeleteFrameBtn);
	DDX_Control(pDX, ROBOT_SEND_COMMAND_BTN, robotSendCommanBtn);
	DDX_Control(pDX, ROBOT_ARM_STOP_BTN, robotStopBtn);
	DDX_Control(pDX, IDC_BUTTON4, carTestBtn);
	DDX_Control(pDX, IDC_BUTTON5, carStopBtn);

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
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, &RobotControlDlg::OnDeltaposSpin2)
	ON_MESSAGE(ROBOT_FRAME_BOX_CURRENT_SEL_DBCLICK, &RobotControlDlg::CurrentSelCommandDBClicked)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_A_MOTOR_SLIDER, &RobotControlDlg::OnNMCustomdrawSlider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_B_MOTOR_SLIDER, &RobotControlDlg::OnNMCustomdrawSlider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_C_MOTOR_SLIDER, &RobotControlDlg::OnNMCustomdrawSlider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_D_MOTOR_SLIDER, &RobotControlDlg::OnNMCustomdrawSlider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER5, &RobotControlDlg::OnNMCustomdrawSlider)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(ROBOT_DELAY_BTN, &RobotControlDlg::OnBnClickedDelayBtn)
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
	
	robotFrameBox.SetColumnWidth(100);
	robotFrameBox.SetHorizontalExtent(200);
	
	SetDlgItemInt(ROBOT_DELAY_EDIT, robotDelay);

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

	CRect rect;
	robotFrameBox.GetClientRect(&rect);
	robotFrameBox.SetItemHeight(currentSel, rect.Height());
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

void RobotControlDlg::CustomDlg()
{
	carBtnFont.CreateFont(BASIC_FONT);
	robotBtnFont.CreateFont(BASIC_FONT);

	if (carTestBtn)
	{
		carTestBtn.SetFont(&carBtnFont);
	}
	if (carStopBtn)
	{
		carStopBtn.SetFont(&carBtnFont);
	}
	if (robotTestBtn)
	{
		robotTestBtn.SetFont(&robotBtnFont);
	}
	if (robotAddFrameBtn)
	{
		robotAddFrameBtn.SetFont(&robotBtnFont);
	}
	if (robotDeleteFrameBtn)
	{
		robotDeleteFrameBtn.SetFont(&robotBtnFont);
	}
	if (robotSendCommanBtn)
	{
		robotSendCommanBtn.SetFont(&robotBtnFont);
	}
	if (robotStopBtn)
	{
		robotStopBtn.SetFont(&robotBtnFont);
	}

	listBoxBrush.CreateSolidBrush(BACKGROUND_BASE_COLOR);
	listBoxTextColor = WHITE_COLOR;
}


void RobotControlDlg::OnNMReleasedcaptureAMotorSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	aMotorMove = true;

	*pResult = 0;
}


void RobotControlDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	carBtnFont.DeleteObject();
	robotBtnFont.DeleteObject();
	listBoxBrush.DeleteObject();

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
	CString command = "";
	for (int i = 0; i < robotFrameBox.GetCount(); i++)
	{
		CString item;
		robotFrameBox.GetText(i, item);
		command += item + ":";
	}

	if (command != "")
		robotArmSP->SendCommand(ROBOTTEST + command);
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

void RobotControlDlg::OnNMCustomdrawSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	switch (pNMCD->dwDrawStage)
	{
	case CDDS_PREPAINT:
	{
		CDC* pDC = CDC::FromHandle(pNMCD->hdc);

		CRect rc;
		::GetClientRect(pNMCD->hdr.hwndFrom, &rc);
		pDC->FillSolidRect(&rc, RGB(54, 57, 63));

		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	break;

	case CDDS_ITEMPREPAINT:
	{
		CDC* pDC = CDC::FromHandle(pNMCD->hdc);

		if (pNMCD->dwItemSpec == TBCD_CHANNEL)
		{
			CRect rc;
			rc.CopyRect(&pNMCD->rc);
			pDC->FillSolidRect(&rc, RGB(70, 70, 70));
		}
		else if (pNMCD->dwItemSpec == TBCD_THUMB)
		{
			CRect rcThumb(pNMCD->rc);
			pDC->FillSolidRect(&rcThumb, RGB(150, 150, 150));
		}
	}

	*pResult = CDRF_SKIPDEFAULT;
	break;

	default:
		*pResult = 0;
		break;
	}
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


void RobotControlDlg::OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	if (pNMUpDown->iDelta < 0)
	{
		robotDelay += 10;
	}
	else {
		robotDelay -= 10;
	}

	SetDlgItemInt(ROBOT_DELAY_EDIT,robotDelay);
	
	*pResult = 0;
}


HBRUSH RobotControlDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_STATIC)
	{
		pDC->SetTextColor(WHITE_COLOR);

		pDC->SetBkMode(TRANSPARENT);
	}
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(WHITE_COLOR);

		pDC->SetBkMode(TRANSPARENT);

		pDC->SelectObject(&carBtnFont);
	}
	if (nCtlColor == CTLCOLOR_LISTBOX)
	{
		pDC->SetTextColor(listBoxTextColor);

		pDC->SetBkMode(OPAQUE);

		pDC->SetBkColor(BACKGROUND_BASE_COLOR);

		return listBoxBrush;
	}

	static HBRUSH hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	return hbr, hbrBackground;
}


void RobotControlDlg::OnBnClickedDelayBtn()
{
	if (robotArmSP != nullptr)
	{
		CString delay;
		delay.Format("%s%d",ROBOTDELAY,robotDelay);
		robotArmSP->SendCommand(delay);
	}
}
