#pragma once

#include "pch.h"
#include "SerialClass.h"

class DataProcessSP
{
private:
	CDialogEx* dialog;
	Serial* sp = nullptr;
	bool isRun = false;

	CWinThread* dataProcessThread = nullptr;

public:
	DataProcessSP(CString portNumber, CDialogEx* dialog);

	~DataProcessSP()
	{
		StopDataProcess();
		ReleaseDataProcess();
	}

	void StartDataProcess();
	void StopDataProcess();
	bool IsRun() { return isRun; }
	void ParsingData(CString& data);

private:
	void ReleaseDataProcess();
	static UINT DataProcessThread(LPVOID lpParam);
};

