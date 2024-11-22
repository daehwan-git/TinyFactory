#include "pch.h"
#include "LogManager.h"


LogManager* LogManager::instance = nullptr;
std::mutex LogManager::mtx;

LogManager::~LogManager()
{
}


void LogManager::InitLogControl(CDialogEx* dialog)
{
	this->dialog = dialog;
}

void LogManager::WriteLog(CString insertData)
{
	CTime aTime;
	CTime cTime = CTime::GetCurrentTime();

	CString strDate;
	strDate.Format("[%04d�� %02d�� %02d�� %02d�� %02d�� %02d��]", cTime.GetYear(), 
		cTime.GetMonth(), 
		cTime.GetDay(),
		cTime.GetHour(),
		cTime.GetMinute(),
		cTime.GetSecond());


	CString* sendData = new CString(strDate + " : " + insertData);

	LPARAM lParam = reinterpret_cast<LPARAM>(sendData);
	
	PostMessage(dialog->m_hWnd,LOG_WRITE,NULL, lParam);
}