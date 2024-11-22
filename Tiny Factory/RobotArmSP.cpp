#include "RobotArmSP.h"
#include"DataManager.h"

void RobotArmSP::StartDataProcess()
{
	if (sp == nullptr)return;

	LogManager::GetInstance()->WriteLog("·Îº¿ÆÈ ÀÛµ¿");

	isRun = true;

	if (sp->IsConnected())
	{
		sp->WriteData(DATAPROCESS_ON_DATA, DATA_LENGTH);
	}

	AfxBeginThread(DataProcessThread, this);
}

void RobotArmSP::StopDataProcess()
{
}

void RobotArmSP::ReleaseDataProcess()
{
}

void RobotArmSP::SendCommand(CString command)
{
	if (sp == nullptr)return;

	LogManager::GetInstance()->WriteLog("·Îº¿ÆÈ ¸í·É¾î ¼Û½Å");

	if (sp->IsConnected())
	{
		sp->WriteData(command, DATA_LENGTH);
	}
}

void RobotArmSP::SendCommandList(CString command,bool rightOrWrong)
{
	if (rightOrWrong == true)
	{
		command = RIGHT_STORED_COMMAND + command + "\n";
	}
	else {
		command = WRONG_STORED_COMMAND + command + "\n";
	}
	
	isFinishCommand = false;

	if (sp == nullptr)return;

	LogManager::GetInstance()->WriteLog("·Îº¿ÆÈ ¸í·É¾î ¼Û½Å");

	if (sp->IsConnected())
	{
		sp->WriteData(command, DATA_LENGTH);
	}

}

void RobotArmSP::PlayRobotArm()
{
	if (sp == nullptr)return;

	if (!isPlaying)
	{
		if (objectQueue.empty()) return;

		CString objectType = objectQueue.front(); objectQueue.pop();
		if (sp->IsConnected())
		{
			isPlaying = true;
			Sleep(ROBOT_WAIT_TIME);
			WorkManager::GetInstance()->ResetGoal();
			sp->WriteData(objectType,DATA_LENGTH);
			PostMessage(dialog->m_hWnd, ROBOTARM_CONDITION_CHANGED, Status::PLAYING, NULL);
			dialog->SetTimer(ROBOT_TIMER, 3000, NULL);
		}
	}
}

void RobotArmSP::AddObjectType(bool isNormal)
{
	if (isNormal)
	{
		objectQueue.push(RIGHT_OBJECT);
	}
	else {
		objectQueue.push(WRONG_OBJECT);
	}

}

void RobotArmSP::ResetIsPlaying()
{
	isPlaying = false;
}

void RobotArmSP::ParsingData(CString command)
{
	const bool isCommandFinish =
		(command == RIGHT_COMMANDFNINISH ||
			command == EMPTY_OBJECT ||
			command == WRONG_COMMANDFNINISH);

	if (isCommandFinish) {
		PostMessage(dialog->m_hWnd, ROBOTARM_CONDITION_CHANGED, Status::WAIT, NULL);
	}

	if (command == RIGHT_COMMANDFNINISH) {
		++rightCount;
		DataManager::GetInstance()->CheckNormalCount(&rightCount);
	}
}

UINT RobotArmSP::DataProcessThread(LPVOID lpParam)
{
	RobotArmSP* robotArm = (RobotArmSP*)lpParam;

	char incomingData[256] = "";
	int resultData = 0;

	while (robotArm->IsRun())
	{
		memset(incomingData, 0, DATA_LENGTH);

		int resultData = robotArm->sp->ReadData(incomingData, DATA_LENGTH - 1);

		incomingData[resultData] = '\0';

		CString result(incomingData);

		robotArm->ParsingData(result);

		Sleep(SYNC_TIME);
	}

	return 0;
}
