#include  "WorkManager.h"
#include <opencv2/core/cvstd.hpp>

WorkManager* WorkManager::instance = nullptr;
std::mutex WorkManager::mtx;

void WorkManager::FinishObjectDetection()
{
	if (isDetection)
	{
		if (conveyorBeltSP != nullptr)
		{
			conveyorBeltSP->StartConveyorBelt();
		}
		
		PostMessage(mainHandle,DETECTIONFINISH,NULL,NULL);
	}
}

void WorkManager::ResetDetection()
{
	conveyorBeltSP->ResetDetect();
}

void WorkManager::ResetYolo()
{
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

		LogManager::GetInstance().WriteLog("������Ʈ ������.");

		if(objectDetection != nullptr)
			objectDetection->StartObjectDetection();
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
		
		LogManager::GetInstance().WriteLog("���������� ������Ʈ ������.");
		conveyorBeltSP->KnockDown();
	}
	else {
		LogManager::GetInstance().WriteLog("�������� ������Ʈ ������.");
	}

	FinishObjectDetection();

}
