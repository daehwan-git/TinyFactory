#pragma once


#include "pch.h"

class LogManager
{

private:
	static LogManager* instance;
	static std::mutex mtx;
	CListBox* logListBox = nullptr;

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

	void InitLogControl(CListBox* listBox);

	void WriteLog(CString insertData);
};