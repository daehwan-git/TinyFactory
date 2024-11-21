#pragma once

#include "pch.h"
#include <queue>

class RobotArmSP
{
private:
	CDialogEx* dialog;
	Serial* sp;
	bool isRun = false;
	bool isFinishCommand = true;
	bool isPlaying = false;
	int rightCount = 0;
	
	std::queue<CString> objectQueue;

public:
	RobotArmSP(CString portNumber, CDialogEx* dialog) :sp(nullptr), dialog(dialog)
	{
		if (portNumber == "")
		{
			LogManager::GetInstance()->WriteLog("�κ��� ��Ʈ�� ��ȣ�� ��ȿ���� ����");
		}
		else
		{
			LogManager::GetInstance()->WriteLog("�κ��� : " + portNumber + " port �� ����õ�");

			this->sp = new Serial(PORT_PREFIX + portNumber,BAUDRATE);

			if (sp->IsConnected())
			{
				LogManager::GetInstance()->WriteLog("�κ��� : " + portNumber + " port�� ���� �Ϸ�");
				StartDataProcess();
			}
			else {
				LogManager::GetInstance()->WriteLog("�κ��� : " + portNumber + " port�� ���� ����...");
			}
		}
	}

	~RobotArmSP()
	{
		StopDataProcess();
		ReleaseDataProcess();
	}


	void StartDataProcess();
	void StopDataProcess();
	void SendCommand(CString command);
	void SendCommandList(CString command, bool rightOrWrong);
	void PlayRobotArm();
	void AddObjectType(bool isNormal);
	
	

private:
	void ReleaseDataProcess();
	bool IsRun() { return isRun; }
	void ParsingData(CString command);
	static UINT DataProcessThread(LPVOID lpParam);
};

