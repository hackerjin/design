// stdafx.cpp : source file that includes just the standard includes
//	NetWorkDemo.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

#if (_ATL_VER < 0x0700)
#include <atlimpl.cpp>
#endif //(_ATL_VER < 0x0700)

// -----------------------------------------------------------------------------------------------------

void Unicode2Ansi(const WCHAR *pInput, std::string &strOutput)
{
	int				nOut;
	char*			pTest;

	if((0 == pInput) || (0 == wcslen(pInput)))
	{
		strOutput.erase(strOutput.begin(), strOutput.end());
		return;
	}

	nOut = WideCharToMultiByte(CP_ACP, 0, pInput, -1, NULL, 0, NULL, NULL);
	nOut++;

	pTest = new char[nOut];
	nOut = WideCharToMultiByte(CP_ACP, 0, pInput, -1, pTest, nOut, NULL, NULL);

	strOutput = pTest;
	delete []pTest;
}
