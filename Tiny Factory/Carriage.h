#pragma once
#include "pch.h"

class Carriage
{
private:
	CString ip;
	int maxCarriageCount = CURRENT_CARRIAGE;

public:
	Carriage(CString ip)
	{
		this->ip = ip;
	}

	void StartCarriage();
	void WaitCarriage();
	int GetCarriageCount() { return maxCarriageCount; }
	void SetCarriageCount(int count) { maxCarriageCount = count; }

private:
	void ConnectToCarriage(CString command);
};

