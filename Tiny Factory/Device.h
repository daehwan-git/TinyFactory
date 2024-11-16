#include"pch.h"
#include <setupapi.h>
#include <devguid.h>
#include <iostream>
#include <string>
#include<vector>

#pragma comment(lib, "setupapi.lib")

class Device {

public:

    static std::vector<CString> ListUsbPorts()
    {
        std::vector<CString> portNames; 

        GUID usbGuid = GUID_DEVCLASS_USB;
        HDEVINFO hDevInfo = SetupDiGetClassDevs(&usbGuid, NULL, NULL, DIGCF_PRESENT);

        if (hDevInfo == INVALID_HANDLE_VALUE) {
            LogManager::GetInstance().WriteLog("연결된 USB 포트가 없음");
            return portNames;  
        }

        SP_DEVINFO_DATA devInfoData;
        devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

        for (DWORD i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &devInfoData); ++i) {
            DWORD dataType, dataSize;
            BYTE buffer[1024];

            // 장치 설명 가져오기
            if (SetupDiGetDeviceRegistryProperty(hDevInfo, &devInfoData, SPDRP_DEVICEDESC, &dataType, buffer, sizeof(buffer), &dataSize)) {
                std::wcout << L"Device Description: " << (wchar_t*)buffer << std::endl;
            }

            // 친숙한 이름을 포트 이름으로 저장
            if (SetupDiGetDeviceRegistryProperty(hDevInfo, &devInfoData, SPDRP_FRIENDLYNAME, &dataType, buffer, sizeof(buffer), &dataSize)) {
                CString name((wchar_t*)buffer);
                portNames.push_back(name);
            }
        }

        SetupDiDestroyDeviceInfoList(hDevInfo); 

        return portNames; 
    }
};


