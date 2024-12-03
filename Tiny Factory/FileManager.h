#pragma once

#include "pch.h"
#include<vector>

class FileManager
{
private:
	static FileManager* instance;

public:

	static FileManager* GetInstance();
	bool SaveFile(std::vector<CString> data);

};

