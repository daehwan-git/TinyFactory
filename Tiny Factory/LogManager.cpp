#include "pch.h"
#include "LogManager.h"


LogManager* LogManager::instance = nullptr;
std::mutex LogManager::mtx;

LogManager::~LogManager()
{
}


LogManager* LogManager::GetInstance()
{
	if (instance == nullptr) 
	{
		std::lock_guard<std::mutex> lock(mtx);
		if (instance == nullptr) 
		{
			instance = new LogManager();
		}
	}
	return instance;
}

void LogManager::InitLogControl(CDialogEx* dialog)
{
	m_dialog = dialog;
}

void LogManager::WriteLog(CString insertData)
{
	CTime aTime;
	CTime cTime = CTime::GetCurrentTime();

	CString strDate;
	strDate.Format("[%04d년 %02d월 %02d일 %02d시 %02d분 %02d초]", cTime.GetYear(), 
		cTime.GetMonth(), 
		cTime.GetDay(),
		cTime.GetHour(),
		cTime.GetMinute(),
		cTime.GetSecond());


	CString* sendData = new CString(strDate + " : " + insertData);

	LPARAM lParam = reinterpret_cast<LPARAM>(sendData);
	
	PostMessage(m_dialog->m_hWnd,LOG_WRITE,NULL, lParam);
}