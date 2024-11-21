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

void WorkManager::StartCarriage()
{
	if (carriage != nullptr)
		carriage->StartCarriage();
}

int WorkManager::GetMaxCarriageCount()
{
	return carriage->GetCarriageCount();
}

void WorkManager::SetMaxCarriage(int count)
{
	carriage->SetCarriageCount(count);
}

//some object detected
void WorkManager::ObjectDetection()
{
	if (!isDetection)
	{
		isDetection = true;

		LogManager::GetInstance()->WriteLog("������Ʈ ������.");
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
		
		LogManager::GetInstance()->WriteLog("���������� ������Ʈ ������.");

		DataManager::GetInstance()->IncreaseWrongCount();

		if (conveyorBeltSP != nullptr)
		{
			conveyorBeltSP->KnockDown();
		}
	}
	else {
		LogManager::GetInstance()->WriteLog("�������� ������Ʈ ������.");

		DataManager::GetInstance()->IncreaseNormalCount();

		if (conveyorBeltSP != nullptr)
		{
			conveyorBeltSP->StartConveyorBelt();
		}
	}

	robotArmSP->AddObjectType(isNormal);
	PostMessage(mainHandle, DETECTIONFINISH, NULL, NULL);

}
