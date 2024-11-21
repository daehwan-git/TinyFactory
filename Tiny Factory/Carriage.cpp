#include "Carriage.h"
#include <afxinet.h>

void Carriage::StartCarriage()
{
	LogManager::GetInstance()->WriteLog("ȭ���� ���");
	ConnectToCarriage("/start");
}

void Carriage::WaitCarriage()
{
	LogManager::GetInstance()->WriteLog("ȭ���� �غ�");
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

			LogManager::GetInstance()->WriteLog("ȭ���� ��� �Ϸ�");
		}
		else {
			LogManager::GetInstance()->WriteLog("ȭ���� ��� ����");
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
		LogManager::GetInstance()->WriteLog("ȭ���� ��� ����");
		e->Delete();
	}

}
