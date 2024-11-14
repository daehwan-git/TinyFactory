#pragma once
#include "SerialClass.h"
#include"pch.h"
#include "resource.h"

class ConveyorBeltSP
{
private:
	const CString OBJECT_DETECTION = "OBJECTDETECTION";

	Serial* sp;
	CDialogEx* dialog;
	bool isRun = false;

	CWinThread* conveyorBeltThread;

public:
	ConveyorBeltSP(CString portNumber,CDialogEx* dialog):sp(nullptr),dialog(dialog)
	{
		if (portNumber == "")
		{
			LogManager::GetInstance().WriteLog("�����̾� ��Ʈ ��Ʈ�� ��ȣ�� ��ȿ���� ����");
		}
		else
		{
			LogManager::GetInstance().WriteLog("�����̾� ��Ʈ : " + portNumber + " port �� ����õ�");

			this->sp = new Serial(PORT_PREFIX + portNumber);

			if (sp->IsConnected())
			{
				LogManager::GetInstance().WriteLog("�����̾� ��Ʈ : " + portNumber + " port�� ���� �Ϸ�");
				dialog->PostMessageA(ON_CONNECT_COMPLETE_MESSAGE,0,0);
			}
			else {
				LogManager::GetInstance().WriteLog("�����̾� ��Ʈ : " + portNumber + " port�� ���� ����...");
			}
		}
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
	
private:
	void ParsingReciveData(CString data);
	void ReleaseConveyorBelt();
	static UINT ConvayorBeltRun(LPVOID lpParam);
};

