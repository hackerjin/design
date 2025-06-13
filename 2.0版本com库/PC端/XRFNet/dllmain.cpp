// dllmain.cpp : Implementation of DllMain.

#include "stdafx.h"
#include "resource.h"
#include "XRFNet_i.h"
#include "dllmain.h"
#include "dlldatax.h"

CXRFNetModule _AtlModule;

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
#ifdef _MERGE_PROXYSTUB
	if (!PrxDllMain(hInstance, dwReason, lpReserved))
		return FALSE;
#endif
	
	switch(dwReason)
	{
		case DLL_PROCESS_ATTACH:
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
			break;

	}
	
	if(L'\0' == g_acModulePath[0])
	{
		wchar_t			acModuleFileName[MAX_PATH] = L"\0";
		std::wstring	strModuleFileName;
		size_t			nFind;

		GetModuleFileName(hInstance, acModuleFileName, MAX_PATH-1);
		strModuleFileName = acModuleFileName;
		
		nFind = strModuleFileName.find_last_of(L'\\');
		if(std::wstring::npos != nFind) 
			strModuleFileName = strModuleFileName.substr(0, nFind+1);

		_tcscpy_s(g_acModulePath, MAX_PATH-1, strModuleFileName.c_str());
	}

	return _AtlModule.DllMain(dwReason, lpReserved); 
}
