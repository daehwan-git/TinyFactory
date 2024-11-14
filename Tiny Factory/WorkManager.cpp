#include  "WorkManager.h"
#include <opencv2/core/cvstd.hpp>

WorkManager* WorkManager::instance = nullptr;

void WorkManager::FinishObjectDetection()
{
	if (isDetection)
	{
		isDetection = false;

		if (conveyorBeltSP != nullptr)
		{
			conveyorBeltSP->StartConveyorBelt();
		}

		Sleep(5000);

		conveyorBeltSP->ResetDetect();
	}
}

//some object detected
void WorkManager::ObjectDetection()
{
	if (!isDetection)
	{
		isDetection = true;

		LogManager::GetInstance().WriteLog("������Ʈ ������.");

		if (conveyorBeltSP != nullptr)
		{
			conveyorBeltSP->StopConveyorBelt();
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
			LogManager::GetInstance().WriteLog("�������� ������Ʈ ������.");
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
		FinishObjectDetection();
	}


	if (!objectCheck)
	{
		
	}
}
