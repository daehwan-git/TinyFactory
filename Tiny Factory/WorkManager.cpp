#include  "WorkManager.h"
#include <opencv2/core/cvstd.hpp>

void WorkManager::FinishObjectDetection()
{
	if (isDetection)
	{
		isDetection = false;
		//move convayor belt again
		LogManager::GetInstance().WriteLog("�����̾� ��Ʈ �簡��.");

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
		LogManager::GetInstance().WriteLog("������Ʈ ������.");

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
			LogManager::GetInstance().WriteLog("�������� ������Ʈ ������.");
			break;
		}
	}

	if (!isNormal)
	{
		//robot arms can move

		LogManager::GetInstance().WriteLog("���������� ������Ʈ ������.");
	}
	else {
		//FinishObjectDetection();
	}


	if (!objectCheck)
	{
		
	}
}
