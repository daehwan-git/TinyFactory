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

			LogManager::GetInstance()->WriteLog("ȭ���� ��� �Ϸ�");
		}
		else {
			LogManager::GetInstance()->WriteLog("ȭ���� ��� ����");
		}

		file->Close();
		connection->Close();
		delete file;
		delete connection;
	}
	catch (Exception e) {
		LogManager::GetInstance()->WriteLog("ȭ���� ��� ����");
	}
}
