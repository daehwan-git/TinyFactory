#include  "WorkManager.h"
#include <opencv2/core/cvstd.hpp>
#include "DataManager.h"

WorkManager* WorkManager::instance = nullptr;
std::mutex WorkManager::mtx;


void WorkManager::ResetDetection()
{
	isDetection = false;
	conveyorBeltSP->ResetDetect();
	objectDetection->ResetFinishFlag();
}

void WorkManager::ResetGoal()
{
	conveyorBeltSP->ResetGoal();
}

void WorkManager::SetMainHandle(HWND hwnd)
{
	mainHandle = hwnd;
}

void WorkManager::ObjectGoal()
{
	if(robotArmSP != nullptr)
		robotArmSP->PlayRobotArm();
}

void WorkManager::ResetIsPlaying()
{
	if (robotArmSP != nullptr)
		robotArmSP->ResetIsPlaying();
}

void WorkManager::StartCarriage()
{
	if (carriage != nullptr)
		carriage->StartCarriage();
}

int WorkManager::GetMaxCarriageCount()
{
	if(carriage != nullptr)
		return carriage->GetCarriageCount();
	return 0;
}

void WorkManager::SetMaxCarriage(int count)
{
	if(carriage != nullptr)
		carriage->SetCarriageCount(count);
}

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
		LogManager::GetInstance()->WriteLog("비정상적인 오브젝트 감지됨.");

		DataManager::GetInstance()->IncreaseWrongCount();

		if (conveyorBeltSP != nullptr)
		{
			conveyorBeltSP->KnockDown();
		}
	}
	else {
		LogManager::GetInstance()->WriteLog("정상적인 오브젝트 감지됨.");

		DataManager::GetInstance()->IncreaseNormalCount();

		if (conveyorBeltSP != nullptr)
		{
			conveyorBeltSP->StartConveyorBelt();
		}
	}

	if (robotArmSP != nullptr)
	{
		robotArmSP->AddObjectType(isNormal);
	}
	PostMessage(mainHandle, DETECTIONFINISH, NULL, NULL);
}
