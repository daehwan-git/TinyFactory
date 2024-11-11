#pragma once

#include "pch.h"
#include "SerialClass.h"

class DataProcessSP
{
private:
	CDialogEx* dialog;
	Serial* sp;
	bool isRun = false;


public:
	DataProcessSP(CString portNumber, CDialogEx* dialog):sp(nullptr),dialog(dialog)
	{
		if (portNumber == "")
		{
			LogManager::GetInstance().WriteLog("데이터 포트의 번호가 유효하지 않음");
		}
		else
		{
			LogManager::GetInstance().WriteLog("데이터 : " + portNumber + " port 에 연결시도");

			this->sp = new Serial(PORT_PREFIX + portNumber);

			if (sp->IsConnected())
			{
				LogManager::GetInstance().WriteLog("데이터 : " + portNumber + " port에 연결 완료");
			}
			else {
				LogManager::GetInstance().WriteLog("데이터 : " + portNumber + " port에 연결 실패...");
			}
		}
	}

	~DataProcessSP()
	{
		StopDataProcess();
		ReleaseDataProcess();
	}

	void StartDataProcess();
	void StopDataProcess();
	bool IsRun() { return isRun; }
	void ParsingData(CString& data);

private:
	void ReleaseDataProcess();
	static UINT DataProcessThread(LPVOID lpParam);
};

