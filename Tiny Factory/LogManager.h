#pragma once


#include "pch.h"

class LogManager
{

private:
	static LogManager* instance;
	static std::mutex mtx;
	CDialogEx* m_dialog;

	~LogManager();

public:
	static LogManager* GetInstance();

	void InitLogControl(CDialogEx* listBox);

	void WriteLog(CString insertData);
};