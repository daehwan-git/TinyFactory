#pragma once

#include "pch.h"
#include "SerialClass.h"

class DataProcessSP
{
private:
	CDialogEx* dialog;
	Serial* sp;
	bool isRun = false;


	DataProcessSP(CString portNumber, CDialogEx* dialog):sp(nullptr),dialog(dialog)
	{

	}
};

