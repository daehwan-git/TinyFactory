#include"pch.h"
#include <setupapi.h>
#include <devguid.h>
#include <iostream>
#include <string>
#include<vector>

#pragma comment(lib, "setupapi.lib")

class Device {

public:
    static std::vector<CString> ListUsbPorts();
};


