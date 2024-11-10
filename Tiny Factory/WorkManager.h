#pragma once

#include"pch.h"
#include "ConvayorBeltSP.h"
#include "DataProcessSP.h"

class WorkManager
{

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
	bool isDetection = false;
	CString detectionClassName = "";
	bool objectCheck = false;

	ConvayorBeltSP* conbayorBeltSP;
	DataProcessSP* dataProcessSP;

private:
	void FinishObjectDetection();

public:
	void ObjectDetection();
	void FinishObjectDetection(std::vector<std::string> classNames);
};

