#include "WorkManager.h"

void WorkManager::FinishObjectDetection()
{
	//move convayor belt again
	LogManager::GetInstance().WriteLog("컨베이어 벨트 재가동.");

	if (conbayorBeltSP != nullptr)
	{
		conbayorBeltSP->StartConvayorBelt();
	}
}

//some object detected
void WorkManager::ObjectDetection()
{

	//stop convayor while finish object detection
	LogManager::GetInstance().WriteLog("오브젝트 감지됨.");

	if (conbayorBeltSP != nullptr)
	{
		conbayorBeltSP->StopConvayorBelt();
	}
}




//finish yolo 
void WorkManager::FinishObjectDetection(std::vector<std::string> classNames)
{
	//case 1: keep going 
	//case 2 robot arms moving

	bool isNormal = false;

	for (int i = 0; i < classNames.size(); i++)
	{
		if (classNames[i] == NORMALOBJECT)
		{
			isNormal = true;
		}
	}

	if (!isNormal)
	{
		//robot arms can move


	}else{
		FinishObjectDetection();
	}
}

