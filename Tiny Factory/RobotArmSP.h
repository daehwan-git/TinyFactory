#pragma once

#include "pch.h"

class RobotArmSP
{
private:
	CDialogEx* dialog;
	Serial* sp;
	bool isRun = false;
	bool isFinishCommand = true;


public:
	RobotArmSP(CString portNumber, CDialogEx* dialog) :sp(nullptr), dialog(dialog)
	{
		if (portNumber == "")
		{
			LogManager::GetInstance().WriteLog("�κ��� ��Ʈ�� ��ȣ�� ��ȿ���� ����");
		}
		else
		{
			LogManager::GetInstance().WriteLog("�κ��� : " + portNumber + " port �� ����õ�");

			this->sp = new Serial(PORT_PREFIX + portNumber);

			if (sp->IsConnected())
			{
				LogManager::GetInstance().WriteLog("�κ��� : " + portNumber + " port�� ���� �Ϸ�");
			}
			else {
				LogManager::GetInstance().WriteLog("�κ��� : " + portNumber + " port�� ���� ����...");
			}
		}
	}

	~RobotArmSP()
	{
		
	}


	void StartDataProcess();
	void StopDataProcess();
	void SendCommand(CString command);
	void SendCommandList(CString command);
	void ParsingData(CString command);
	bool IsRun() { return isRun; }
	

private:
	void ReleaseDataProcess();
	static UINT DataProcessThread(LPVOID lpParam);
};

