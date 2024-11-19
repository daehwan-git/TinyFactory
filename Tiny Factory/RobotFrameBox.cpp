#include "RobotFrameBox.h"


IMPLEMENT_DYNAMIC(RobotFrameBox, CListBox)

BEGIN_MESSAGE_MAP(RobotFrameBox, CListBox)
END_MESSAGE_MAP()



RobotFrameBox::RobotFrameBox() {
    m_backgroundColor = RGB(54, 57, 63); 
    m_textColor = RGB(0, 0, 0); 
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

