#pragma once


#include "pch.h"

class LogManager
{

private:
	static LogManager* instance;
	static std::mutex mtx;
	CDialogEx* dialog;

	~LogManager();

public:
	static LogManager* GetInstance()
	{
		if (instance == nullptr) { 
			std::lock_guard<std::mutex> lock(mtx);
			if (instance == nullptr) {
				instance = new LogManager();
			}
		}
		return instance;
	}

	void InitLogControl(CDialogEx* listBox);

	void WriteLog(CString insertData);
};