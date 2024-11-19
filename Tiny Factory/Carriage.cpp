#include "Carriage.h"
#include <afxinet.h>

void Carriage::StartCarriage()
{
	LogManager::GetInstance()->WriteLog("화물차 출발");
	ConnectToCarriage("/start");
}

void Carriage::WaitCarriage()
{
	LogManager::GetInstance()->WriteLog("화물차 준비");
	ConnectToCarriage("/wait");
}

void Carriage::ConnectToCarriage(CString command)
{
	try {
		CInternetSession session("CARRIAGE");

		CHttpConnection* connection = session.GetHttpConnection(
			ip, INTERNET_DEFAULT_HTTP_PORT,
			nullptr,
			nullptr);

		CHttpFile* file = connection->OpenRequest(
			CHttpConnection::HTTP_VERB_GET, command);

		file->SendRequest();

		DWORD status;
		file->QueryInfoStatusCode(status);

		if (status == HTTP_STATUS_OK)
		{
			CString response;
			CString line;

			while (file->ReadString(line))
				response += line;

			LogManager::GetInstance()->WriteLog("화물차 통신 완료");
		}
		else {
			LogManager::GetInstance()->WriteLog("화물차 통신 실패");
		}

		file->Close();
		connection->Close();
		delete file;
		delete connection;
	}
	catch (Exception e) {
		LogManager::GetInstance()->WriteLog("화물차 통신 실패");
	}
}
