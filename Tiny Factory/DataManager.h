#pragma once
#include "pch.h"


class DataManager
{
private:
	static DataManager* instance;
	static std::mutex mtx;

private:
	int normalObjectCount = 0;
	int wrongObjectCount = 0;
	int carriageObjectCount = 0;

	HWND m_mainHandle = nullptr;

	DataManager() {}
	~DataManager() {}

public:
	static DataManager* GetInstance();


	void SetMainHandle(HWND mainHandle);

public:
	void IncreaseWrongCount();
	void IncreaseNormalCount();
	void CheckNormalCount(int* count);
};

