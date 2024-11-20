#include "RobotFrameBox.h"
#include "Define.h"


IMPLEMENT_DYNAMIC(RobotFrameBox, CListBox)

BEGIN_MESSAGE_MAP(RobotFrameBox, CListBox)
    ON_WM_LBUTTONDBLCLK()
    ON_WM_LBUTTONDOWN()
    ON_WM_TIMER()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



RobotFrameBox::RobotFrameBox() {
    m_backgroundColor = RGB(132,137,39);
    m_textColor = RGB(255, 255, 255); 
}

RobotFrameBox::~RobotFrameBox() {
    if (timerID != 0)
        KillTimer(timerID);
}


void RobotFrameBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) {
    if (lpDrawItemStruct->itemID == -1) return;

    CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

    BOOL isSelected = (lpDrawItemStruct->itemState & ODS_SELECTED);
    CBrush brush(isSelected ? RGB(100, 100, 100) : m_backgroundColor);

    CRect itemRect;
    GetItemRect(lpDrawItemStruct->itemID,itemRect);
    itemRect.top -= 1;
    itemRect.bottom -= 1;
    itemRect.right -= 1;
    itemRect.left -= 1;
    pDC->SetDCPenColor(RGB(0,0,0));
    pDC->Rectangle(itemRect);

    pDC->FillRect(&lpDrawItemStruct->rcItem, &brush);

    pDC->SetTextColor(isSelected ? RGB(255, 255, 255) : m_textColor);
    pDC->SetBkMode(TRANSPARENT);


    CString itemText;
    GetText(lpDrawItemStruct->itemID, itemText);
    pDC->DrawText(itemText, &lpDrawItemStruct->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void RobotFrameBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	lpMeasureItemStruct->itemHeight = 1000;
	lpMeasureItemStruct->itemWidth = 60;
}



void RobotFrameBox::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    if (canMove)
    {
        canMove = false;
        if (timerID != 0)
        {
            KillTimer(timerID);
            timerID = 0;
        }
    }
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


void RobotFrameBox::OnLButtonDown(UINT nFlags, CPoint point)
{
    BOOL selected = FALSE;
    selectedIndex = ItemFromPoint(point, selected);

    if (selectedIndex != LB_ERR)
    {
        startPoint = point;
        timerID = SetTimer(1, 500, NULL);
    }
    
    CListBox::OnLButtonDown(nFlags, point);
}


void RobotFrameBox::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == 1 && selectedIndex != LB_ERR)
    {
        canMove = true;
        KillTimer(timerID);
        timerID = 0;

        SetCapture();
        ::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HAND));
    }
    
    CListBox::OnTimer(nIDEvent);
}


void RobotFrameBox::OnLButtonUp(UINT nFlags, CPoint point)
{
    if (canMove)
    {
        ReleaseCapture();
        canMove = false;

        BOOL selected = FALSE;
        hoveredIndex = ItemFromPoint(point, selected);

        if (hoveredIndex != LB_ERR &&
            hoveredIndex != selectedIndex)
        {
            CString dragItem, targetItem;
            GetText(selectedIndex, dragItem);
            GetText(hoveredIndex, targetItem);

            DeleteString(selectedIndex);
            InsertString(selectedIndex, targetItem);

            DeleteString(hoveredIndex);
            InsertString(hoveredIndex, dragItem);

            SetCurSel(hoveredIndex);
        }
    }

    if (timerID != 0)
    {
        KillTimer(timerID);
        timerID = 0;
    }

    Invalidate(TRUE);

    CListBox::OnLButtonUp(nFlags, point);
}


void RobotFrameBox::OnMouseMove(UINT nFlags, CPoint point)
{
    if(canMove)
    {
        CRect clientRect;
        GetClientRect(&clientRect);

        if (!clientRect.PtInRect(point))
        {
            canMove = false;
            ReleaseCapture();
            return;
        }

        CDC memDC;
        CClientDC dc(this);
        memDC.CreateCompatibleDC(&dc);

        CBitmap memBitmap;
        memBitmap.CreateCompatibleBitmap(&dc, clientRect.Width(), clientRect.Height()); 
        CBitmap* pOldBitmap = memDC.SelectObject(&memBitmap);

        memDC.FillSolidRect(&clientRect, WHITE_COLOR);

        CRect itemRect;
        CString itemText;
        GetItemRect(selectedIndex, itemRect);
        GetText(selectedIndex, itemText);
        itemRect.MoveToXY(point);

        memDC.FillSolidRect(itemRect, m_backgroundColor);  
        memDC.SetBkMode(TRANSPARENT); 
        memDC.SetTextColor(m_textColor);
        memDC.DrawText(itemText, &itemRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE); // 텍스트 그리기

 
        dc.BitBlt(0, 0, clientRect.Width(), clientRect.Height(), &memDC, 0, 0, SRCCOPY);

        memDC.SelectObject(pOldBitmap); 
        memBitmap.DeleteObject(); 

        Invalidate(FALSE);
    }
    CListBox::OnMouseMove(nFlags, point);
}
