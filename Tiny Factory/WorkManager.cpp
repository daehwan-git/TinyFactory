#include  "WorkManager.h"
#include <opencv2/core/cvstd.hpp>
#include "DataManager.h"

WorkManager* WorkManager::instance = nullptr;
std::mutex WorkManager::mtx;


WorkManager* WorkManager::GetInstance()
{
	if (instance == nullptr) {
		std::lock_guard<std::mutex> lock(mtx);
		if (instance == nullptr) {
			instance = new WorkManager();
		}
	}
	return instance;
}

void WorkManager::InitConvayorBeltSP(ConveyorBeltSP* conveyorBeltSP)
{
	m_conveyorBeltSP = conveyorBeltSP;
}

void WorkManager::InitObjectDetection(ObjectDetection* objectDetection)
{
	m_objectDetection = objectDetection;
}
void WorkManager::InitRobotArmSP(RobotArmSP* robotArmSP)
{
	m_robotArmSP = robotArmSP;
}

void WorkManager::InitCarriage(Carriage* carriage)
{
	m_carriage = carriage;
}

void WorkManager::ResetDetection()
{
	isDetection = false;
	m_conveyorBeltSP->ResetDetect();
	m_objectDetection->ResetFinishFlag();
}

void WorkManager::ResetGoal()
{
	m_conveyorBeltSP->ResetGoal();
}

void WorkManager::SetMainHandle(HWND hwnd)
{
	mainHandle = hwnd;
}

void WorkManager::ObjectGoal()
{
	if(m_robotArmSP != nullptr)
		m_robotArmSP->PlayRobotArm();
}

void WorkManager::ResetIsPlaying()
{
	if (m_robotArmSP != nullptr)
		m_robotArmSP->ResetIsPlaying();
}

void WorkManager::StartCarriage()
{
	if (m_carriage != nullptr)
		m_carriage->StartCarriage();
}

int WorkManager::GetMaxCarriageCount()
{
	if(m_carriage != nullptr)
		return m_carriage->GetCarriageCount();
	return 0;
}

void WorkManager::SetMaxCarriage(int count)
{
	if(m_carriage != nullptr)
		m_carriage->SetCarriageCount(count);
}


void WorkManager::ObjectDetected()
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

		if (m_conveyorBeltSP != nullptr)
		{
			m_conveyorBeltSP->KnockDown();
		}
	}
	else {
		LogManager::GetInstance()->WriteLog("정상적인 오브젝트 감지됨.");

		DataManager::GetInstance()->IncreaseNormalCount();

		if (m_conveyorBeltSP != nullptr)
		{
			m_conveyorBeltSP->StartConveyorBelt();
		}
	}

	if (m_robotArmSP != nullptr)
	{
		m_robotArmSP->AddObjectType(isNormal);
	}
	PostMessage(mainHandle, DETECTIONFINISH, NULL, NULL);
}
