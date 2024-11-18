#include "CustomBtn.h"


CustomBtn::CustomBtn()
{
	m_bgColor = RGB(114, 137, 218);
	m_textColor = RGB(255, 255, 255);
}

void CustomBtn::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	if (lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		m_bgColor = RGB(0, 0, 200);
	}
	else
	{
		m_bgColor = RGB(114, 137, 218);
	}

	CBrush brush(m_bgColor);
	pDC->FillRect(&lpDrawItemStruct->rcItem, &brush);

	pDC->SetTextColor(m_textColor);
	pDC->SetBkMode(TRANSPARENT);

	CString strText;
	GetWindowText(strText);

	pDC->DrawText(strText, &lpDrawItemStruct->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
