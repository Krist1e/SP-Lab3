// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include "StringReplacer.h"

BOOL APIENTRY DllMain(HMODULE hModule,
                      const DWORD dwReason,
                      LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		{
			ReplaceString();
			break;
		}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		{
			ClearParams();
			break;
		}
	}
	return TRUE;
}
