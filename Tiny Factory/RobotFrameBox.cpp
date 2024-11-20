#include "RobotFrameBox.h"
#include "Define.h"


IMPLEMENT_DYNAMIC(RobotFrameBox, CListBox)

BEGIN_MESSAGE_MAP(RobotFrameBox, CListBox)
    ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()



RobotFrameBox::RobotFrameBox() {
    m_backgroundColor = RGB(54, 57, 63); 
    m_textColor = RGB(255, 255, 255); 
}

RobotFrameBox::~RobotFrameBox() {

}


void RobotFrameBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) {
    if (lpDrawItemStruct->itemID == -1) return;

    CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

    BOOL isSelected = (lpDrawItemStruct->itemState & ODS_SELECTED);
    CBrush brush(isSelected ? RGB(100, 100, 100) : m_backgroundColor);
    pDC->FillRect(&lpDrawItemStruct->rcItem, &brush);

    pDC->SetTextColor(isSelected ? RGB(255, 255, 255) : m_textColor);
    pDC->SetBkMode(TRANSPARENT);

    CString itemText;
    GetText(lpDrawItemStruct->itemID, itemText);
    pDC->DrawText(itemText, &lpDrawItemStruct->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void RobotFrameBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	lpMeasureItemStruct->itemHeight = 60;
	lpMeasureItemStruct->itemWidth = 60;
}



void RobotFrameBox::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    BOOL selected = TRUE;
    int index = ItemFromPoint(point, selected);

    if (!selected && index != LB_ERR)
    {
        CString commandText;
        GetText(index, commandText);
        
        if (commandText == "")return;

        CString* pCommandText = new CString(commandText);

        GetParent()->PostMessage(ROBOT_FRAME_BOX_CURRENT_SEL_DBCLICK,0,reinterpret_cast<LPARAM>(pCommandText));
    }
    
    CListBox::OnLButtonDblClk(nFlags, point);
}
