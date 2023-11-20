#pragma once

extern "C" __declspec(dllexport) void ReplaceString(const char* oldString, const char* newString);

void ReplaceString();

extern "C" __declspec(dllexport) void SetParams(const char* oldString, const char* newString);

void ClearParams();