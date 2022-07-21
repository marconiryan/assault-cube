#include "pch.h"
DWORD getProcessIDbyName(const  wchar_t* processName) {
    HANDLE hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(PROCESSENTRY32);
    if (hProcSnap != INVALID_HANDLE_VALUE) {
        if (Process32First(hProcSnap, &processEntry)) {
            do {
                if (!wcsicmp(processEntry.szExeFile,processName)) {
                    DWORD hproc = processEntry.th32ProcessID;
                    CloseHandle(hProcSnap);
                    return hproc;
                }
            } while (Process32Next(hProcSnap, &processEntry));
        }
    }
    CloseHandle(hProcSnap);
    return 0;

}
HMODULE getBaseModuleAddress(DWORD processID, const  wchar_t* moduleName) {
    HANDLE hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processID);
    MODULEENTRY32 moduleEntry;
    moduleEntry.dwSize = sizeof(MODULEENTRY32);
    if (hModuleSnap != INVALID_HANDLE_VALUE) {
        if (Module32First(hModuleSnap, &moduleEntry)) {
            do {
                if (!_wcsicmp((moduleEntry.szModule), moduleName)) {
                    HMODULE modBaseAddr = (HMODULE)moduleEntry.modBaseAddr;
                    CloseHandle(hModuleSnap);
                    return modBaseAddr;
                }
            } while (Module32Next(hModuleSnap, &moduleEntry));

        }
    }
    CloseHandle(hModuleSnap);
    return 0;

}
DWORD getDynamicAddress(HANDLE hProcess, uintptr_t dynamicBaseAddress, std::vector<unsigned int> offsets) {
    DWORD dynamicAddress = dynamicBaseAddress;
    for (unsigned int i = 0; i < offsets.size(); i++) {
        
        ReadProcessMemory(hProcess, (BYTE*)dynamicAddress, &dynamicAddress, sizeof(dynamicAddress), 0);
        dynamicAddress = dynamicAddress + offsets[i];
        
    }
    return dynamicAddress;
}