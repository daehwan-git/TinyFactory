#pragma once

#include "pch.h"

class RobotArmSP
{
private:
	CDialogEx* dialog;
	Serial* sp;
	bool isRun = false;


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


	void StartDataProcess();
	void StopDataProcess();
	void ReleaseDataProcess();
	void SendCommand(CString command);
	bool IsRun() { return isRun; }
	

private:
	static UINT DataProcessThread(LPVOID lpParam);
};

