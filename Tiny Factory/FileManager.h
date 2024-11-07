#pragma once

#include "pch.h"

class FileManager
{

public:
	static FileManager& GetInstance()
	{
		static FileManager instance;
		return instance;
	}


	bool SaveFile(CString* data, CString path = DATASTORE_PATH);

};

