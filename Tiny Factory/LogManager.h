#pragma once


#include "pch.h"

class LogManager
{
private:
	CListBox* logListBox = nullptr;

public:
	static LogManager& GetInstance()
	{
		static LogManager instance;
		return instance;
	}

	void InitLogControl(CListBox* listBox);

	void WriteLog(CString insertData);
};