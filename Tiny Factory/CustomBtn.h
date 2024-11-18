#pragma once

#include <afxwin.h>

class CustomBtn : public CButton
{
public:
	CustomBtn();

protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

private:
	COLORREF m_textColor;
	COLORREF m_bgColor;
};

