#pragma once
#include "SerialClass.h"
#include"pch.h"
#include "resource.h"

class ConvayorBeltSP
{
private:
	Serial* sp;
	CDialogEx* dialog;
	bool isRun = false;

public:
	ConvayorBeltSP(CString portNumber,CDialogEx* dialog):sp(nullptr),dialog(dialog)
	{
		if (portNumber == "" || sp != nullptr)
		{
			LogManager::GetInstance().WriteLog("포트의 번호가 유효하지 않음");
		}
		else
		{
			LogManager::GetInstance().WriteLog("컨베이어 벨트 : " + portNumber + " port 에 연결시도");

			this->sp = new Serial(PORT_PREFIX + portNumber);

			if (sp->IsConnected())
			{
				LogManager::GetInstance().WriteLog("컨베이어 벨트 : " + portNumber + " port에 연결 완료");
				dialog->PostMessageA(ON_CONNECT_COMPLETE_MESSAGE,0,0);
			}
			else {
				LogManager::GetInstance().WriteLog("컨베이어 벨트 : " + portNumber + " port에 연결 실패...");
			}
		}
	}

	void StopConvayorBelt();
	void StartConvayorBelt();
	void ReleaseConvayorBelt();
	bool IsRun() { return isRun; }
	
private:
	static UINT ConvayorBeltRun(LPVOID lpParam);
};

