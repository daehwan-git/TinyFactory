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
			LogManager::GetInstance().WriteLog("·Îº¿ÆÈ Æ÷Æ®ÀÇ ¹øÈ£°¡ À¯È¿ÇÏÁö ¾ÊÀ½");
		}
		else
		{
			LogManager::GetInstance().WriteLog("·Îº¿ÆÈ : " + portNumber + " port ¿¡ ¿¬°á½Ãµµ");

			this->sp = new Serial(PORT_PREFIX + portNumber);

			if (sp->IsConnected())
			{
				LogManager::GetInstance().WriteLog("·Îº¿ÆÈ : " + portNumber + " port¿¡ ¿¬°á ¿Ï·á");
			}
			else {
				LogManager::GetInstance().WriteLog("·Îº¿ÆÈ : " + portNumber + " port¿¡ ¿¬°á ½ÇÆÐ...");
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

