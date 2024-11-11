#include "pch.h"
#include "ConvayorBeltSP.h"


void ConvayorBeltSP::StopConvayorBelt()
{
	if (sp == nullptr)return;
	if (isRun)
	{
		if (sp->IsConnected())
		{
			LogManager::GetInstance().WriteLog("컨베이어 벨트 작동 중지");
			sp->WriteData(CONVAYORBELT_OFF_DATA, DATA_LENGTH);
		}
		isRun = false;
	}
}

void ConvayorBeltSP::StartConvayorBelt()
{
	if (sp == nullptr)return;

	LogManager::GetInstance().WriteLog("컨베이어 벨트 작동");

	isRun = true;

	if (sp->IsConnected())
	{
		sp->WriteData(CONVAYORBELT_ON_DATA, DATA_LENGTH);
	}

	AfxBeginThread(ConvayorBeltRun,this);
}

void ConvayorBeltSP::ReleaseConvayorBelt()
{
	if (sp != nullptr)
	{	
		WaitForSingleObject(ConvayorBeltRun, INFINITE);
		delete sp;
	}
}

UINT ConvayorBeltSP::ConvayorBeltRun(LPVOID lpParam)
{

	ConvayorBeltSP* convayorBeltSP = (ConvayorBeltSP*)lpParam;

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


