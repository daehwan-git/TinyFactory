#pragma once
#include "SerialClass.h"
#include"pch.h"
#include "resource.h"

class ConveyorBeltSP
{
private:
	const CString OBJECT_DETECTION = "OBJECTDETECTION";

	Serial* sp = nullptr;
	CDialogEx* dialog = nullptr;
	bool isRun = false;

	CWinThread* conveyorBeltThread = nullptr;

public:

	enum Status{
		ON,
		OFF,
	};

	bool InitConveyorBeltSP(CString portNumber,CDialogEx* dialog)
	{
		if (portNumber == "")
		{
			LogManager::GetInstance()->WriteLog("컨베이어 벨트 포트의 번호가 유효하지 않음");
		}
		else
		{
			LogManager::GetInstance()->WriteLog("컨베이어 벨트 : " + portNumber + " port 에 연결시도");

			this->sp = new Serial(PORT_PREFIX + portNumber,115200);

			if (sp->IsConnected())
			{
				this->dialog = dialog;
				LogManager::GetInstance()->WriteLog("컨베이어 벨트 : " + portNumber + " port에 연결 완료");
				StartConveyorBelt();
				return true;
			}
			else {
				LogManager::GetInstance()->WriteLog("컨베이어 벨트 : " + portNumber + " port에 연결 실패...");
			}
		}
		
		return false;

	}

	~ConveyorBeltSP()
	{
		StopConveyorBelt();
		ReleaseConveyorBelt();
	}

	void StopConveyorBelt();
	void StartConveyorBelt();
	bool IsRun() { return isRun; }
	void KnockDown();
	void ResetDetect();
	void ResetGoal();
	
private:
	void ParsingReciveData(CString data);
	void ReleaseConveyorBelt();
	static UINT ConvayorBeltRun(LPVOID lpParam);
};

