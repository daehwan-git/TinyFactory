#pragma once

#include "pch.h"

class RobotArmSP
{
private:
	CDialogEx* dialog;
	Serial* sp;
	bool isRun = false;
	bool isFinishCommand = true;
	bool isPlaying = false;


public:
	RobotArmSP(CString portNumber, CDialogEx* dialog) :sp(nullptr), dialog(dialog)
	{
		if (portNumber == "")
		{
			LogManager::GetInstance()->WriteLog("·Îº¿ÆÈ Æ÷Æ®ÀÇ ¹øÈ£°¡ À¯È¿ÇÏÁö ¾ÊÀ½");
		}
		else
		{
			LogManager::GetInstance()->WriteLog("·Îº¿ÆÈ : " + portNumber + " port ¿¡ ¿¬°á½Ãµµ");

			this->sp = new Serial(PORT_PREFIX + portNumber);

			if (sp->IsConnected())
			{
				LogManager::GetInstance()->WriteLog("·Îº¿ÆÈ : " + portNumber + " port¿¡ ¿¬°á ¿Ï·á");
				StartDataProcess();
			}
			else {
				LogManager::GetInstance()->WriteLog("·Îº¿ÆÈ : " + portNumber + " port¿¡ ¿¬°á ½ÇÆÐ...");
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
	void SendCommandList(CString command);
	void PlayRobotArm();
	void SendObjectType(bool isNormal);
	

private:
	void ReleaseDataProcess();
	bool IsRun() { return isRun; }
	void ParsingData(CString command);
	static UINT DataProcessThread(LPVOID lpParam);
};

