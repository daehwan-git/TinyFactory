#include "pch.h"
#include "ConvayorBeltSP.h"


void ConvayorBeltSP::StopConvayorBelt()
{
	if (sp == nullptr)return;
	if (isRun)
	{
		if (sp->IsConnected())
		{
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
		sp->~Serial();
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

		if (!result.IsEmpty())
		{
			if (result.Compare(OBJECT_DETECTION) == 0)
			{
				LogManager::GetInstance().WriteLog("들어왔으유");
				convayorBeltSP->StopConvayorBelt();
			}

			result += _T("\r\n");
			LogManager::GetInstance().WriteLog(result);
		}

		Sleep(SYNC_TIME);
	}

	return 0;
}


