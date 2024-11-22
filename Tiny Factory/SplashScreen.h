#pragma once

#include "pch.h"

class SplashScreen : public CWnd
{
public:
	static void ShowSplashScreen(CWnd* parentWnd = nullptr);
	static void HideSplashScreen();

protected:
	BOOL Create(CWnd* parentWnd);
	void PostNcDestroy() override;

private:
	static SplashScreen* splashScreen;
	CWnd* parentWnd;
	CBitmap bitMap;

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
};

