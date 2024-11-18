#pragma once
#include "pch.h"

class Carriage
{
private:
	CString ip;


public:
	Carriage(CString ip)
	{
		this->ip = ip;
	}

	void StartCarriage();
	void StopCarriage();
	void ReturnCarriage();

private:
	void ConnectToCarriage(CString command);
};

