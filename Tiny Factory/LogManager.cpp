#include "pch.h"
#include "LogManager.h"


void LogManager::InitLogControl(CListBox* listBox)
{
	this->logListBox = listBox;
}


void LogManager::WriteLog(CString insertData)
{
	printf("%s", insertData);
	CTime cTime = CTime::GetCurrentTime();

	CString strDate;
	strDate.Format("[%04d�� %02d�� %02d�� %02d�� %02d�� %02d��]", cTime.GetYear(), 
		cTime.GetMonth(), 
		cTime.GetDay(),
		cTime.GetHour(),
		cTime.GetMinute(),
		cTime.GetSecond());

	insertData = strDate +  " : " + insertData;

	logListBox->AddString(insertData);
	logListBox->SetCurSel(logListBox->GetCount() - 1);
}