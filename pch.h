#pragma once
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <Psapi.h>
DWORD getProcessIDbyName(const  wchar_t* moduleName);
HMODULE getBaseModuleAddress(DWORD processID, const  wchar_t* moduleName);
DWORD getDynamicAddress(HANDLE hProcess, uintptr_t dynamicBaseAddress, std::vector<unsigned int> offsets);
