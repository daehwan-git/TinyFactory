#include "FileManager.h"
#include<fstream>
#include<vector>
#include<string>

FileManager* FileManager::instance = nullptr;

FileManager* FileManager::GetInstance()
{
    if (instance != nullptr)
    {
        return instance;
    }
    else {
        instance = new FileManager();
        return instance;
    }
}

bool FileManager::SaveFile(std::vector<CString>  data)
{
    //메모장에 데이터 저장
    TCHAR path[256] = { 0, };
    GetModuleFileName(NULL, path, 256);

    CString folderPath(path);
    folderPath = folderPath.Left(folderPath.ReverseFind('\\'));

    std::ofstream  fout(DATASTORE_FILE_NAME, std::ios::app | std::ios::out);

    if (fout.is_open())
    {
        for (int i = 0; i < data.size(); i++)
        {
            fout << std::string(data[i]) << "\n";
        }

        fout.close();

        LogManager::GetInstance()->WriteLog("로그 데이터 저장 완료.");
    }
    else {
        LogManager::GetInstance()->WriteLog("로그 데이터 저장 실패.");
    }

    return false;
}
