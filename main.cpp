#include "pch.h"
#include <iostream>

using namespace winrt;
using namespace Windows::Foundation;




int main()
{
    DWORD procId = getProcessIDbyName(L"ac_client.exe");
    HMODULE BaseModuleAddress = getBaseModuleAddress(procId, L"ac_client.exe");
    DWORD BaseDynamicAddress = (DWORD)BaseModuleAddress + 0x17E0A8;
    HANDLE hproc = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
    while (1) {
        WriteProcess(procId, BaseDynamicAddress, hproc, std::vector<unsigned int> { 0x364, 0x14, 0x0 }, 5000); // Infinite ammo
        WriteProcess(procId, BaseDynamicAddress, hproc, std::vector<unsigned int> { 0x364, 0x18, 0x0 }, 0); // No bolt action
    }
    return 0;
    
}
