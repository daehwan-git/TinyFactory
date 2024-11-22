#include "SplashScreen.h"
BEGIN_MESSAGE_MAP(SplashScreen, CWnd)
	ON_WM_TIMER()
ON_WM_PAINT()
END_MESSAGE_MAP()


SplashScreen* SplashScreen::splashScreen = nullptr;

void SplashScreen::ShowSplashScreen(CWnd* parentWnd)
{
	if (splashScreen == nullptr)
	{
		splashScreen = new SplashScreen();
		if (!splashScreen->Create(parentWnd))
		{
			delete splashScreen;
			splashScreen = nullptr;
		}
	}
}

void SplashScreen::HideSplashScreen()
{
	if (splashScreen != nullptr)
	{
		splashScreen->DestroyWindow();
	}
}

BOOL SplashScreen::Create(CWnd* parentWnd)
{
	if (!bitMap.LoadBitmap(SPLASH_LOGO))
		return FALSE;

	this->parentWnd = parentWnd;
	BITMAP bmp;
	bitMap.GetBitmap(&bmp);

	CRect rect(0, 0, bmp.bmWidth, bmp.bmHeight);
	if (!CreateEx(0, AfxRegisterWndClass(0), nullptr,
		WS_POPUP | WS_VISIBLE, rect, parentWnd, 0))
	{
		return FALSE;
	}

	CenterWindow();
	SetTimer(1, 3000, nullptr);
	return TRUE;
}

void SplashScreen::PostNcDestroy()
{
	delete splashScreen;
	splashScreen = nullptr;
}

void SplashScreen::OnTimer(UINT_PTR nIDEvent)
{
	HideSplashScreen();
}



void SplashScreen::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);

	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);

	CBitmap* oldBitMap = dcMem.SelectObject(&bitMap);
	dc.BitBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,SRCCOPY);
	dcMem.SelectObject(oldBitMap);

}
