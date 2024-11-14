#pragma once

#include"pch.h"
#include  "ConveyorBelt.h"
#include "DataProcessSP.h"
#include <opencv2/core/cvstd.hpp>

class DataProcessSP;
class ConveyorBeltSP;

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

	ConveyorBeltSP* conbayorBeltSP = nullptr;
	DataProcessSP* dataProcessSP = nullptr;

public:
	void InitConvayorBeltSP(ConveyorBeltSP* conbayorBeltSP)
	{
		this->conbayorBeltSP = conbayorBeltSP;
	}

	void InitDataProcessSP(DataProcessSP* dataProcessSP)
	{
		this->dataProcessSP = dataProcessSP;
	}


private:
	void FinishObjectDetection();

public:
	void ObjectDetection();
	void FinishYOLO(std::vector<cv::String> classNames);
	bool IsDetection() { return isDetection; }
};

