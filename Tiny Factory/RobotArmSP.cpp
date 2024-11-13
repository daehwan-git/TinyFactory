#include "RobotArmSP.h"

void RobotArmSP::StartDataProcess()
{
	if (sp == nullptr)return;

	LogManager::GetInstance().WriteLog("�κ��� �۵�");

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

	LogManager::GetInstance().WriteLog("�κ��� ���ɾ� �۽�");

	if (sp->IsConnected())
	{
		sp->WriteData(command, DATA_LENGTH);
	}
}

void RobotArmSP::SendCommandList(CString command)
{

		command = STORECOMMAND + command;
		isFinishCommand = false;

		if (sp == nullptr)return;

		LogManager::GetInstance().WriteLog("�κ��� ���ɾ� �۽�");

		if (sp->IsConnected())
		{
			sp->WriteData(command, DATA_LENGTH);
		}
	
}

void RobotArmSP::ParsingData(CString command)
{
	printf("%s", command);
	if (command == COMMANDFNINISH)
	{
		isFinishCommand = true;
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
