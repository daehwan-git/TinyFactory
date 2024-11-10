#pragma once

#include"pch.h"
#include  "ConvayorBeltSP.h"
#include "DataProcessSP.h"

class DataProcessSP;
class ConvayorBeltSP;

class WorkManager
{
private:
	bool isDetection = false;
	CString detectionClassName = "";
	bool objectCheck = false;

	ConvayorBeltSP* conbayorBeltSP = nullptr;
	DataProcessSP* dataProcessSP = nullptr;

public:
	static WorkManager& GetInstance()
	{
		static WorkManager dataManager;
		return dataManager;
	}

	void InitConvayorBeltSP(ConvayorBeltSP* conbayorBeltSP)
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
	void FinishYOLO(std::vector<std::string> classNames);
};

