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
	bool isDetection = false;
	CString detectionClassName = "";
	bool objectCheck = false;

	ConveyorBeltSP* conbayorBeltSP = nullptr;
	DataProcessSP* dataProcessSP = nullptr;

public:
	static WorkManager& GetInstance()
	{
		static WorkManager dataManager;
		return dataManager;
	}

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

