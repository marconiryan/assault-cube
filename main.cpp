#include "pch.h"
#include <iostream>

using namespace winrt;
using namespace Windows::Foundation;


void ammo(int qntd_ammo);

int main()
{
 
    ammo(5000);

    return 0;
    
}
void ammo(int ammoValue) {
    DWORD procId = getProcessIDbyName(L"ac_client.exe");
    HMODULE BaseModuleAddress = getBaseModuleAddress(procId, L"ac_client.exe");
    DWORD BaseDynamicAddress = (DWORD)BaseModuleAddress + 0x17E0A8;
    HANDLE hproc = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
    std::vector<unsigned int> ammoOffsets = {0x364,0x14,0x0};
    DWORD ammoAddr = getDynamicAddress(hproc, BaseDynamicAddress, ammoOffsets);
    WriteProcessMemory(hproc, (BYTE*)ammoAddr, &ammoValue, sizeof(ammoValue), nullptr);


}