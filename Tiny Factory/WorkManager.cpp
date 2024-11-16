#include  "WorkManager.h"
#include <opencv2/core/cvstd.hpp>

WorkManager* WorkManager::instance = nullptr;
std::mutex WorkManager::mtx;


void WorkManager::ResetDetection()
{
	isDetection = false;
	conveyorBeltSP->ResetDetect();
	objectDetection->ResetFinishFlag();
}

void WorkManager::SetMainHandle(HWND hwnd)
{
	mainHandle = hwnd;
}

void WorkManager::ObjectGoal()
{
	
}

//some object detected
void WorkManager::ObjectDetection()
{
	if (!isDetection)
	{
		isDetection = true;

		LogManager::GetInstance()->WriteLog("오브젝트 감지됨.");
	}
}

void WorkManager::FinishYOLO(std::vector<cv::String> classNames)
{
	bool isNormal = false;

	for (int i = 0; i < classNames.size(); i++)
	{
		if (classNames[i] == NORMALOBJECT)
		{
			isNormal = true;
			break;
		}
	}

	if (!isNormal)
	{
		//robot arms can move
		
		LogManager::GetInstance()->WriteLog("비정상적인 오브젝트 감지됨.");

		if (conveyorBeltSP != nullptr)
		{
			conveyorBeltSP->KnockDown();
		}

		PostMessage(mainHandle, DETECTIONFINISH, NULL, NULL);
	}
	else {
		LogManager::GetInstance()->WriteLog("정상적인 오브젝트 감지됨.");

		if (conveyorBeltSP != nullptr)
		{
			conveyorBeltSP->StartConveyorBelt();
		}
	}

	PostMessage(mainHandle, DETECTIONFINISH, NULL, NULL);

}
