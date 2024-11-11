#pragma once
#include "SerialClass.h"
#include"pch.h"
#include "resource.h"

class ConvayorBeltSP
{
private:
	Serial* sp;
	CDialogEx* dialog;
	bool isRun = false;

public:
	ConvayorBeltSP(CString portNumber,CDialogEx* dialog):sp(nullptr),dialog(dialog)
	{
		if (portNumber == "")
		{
			LogManager::GetInstance().WriteLog("�����̾� ��Ʈ ��Ʈ�� ��ȣ�� ��ȿ���� ����");
		}
		else
		{
			LogManager::GetInstance().WriteLog("�����̾� ��Ʈ : " + portNumber + " port �� ����õ�");

			this->sp = new Serial(PORT_PREFIX + portNumber);

			if (sp->IsConnected())
			{
				LogManager::GetInstance().WriteLog("�����̾� ��Ʈ : " + portNumber + " port�� ���� �Ϸ�");
				dialog->PostMessageA(ON_CONNECT_COMPLETE_MESSAGE,0,0);
			}
			else {
				LogManager::GetInstance().WriteLog("�����̾� ��Ʈ : " + portNumber + " port�� ���� ����...");
			}
		}
	}

	void StopConvayorBelt();
	void StartConvayorBelt();
	void ReleaseConvayorBelt();
	bool IsRun() { return isRun; }
	
private:
	static UINT ConvayorBeltRun(LPVOID lpParam);
};

