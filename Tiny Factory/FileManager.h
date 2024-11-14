#pragma once

#include "pch.h"
#include<vector>

class FileManager
{
private:
	static FileManager* instance;

public:

	static FileManager* GetInstance()
	{
		if (instance != nullptr)
		{
			return instance;
		}
		else {
			instance = new FileManager();
			return instance;
		}
	}


	bool SaveFile(std::vector<CString> data);

};

