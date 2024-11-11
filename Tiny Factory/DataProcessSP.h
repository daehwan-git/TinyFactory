#pragma once

#include "pch.h"
#include "SerialClass.h"

class DataProcessSP
{
private:
	CDialogEx* dialog;
	Serial* sp;
	bool isRun = false;


public:
	DataProcessSP(CString portNumber, CDialogEx* dialog):sp(nullptr),dialog(dialog)
	{
		if (portNumber == "")
		{
			LogManager::GetInstance().WriteLog("������ ��Ʈ�� ��ȣ�� ��ȿ���� ����");
		}
		else
		{
			LogManager::GetInstance().WriteLog("������ : " + portNumber + " port �� ����õ�");

			this->sp = new Serial(PORT_PREFIX + portNumber);

			if (sp->IsConnected())
			{
				LogManager::GetInstance().WriteLog("������ : " + portNumber + " port�� ���� �Ϸ�");
			}
			else {
				LogManager::GetInstance().WriteLog("������ : " + portNumber + " port�� ���� ����...");
			}
		}
	}


	void StartDataProcess();
	void StopDataProcess();
	void ReleaseDataProcess();
	bool IsRun() { return isRun; }
	void ParsingData(CString& data);

private:
	static UINT DataProcessThread(LPVOID lpParam);
};

