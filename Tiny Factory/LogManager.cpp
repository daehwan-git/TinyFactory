#include "pch.h"
#include "LogManager.h"


void LogManager::InitLogControl(CListBox* listBox)
{
	this->logListBox = listBox;
}


void LogManager::WriteLog(CString insertData)
{
	CTime cTime = CTime::GetCurrentTime();

	CString strDate;
	strDate.Format("[%04d년 %02d월 %02d일 %02d시 %02d분 %02d초]", cTime.GetYear(), 
		cTime.GetMonth(), 
		cTime.GetDay(),
		cTime.GetHour(),
		cTime.GetMinute(),
		cTime.GetSecond());

	insertData = strDate +  " : " + insertData;

	logListBox->InsertString(0,insertData);
}