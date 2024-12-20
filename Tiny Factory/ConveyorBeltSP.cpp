#include "pch.h"
#include "ConveyorBelt.h"
#include"DataManager.h"


void ConveyorBeltSP::StopConveyorBelt()
{
	if (sp == nullptr)return;
	if (isRun)
	{
		if (sp->IsConnected())
		{
			LogManager::GetInstance()->WriteLog("컨베이어 벨트 작동 중지");
			sp->WriteData(CONVAYORBELT_OFF_DATA, DATA_LENGTH);
			PostMessage(dialog->m_hWnd, CONVEYORBELT_CONDITION_CHANGED, Status::OFF, NULL);
		}
		isRun = false;
	}
}

void ConveyorBeltSP::StartConveyorBelt()
{
	if (sp == nullptr)return;

	LogManager::GetInstance()->WriteLog("컨베이어 벨트 작동");

	isRun = true;

	if (sp->IsConnected())
	{
		sp->WriteData(CONVAYORBELT_ON_DATA, DATA_LENGTH);
		PostMessage(dialog->m_hWnd,CONVEYORBELT_CONDITION_CHANGED,Status::ON,NULL);
	}

	if(conveyorBeltThread == nullptr)
		conveyorBeltThread = AfxBeginThread(ConvayorBeltRun,this);
}

void ConveyorBeltSP::KnockDown()
{
	if (sp == nullptr)return;

	if (sp->IsConnected())
	{
		sp->WriteData(KNOCKDOWN, DATA_LENGTH);
	}

}

void ConveyorBeltSP::ResetDetect()
{
	if (sp == nullptr)return;

	if (sp->IsConnected())
	{
		for (int i = 0; i < 5; i++)
		{
			sp->WriteData(RESETDETECT, DATA_LENGTH);
			Sleep(30);
		}
	}
}

void ConveyorBeltSP::ResetGoal()
{
	if (sp == nullptr)return;

	if (sp->IsConnected())
	{
		for (int i = 0; i < 5; i++)
		{
			sp->WriteData(RESETGOAL, DATA_LENGTH);
			Sleep(30);
		}
	}
}

void ConveyorBeltSP::ParsingReciveData(CString data)
{
	if (data == OBJECT_DETECTION)
	{
		WorkManager::GetInstance()->ObjectDetected();
	}
	else if (data == OBJECT_GOAL)
	{
		WorkManager::GetInstance()->ObjectGoal();
	}
}

void ConveyorBeltSP::ReleaseConveyorBelt()
{
	if (sp != nullptr)
	{	
		WaitForSingleObject(conveyorBeltThread->m_hThread, INFINITE);
		delete sp;
	}
}

UINT ConveyorBeltSP::ConvayorBeltRun(LPVOID lpParam)
{

	ConveyorBeltSP* conveyorBeltSP = (ConveyorBeltSP*)lpParam;

	char incomingData[256] = "";
	int resultData = 0;

	while (conveyorBeltSP->IsRun())
	{
		memset(incomingData, 0, DATA_LENGTH);

		int resultData = conveyorBeltSP->sp->ReadData(incomingData, DATA_LENGTH - 1);

		incomingData[resultData] = '\0';

		CString result(incomingData);

		conveyorBeltSP->ParsingReciveData(result);

		Sleep(SYNC_TIME);
	}

	return 0;
}


