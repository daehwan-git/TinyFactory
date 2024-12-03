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
	enum Status
	{
		WAIT,
		PLAYING
	};
	bool InitRobotArmSP(CString portNumber, CDialogEx* dialog);

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
	void ResetIsPlaying();
	
	

private:
	void ReleaseDataProcess();
	bool IsRun() { return isRun; }
	void ParsingData(CString command);
	static UINT DataProcessThread(LPVOID lpParam);
};

