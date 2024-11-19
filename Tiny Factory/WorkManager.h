#pragma once

#include"pch.h"
#include  "ConveyorBelt.h"
#include "DataProcessSP.h"
#include <opencv2/core/cvstd.hpp>
#include "ObjectDetection.h"
#include "RobotArmSP.h"
#include"Carriage.h"

class DataProcessSP;
class ConveyorBeltSP;
class ObjectDetection;
class RobotArmSP;
class Carriage;

class WorkManager
{
private:
	static WorkManager* instance;
	static std::mutex mtx;
	

public:
	static WorkManager* GetInstance()
	{
		if (instance == nullptr) { 
			std::lock_guard<std::mutex> lock(mtx); 
			if (instance == nullptr) { 
				instance = new WorkManager();
			}
		}
		return instance;
	}


private:
	bool isDetection = false;
	CString detectionClassName = "";
	bool objectCheck = false;

	ConveyorBeltSP* conveyorBeltSP = nullptr;
	ObjectDetection* objectDetection = nullptr;
	Carriage* carriage = nullptr;
	RobotArmSP* robotArmSP = nullptr;
	HWND mainHandle = nullptr;

public:
	void InitConvayorBeltSP(ConveyorBeltSP* conveyorBeltSP)
	{
		this->conveyorBeltSP = conveyorBeltSP;
	}

	void InitObjectDetection(ObjectDetection* objectDetection)
	{
		this->objectDetection = objectDetection;
	}

	void InitRobotArmSP(RobotArmSP* robotArmSP)
	{
		this->robotArmSP = robotArmSP;
	}

	void InitCarriage(Carriage* carriage)
	{
		this->carriage = carriage;
	}


public:
	void ObjectDetection();
	void FinishYOLO(std::vector<cv::String> classNames);
	bool IsDetection() { return isDetection; }
	void ResetDetection();
	void ResetGoal();
	void SetMainHandle(HWND hwnd);
	void ObjectGoal();

	void StartCarriage();
	int GetMaxCarriageCount();
	void SetMaxCarriage(int count);
};

