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

	HWND mainHandle = nullptr;

	DataManager() {}
	~DataManager() {}

public:
	static DataManager* GetInstance()
	{
		if (instance == nullptr) {
			std::lock_guard<std::mutex> lock(mtx);
			if (instance == nullptr) {
				instance = new DataManager();
			}
		}
		return instance;
	}


	void SetMainHandle(HWND mainHandle)
	{
		this->mainHandle = mainHandle;
	}

public:
	void IncreaseWrongCount();
	void IncreaseNormalCount();
	void CheckNormalCount();
};

