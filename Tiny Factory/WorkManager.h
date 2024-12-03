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
	static WorkManager* GetInstance();


private:
	bool isDetection = false;
	CString detectionClassName = "";
	bool objectCheck = false;

	ConveyorBeltSP* m_conveyorBeltSP = nullptr;
	ObjectDetection* m_objectDetection = nullptr;
	Carriage* m_carriage = nullptr;
	RobotArmSP* m_robotArmSP = nullptr;
	HWND mainHandle = nullptr;

public:
	void InitConvayorBeltSP(ConveyorBeltSP* conveyorBeltSP);
	void InitObjectDetection(ObjectDetection* objectDetection);
	void InitRobotArmSP(RobotArmSP* robotArmSP);
	void InitCarriage(Carriage* carriage);


public:
	void ObjectDetected();
	void FinishYOLO(std::vector<cv::String> classNames);
	bool IsDetection() { return isDetection; }
	void ResetDetection();
	void ResetGoal();
	void SetMainHandle(HWND hwnd);
	void ObjectGoal();
	void ResetIsPlaying();

	void StartCarriage();
	int GetMaxCarriageCount();
	void SetMaxCarriage(int count);
};

