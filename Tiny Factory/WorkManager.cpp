#include  "WorkManager.h"
#include <opencv2/core/cvstd.hpp>

void WorkManager::FinishObjectDetection()
{
	if (isDetection)
	{
		isDetection = false;
		//move convayor belt again
		LogManager::GetInstance().WriteLog("컨베이어 벨트 재가동.");

		if (conbayorBeltSP != nullptr)
		{
			conbayorBeltSP->StartConveyorBelt();
		}
	}
}

//some object detected
void WorkManager::ObjectDetection()
{
	if (!isDetection)
	{
		isDetection = true;
		//stop convayor while finish object detection
		LogManager::GetInstance().WriteLog("오브젝트 감지됨.");

		if (conbayorBeltSP != nullptr)
		{
			conbayorBeltSP->StopConveyorBelt();
		}
	}
}

void WorkManager::FinishYOLO(std::vector<cv::String> classNames)
{
	//case 1: keep going 
	//case 2 robot arms moving

	objectCheck = true;

	bool isNormal = false;

	for (int i = 0; i < classNames.size(); i++)
	{
		if (classNames[i] == NORMALOBJECT)
		{
			isNormal = true;
			LogManager::GetInstance().WriteLog("정상적인 오브젝트 감지됨.");
			break;
		}
	}

	if (!isNormal)
	{
		//robot arms can move

		LogManager::GetInstance().WriteLog("비정상적인 오브젝트 감지됨.");
	}
	else {
		//FinishObjectDetection();
	}


	if (!objectCheck)
	{
		
	}
}
