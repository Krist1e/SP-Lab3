#include "pch.h"
#include "StringReplacer.h"

bool IsRegionAccessible(const MEMORY_BASIC_INFORMATION& mbi)
{
	return mbi.State == MEM_COMMIT && mbi.Protect != PAGE_NOACCESS;
}

void ReplaceStringInRegion(const HANDLE handle, const char* oldString, const char* newString,
                           const size_t stringLen, const MEMORY_BASIC_INFORMATION& memInfo)
{
	const auto buffer = new char[memInfo.RegionSize];
	const LPVOID startAddress = memInfo.BaseAddress;

	if (!ReadProcessMemory(handle, startAddress, buffer, memInfo.RegionSize, nullptr))
		return;

	for (size_t i = 0; i < memInfo.RegionSize - stringLen; ++i)
		if (memcmp(buffer + i, oldString, stringLen) == 0)
			if (!WriteProcessMemory(handle, static_cast<PBYTE>(startAddress) + i, newString, stringLen, nullptr))
				return;

	delete[] buffer;
}


void ReplaceString(const char* oldString, const char* newString)
{
	if (oldString == nullptr || newString == nullptr)
		return;

	const size_t stringLen = strlen(oldString);

	if (stringLen == 0 || stringLen != strlen(newString))
		return;

	const HANDLE process = GetCurrentProcess();

	MEMORY_BASIC_INFORMATION memInfo;
	LPVOID regionAddress = nullptr;

	while (VirtualQuery(regionAddress, &memInfo, sizeof(memInfo)))
	{
		if (IsRegionAccessible(memInfo))
			ReplaceStringInRegion(process, oldString, newString, stringLen, memInfo);
		regionAddress = static_cast<PBYTE>(memInfo.BaseAddress) + memInfo.RegionSize;
	}
}

#pragma section("shrsec", shared)
__declspec(allocate("shrsec")) char sharedOldString[256] = {0};
__declspec(allocate("shrsec")) char sharedNewString[256] = {0};

void SetParams(const char* oldString, const char* newString)
{
	if (oldString == nullptr || newString == nullptr)
		return;

	strcpy_s(::sharedOldString, oldString);
	strcpy_s(::sharedNewString, newString);
}

bool IsParamsSet()
{
	return ::sharedOldString[0] != '\0' && ::sharedNewString[0] != '\0';
}

void ClearParams()
{
	::sharedOldString[0] = '\0';
	::sharedNewString[0] = '\0';
}

void ReplaceString()
{
	if (IsParamsSet())
	{
		ReplaceString(::sharedOldString, ::sharedNewString);
		ClearParams();
	}
}
