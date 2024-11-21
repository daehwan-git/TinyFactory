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
	if (ip == "")return;
	try {
		CInternetSession session("CARRIAGE");
		CHttpConnection* connection = nullptr;
		CHttpFile* file = nullptr;

		session.SetOption(INTERNET_OPTION_END_BROWSER_SESSION, 1);
		
		connection = session.GetHttpConnection(
			ip, INTERNET_DEFAULT_HTTP_PORT,
			nullptr,
			nullptr);

		file = connection->OpenRequest(
			CHttpConnection::HTTP_VERB_GET, command);
		file->SendRequest();

		DWORD status = 0;
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

		if (file) {
			file->Close();
			delete file;
		}
		if (connection) {
			connection->Close();
			delete connection;
		}
	}
	catch (CInternetException* e) {
		LogManager::GetInstance()->WriteLog("화물차 통신 실패");
		e->Delete();
	}

}
