#pragma once

#include "pch.h"
#include<vector>

class FileManager
{

public:
	static FileManager& GetInstance()
	{
		static FileManager instance;
		return instance;
	}


	bool SaveFile(std::vector<CString> data);

};

