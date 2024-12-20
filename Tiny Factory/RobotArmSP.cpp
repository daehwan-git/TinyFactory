#include "RobotArmSP.h"
#include"DataManager.h"

bool RobotArmSP::InitRobotArmSP(CString portNumber, CDialogEx* dialog)
{
	if (portNumber == "")
	{
		LogManager::GetInstance()->WriteLog("�κ��� ��Ʈ�� ��ȣ�� ��ȿ���� ����");
	}
	else
	{
		LogManager::GetInstance()->WriteLog("�κ��� : " + portNumber + " port �� ����õ�");

		this->sp = new Serial(PORT_PREFIX + portNumber, BAUDRATE);

		if (sp->IsConnected())
		{
			this->dialog = dialog;
			LogManager::GetInstance()->WriteLog("�κ��� : " + portNumber + " port�� ���� �Ϸ�");
			StartDataProcess();
			return true;
		}
		else {
			LogManager::GetInstance()->WriteLog("�κ��� : " + portNumber + " port�� ���� ����...");
		}
	}

	return false;
}

void RobotArmSP::StartDataProcess()
{
	if (sp == nullptr)return;

	LogManager::GetInstance()->WriteLog("�κ��� �۵�");


	isRun = true;

	if (sp->IsConnected())
	{
		PostMessage(dialog->m_hWnd, ROBOTARM_CONDITION_CHANGED, Status::WAIT, NULL);
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

	LogManager::GetInstance()->WriteLog("�κ��� ���ɾ� �۽�");

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

	LogManager::GetInstance()->WriteLog("�κ��� ���ɾ� �۽�");

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
			PostMessage(dialog->m_hWnd, ROBOTARM_CONDITION_CHANGED, Status::PLAYING, NULL);
			isPlaying = true;
			Sleep(ROBOT_WAIT_TIME);
			WorkManager::GetInstance()->ResetGoal();
			sp->WriteData(objectType,DATA_LENGTH);
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
