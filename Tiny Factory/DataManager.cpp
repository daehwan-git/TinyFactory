#include "DataManager.h"


DataManager* DataManager::instance = nullptr;
std::mutex DataManager::mtx;

void DataManager::IncreaseWrongCount()
{
	wrongObjectCount++;
	PostMessage(mainHandle,WRONG_OBJECT_INC, wrongObjectCount,NULL);
}

void DataManager::IncreaseNormalCount()
{
	normalObjectCount++;
	PostMessage(mainHandle,NORMAL_OBJECT_INC,normalObjectCount,NULL);
}