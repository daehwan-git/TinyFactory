#pragma once
#include "pch.h"

class Carriage
{
private:
	CString ip;
	int maxCarriageCount = CURRENT_CARRIAGE;

public:
	bool InitCarriage(CString ip)
	{
		if (ip.IsEmpty())
		{
			return false;
		}

		this->ip = ip;
		
		if (ConnectToCarriage("/wait"))
		{
			return true;
		}
		return false;
	}

	void StartCarriage();
	void WaitCarriage();
	int GetCarriageCount() { return maxCarriageCount; }
	void SetCarriageCount(int count) { maxCarriageCount = count; }

private:
	bool ConnectToCarriage(CString command);
};

