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
public:
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};