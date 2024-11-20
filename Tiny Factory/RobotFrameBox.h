#pragma once
#include <afxwin.h>


class RobotFrameBox : public CListBox {

    DECLARE_DYNAMIC(RobotFrameBox)


public:
    RobotFrameBox();
    virtual ~RobotFrameBox();

protected:
    DECLARE_MESSAGE_MAP()
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

private:
    COLORREF m_backgroundColor; 
    COLORREF m_textColor;       

    bool canMove = false;
    int selectedIndex;
    int hoveredIndex;
    CPoint startPoint;
    UINT_PTR timerID;

public:
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};