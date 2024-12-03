#include "DataProcessSP.h"

DataProcessSP::DataProcessSP(CString portNumber, CDialogEx* dialog)
{
	if (portNumber == "")
	{
		LogManager::GetInstance()->WriteLog("������ ��Ʈ�� ��ȣ�� ��ȿ���� ����");
	}
	else
	{
		LogManager::GetInstance()->WriteLog("������ : " + portNumber + " port �� ����õ�");

		this->sp = new Serial(PORT_PREFIX + portNumber);

		if (sp->IsConnected())
		{
			LogManager::GetInstance()->WriteLog("������ : " + portNumber + " port�� ���� �Ϸ�");
		}
		else {
			LogManager::GetInstance()->WriteLog("������ : " + portNumber + " port�� ���� ����...");
		}
	}
}

void DataProcessSP::StartDataProcess()
{
	if (sp == nullptr)return;

	LogManager::GetInstance()->WriteLog("������ ��� �۵�");

	isRun = true;

	if (sp->IsConnected())
	{
		sp->WriteData(DATAPROCESS_ON_DATA, DATA_LENGTH);
	}

	dataProcessThread = AfxBeginThread(DataProcessThread, this);
}

void DataProcessSP::StopDataProcess()
{
	if (sp == nullptr)return;
	if (isRun)
	{
		if (sp->IsConnected())
		{
			sp->WriteData(DATAPROCESS_OFF_DATA, DATA_LENGTH);
		}
		isRun = false;
	}
}

void DataProcessSP::ReleaseDataProcess()
{
	if (sp != nullptr)
	{
		WaitForSingleObject(dataProcessThread->m_hThread, INFINITE);
		delete sp;
	}
}

void DataProcessSP::ParsingData(CString& data)
{
	/*if (data.Compare(OBJECT_DETECTION) == 0)
	{
		WorkManager::GetInstance()->ObjectDetection();
	}*/
}

UINT DataProcessSP::DataProcessThread(LPVOID lpParam)
{
	DataProcessSP* dataProcess = (DataProcessSP*)lpParam;

	char incomingData[256] = "";
	int resultData = 0;

	while (dataProcess->IsRun())
	{
		memset(incomingData, 0, DATA_LENGTH);

		int resultData = dataProcess->sp->ReadData(incomingData, DATA_LENGTH - 1);

		incomingData[resultData] = '\0';

		CString result(incomingData);
		

		if (!result.IsEmpty())
		{
			dataProcess->ParsingData(result);
			LogManager::GetInstance()->WriteLog(result);
		}

		Sleep(SYNC_TIME);
	}

	return 0;
}
