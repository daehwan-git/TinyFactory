#include "RobotArmSP.h"

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

void RobotArmSP::SendCommandList(CString command)
{

	command = STORECOMMAND + command + "\n";
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
		if (sp->IsConnected())
		{
			isPlaying = true;
			Sleep(ROBOT_WAIT_TIME);
			sp->WriteData(PLAYROBOT, DATA_LENGTH);
		}
	}
}

void RobotArmSP::SendObjectType(bool isNormal)
{
	if (sp == nullptr)return;

	if (sp->IsConnected())
	{
		if (isNormal)
		{
			sp->WriteData(RIGHT_OBJECT, DATA_LENGTH);
		}
		else {
			sp->WriteData(WRONG_OBJECT, DATA_LENGTH);
		}
	}

}

void RobotArmSP::ParsingData(CString command)
{
	if (command == "")return;
	if (command == COMMANDFNINISH)
	{
		isPlaying = false;
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
