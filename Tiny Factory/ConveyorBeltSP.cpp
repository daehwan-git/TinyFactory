#include "pch.h"
#include "ConveyorBelt.h"


void ConveyorBeltSP::StopConveyorBelt()
{
	if (sp == nullptr)return;
	if (isRun)
	{
		if (sp->IsConnected())
		{
			LogManager::GetInstance().WriteLog("�����̾� ��Ʈ �۵� ����");
			sp->WriteData(CONVAYORBELT_OFF_DATA, DATA_LENGTH);
		}
		isRun = false;
	}
}

void ConveyorBeltSP::StartConveyorBelt()
{
	if (sp == nullptr)return;

	LogManager::GetInstance().WriteLog("�����̾� ��Ʈ �۵�");

	isRun = true;

	if (sp->IsConnected())
	{
		sp->WriteData(CONVAYORBELT_ON_DATA, DATA_LENGTH);
	}

	conveyorBeltThread = AfxBeginThread(ConvayorBeltRun,this);
}

void ConveyorBeltSP::ReleaseConveyorBelt()
{
	if (sp != nullptr)
	{	
		WaitForSingleObject(conveyorBeltThread, INFINITE);
		delete sp;
	}
}

UINT ConveyorBeltSP::ConvayorBeltRun(LPVOID lpParam)
{

	ConveyorBeltSP* convayorBeltSP = (ConveyorBeltSP*)lpParam;

	char incomingData[256] = "";
	int resultData = 0;

	while (convayorBeltSP->IsRun())
	{
		memset(incomingData, 0, DATA_LENGTH);

		int resultData = convayorBeltSP->sp->ReadData(incomingData, DATA_LENGTH - 1);

		incomingData[resultData] = '\0';

		CString result(incomingData);

		Sleep(SYNC_TIME);
	}

	return 0;
}


