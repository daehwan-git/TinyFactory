#include "DataManager.h"


DataManager* DataManager::instance = nullptr;
std::mutex DataManager::mtx;

DataManager* DataManager::GetInstance()
{
	if (instance == nullptr) {
		std::lock_guard<std::mutex> lock(mtx);
		if (instance == nullptr) {
			instance = new DataManager();
		}
	}
	return instance;
}

void DataManager::SetMainHandle(HWND mainHandle)
{
	m_mainHandle = mainHandle;
}

void DataManager::IncreaseWrongCount()
{
	wrongObjectCount++;
	PostMessage(m_mainHandle,WRONG_OBJECT_INC, wrongObjectCount,NULL);
}

void DataManager::IncreaseNormalCount()
{
	normalObjectCount++;
	carriageObjectCount++;
	PostMessage(m_mainHandle,NORMAL_OBJECT_INC,normalObjectCount,NULL);
}

void DataManager::CheckNormalCount(int* count)
{
	int maxCount = WorkManager::GetInstance()->GetMaxCarriageCount();
	if (*count >= maxCount)
	{
		*count -= maxCount;
		WorkManager::GetInstance()->StartCarriage();
	}
}
