#pragma once

#include"pch.h"
#include  "ConveyorBelt.h"
#include "DataProcessSP.h"
#include <opencv2/core/cvstd.hpp>
#include "ObjectDetection.h"

class DataProcessSP;
class ConveyorBeltSP;
class ObjectDetection;

class WorkManager
{
private:
	static WorkManager* instance;
	

public:
	static WorkManager* GetInstance()
	{
		if (instance != nullptr) {
			return instance;
		}
		else {
			instance = new WorkManager();
			return instance;
		}
	}


private:
	bool isDetection = false;
	CString detectionClassName = "";
	bool objectCheck = false;

	ConveyorBeltSP* conveyorBeltSP = nullptr;
	ObjectDetection* objectDetection = nullptr;
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

private:
	void FinishObjectDetection();

public:
	void ObjectDetection();
	void FinishYOLO(std::vector<cv::String> classNames);
	bool IsDetection() { return isDetection; }
	void ResetDetection();
	void ResetYolo();
	void SetMainHandle(HWND hwnd);
};

