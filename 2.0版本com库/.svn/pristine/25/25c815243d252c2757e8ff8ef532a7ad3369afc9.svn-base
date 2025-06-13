#include "SkyrayUtil.h"

#include <math.h>

namespace Skyray
{
	const std::string g_strDigitxA = "0123456789abcdefABCDEF";
	const std::wstring g_strDigitxU = L"0123456789abcdefABCDEF";

	// -----------------------------------------------------------------------------------------------------

	void UTF8Encode(const char *pInput, std::string &strOutput)
	{
		int				nOut;
		const WCHAR*	pInputTemp;
		char*			pTest;

		if((0 == pInput) || (0 == strlen(pInput)))
		{
			strOutput.erase(strOutput.begin(), strOutput.end());
			return;
		}

		WCHAR*			pBuffer; 

		nOut = MultiByteToWideChar(CP_ACP, 0, pInput, -1, NULL, 0);
		nOut++;
		pBuffer = new WCHAR[nOut];
		MultiByteToWideChar(CP_ACP, 0, pInput, -1, pBuffer, nOut);
		pInputTemp = pBuffer;
	
		nOut = WideCharToMultiByte(CP_UTF8, 0, pInputTemp, -1, NULL, 0, NULL, NULL);
		nOut++;
		pTest = new char[nOut];
		WideCharToMultiByte(CP_UTF8, 0, pInputTemp, -1, pTest, nOut, NULL, NULL);		
		strOutput = pTest;
		delete []pTest;

		delete []pBuffer;	
	}

	// -----------------------------------------------------------------------------------------------------

	void UTF8Encode(const wchar_t *pInput, std::string &strOutput)
	{
		int				nOut;
		char*			pTest;

		if((0 == pInput) || (0 == _tcslen(pInput)))
		{
			strOutput.erase(strOutput.begin(), strOutput.end());
			return;
		}

		nOut = WideCharToMultiByte(CP_UTF8, 0, pInput, -1, NULL, 0, NULL, NULL);
		nOut++;
		pTest = new char[nOut];
		WideCharToMultiByte(CP_UTF8, 0, pInput, -1, pTest, nOut, NULL, NULL);		
		strOutput = pTest;
		delete []pTest;
	}

	// -----------------------------------------------------------------------------------------------------

	void UTF8Decode(const char *pInput, std::string &strOutput)
	{
		int			nOut;
		WCHAR*		pBuffer; 
		char*		pTest;

		if((0 == pInput) || (0 == strlen(pInput)))
		{
			strOutput.erase(strOutput.begin(), strOutput.end());
			return;
		}

		nOut = MultiByteToWideChar(CP_UTF8, 0, pInput, -1, NULL, 0);
		nOut++;

		pBuffer = new WCHAR[nOut];
		MultiByteToWideChar(CP_UTF8, 0, pInput, -1, pBuffer, nOut);

		nOut = WideCharToMultiByte(CP_ACP, 0, pBuffer, -1, NULL, 0, NULL, NULL);
		nOut++;

		pTest = new char[nOut];
		nOut = WideCharToMultiByte(CP_ACP, 0, pBuffer, -1, pTest, nOut, NULL, NULL);		

		strOutput = pTest;
		delete []pTest;
		delete []pBuffer;
	}

	// -----------------------------------------------------------------------------------------------------

	void UTF8Decode(const char *pInput, std::wstring &strOutput)
	{
		int			nOut;
		WCHAR*		pBuffer; 

		if((0 == pInput) || (0 == strlen(pInput)))
		{
			strOutput.erase(strOutput.begin(), strOutput.end());
			return;
		}

		nOut = MultiByteToWideChar(CP_UTF8, 0, pInput, -1, NULL, 0);
		nOut++;

		pBuffer = new WCHAR[nOut];
		MultiByteToWideChar(CP_UTF8, 0, pInput, -1, pBuffer, nOut);

		strOutput = pBuffer;
		delete []pBuffer;
	}

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

	// -----------------------------------------------------------------------------------------------------

	void Ansi2Unicode(const char *pInput, std::wstring &strOutput)
	{
		int				nOut;
		WCHAR*			pTest;

		if((0 == pInput) || (0 == strlen(pInput)))
		{
			strOutput.erase(strOutput.begin(), strOutput.end());
			return;
		}

		nOut = MultiByteToWideChar(CP_ACP, 0, pInput, -1, NULL, 0);
		nOut++;

		pTest = new WCHAR[nOut];
		MultiByteToWideChar(CP_ACP, 0, pInput, -1, pTest, nOut);

		strOutput = pTest;
		delete []pTest;
	}

	// -----------------------------------------------------------------------------------------------------

	UINT GetHexValue(const char *pBuffer, int nLen)
	{
		std::string		strText;
		UINT			nDecNum;
		size_t			k;

		if(nLen < 0)
			nLen = strlen(pBuffer);

		strText = pBuffer;
		k = strText.find_first_not_of(g_strDigitxA);
		if(k == std::string::npos)
		{
			k = nLen - 1;
		}
		else
		{
			if(k > (size_t)(nLen-1))
				k = nLen-1;
		}
		nDecNum = 0;
		for(int i=0; k>=0; i++, k--)
		{
			switch(strText[i])
			{
				case 'a':
				case 'A': 
					nDecNum += _Pow_int(16, k)*10;
					break;
				case 'b':
				case 'B': 
					nDecNum += _Pow_int(16, k)*11;
					break;
				case 'c':
				case 'C': 
					nDecNum += _Pow_int(16, k)*12;
					break;
				case 'd':
				case 'D': 
					nDecNum += _Pow_int(16, k)*13;
					break;
				case 'e':
				case 'E': 
					nDecNum += _Pow_int(16, k)*14;
					break;
				case 'f':
				case 'F': 
					nDecNum += _Pow_int(16, k)*15;
					break;
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					nDecNum += _Pow_int(16, k)*(strText[i] - '0'); 
					break;
				default:
					return nDecNum;	
			}
		}

		return nDecNum;	
	}
	
	// -----------------------------------------------------------------------------------------------------

	UINT GetHexValue(const wchar_t *pBuffer, int nLen)
	{
		std::wstring	strText;
		UINT			nDecNum;
		size_t			k;

		if(nLen < 0)
			nLen = wcslen(pBuffer);

		strText = pBuffer;
		k = strText.find_first_not_of(g_strDigitxU);
		if(k == std::wstring::npos)
		{
			k = nLen - 1;
		}
		else
		{
			if(k > (size_t)(nLen-1))
				k = nLen-1;
		}
		nDecNum = 0;
		for(int i=0; k>=0; i++, k--)
		{
			switch(strText[i])
			{
				case L'a':
				case L'A': 
					nDecNum += _Pow_int(16, k)*10;
					break;
				case L'b':
				case L'B': 
					nDecNum += _Pow_int(16, k)*11;
					break;
				case L'c':
				case L'C': 
					nDecNum += _Pow_int(16, k)*12;
					break;
				case L'd':
				case L'D': 
					nDecNum += _Pow_int(16, k)*13;
					break;
				case L'e':
				case L'E': 
					nDecNum += _Pow_int(16, k)*14;
					break;
				case L'f':
				case L'F': 
					nDecNum += _Pow_int(16, k)*15;
					break;
				case L'0':
				case L'1':
				case L'2':
				case L'3':
				case L'4':
				case L'5':
				case L'6':
				case L'7':
				case L'8':
				case L'9':
					nDecNum += _Pow_int(16, k)*(strText[i] - L'0'); 
					break;
				default:
					return nDecNum;	
			}
		}

		return nDecNum;	
	}

	// -----------------------------------------------------------------------------------------------------

	void StringSplit(const std::string &str, std::string::value_type separator, std::vector<std::string> &strList)
	{
		std::string::const_iterator		it;
		std::string::const_iterator		itBegin;

		strList.clear();

		itBegin = str.begin(),
			it = itBegin;

		for(; it != str.end(); it++)
		{
			if(*it == separator)
			{
				strList.push_back(std::string(itBegin, it));
				itBegin = it + 1;
			}
		}			

		if(itBegin != it)
			strList.push_back(std::string(itBegin, it));		
	}
	
	// -----------------------------------------------------------------------------------------------------

	void StringSplit(const std::wstring &str, std::wstring::value_type separator, std::vector<std::wstring> &strList)
	{
		std::wstring::const_iterator		it;
		std::wstring::const_iterator		itBegin;

		strList.clear();

		itBegin = str.begin(),
			it = itBegin;

		for(; it != str.end(); it++)
		{
			if(*it == separator)
			{
				strList.push_back(std::wstring(itBegin, it));
				itBegin = it + 1;
			}
		}			

		if(itBegin != it)
			strList.push_back(std::wstring(itBegin, it));		
	}

	// -----------------------------------------------------------------------------------------------------

	void StringSplit(const std::string &str, const std::string &separator, std::vector<std::string> &strList)
	{
		std::string::size_type			nPos;
		std::string::size_type			nFind;
		std::string						temp;

		strList.clear();

		nPos = str.find_first_not_of(separator);
		while(std::string::npos != nPos)
		{
			nFind = str.find_first_of(separator, nPos);
			if(nFind == std::string::npos)
			{
				temp = str.substr(nPos, str.size()-nPos);
				strList.push_back(temp);
				break;
			}
			else 
			{
				temp = str.substr(nPos, nFind - nPos);
				strList.push_back(temp);
				nPos = str.find_first_not_of(separator, nFind);
			}
		}
	}
	
	// -----------------------------------------------------------------------------------------------------

	void StringSplit(const std::wstring &str, const std::wstring &separator, std::vector<std::wstring> &strList)
	{
		std::wstring::size_type			nPos;
		std::wstring::size_type			nFind;
		std::wstring					temp;

		strList.clear();

		nPos = str.find_first_not_of(separator);
		while(std::wstring::npos != nPos)
		{
			nFind = str.find_first_of(separator, nPos);
			if(nFind == std::wstring::npos)
			{
				temp = str.substr(nPos, str.size()-nPos);
				strList.push_back(temp);
				break;
			}
			else 
			{
				temp = str.substr(nPos, nFind - nPos);
				strList.push_back(temp);
				nPos = str.find_first_not_of(separator, nFind);
			}
		}
	}

	// -----------------------------------------------------------------------------------------------------

	void PickupString(const std::string &str, const std::string &strSub, std::vector<std::string> &strList)
	{
		std::string::size_type			nPos;
		std::string::size_type			nFind;
		std::string						temp;

		strList.clear();

		nPos = str.find_first_of(strSub);
		while(std::string::npos != nPos)
		{
			nFind = str.find_first_not_of(strSub, nPos);
			if(nFind == std::string::npos)
			{
				temp = str.substr(nPos, str.size()-nPos);
				strList.push_back(temp);
				break;
			}
			else 
			{
				temp = str.substr(nPos, nFind - nPos);
				strList.push_back(temp);
				nPos = str.find_first_of(strSub, nFind);
			}
		}
	}

	// -----------------------------------------------------------------------------------------------------

	void PickupString(const std::wstring &str, const std::wstring &strSub, std::vector<std::wstring> &strList)
	{
		std::wstring::size_type			nPos;
		std::wstring::size_type			nFind;
		std::wstring					temp;

		strList.clear();

		nPos = str.find_first_of(strSub);
		while(std::wstring::npos != nPos)
		{
			nFind = str.find_first_not_of(strSub, nPos);
			if(nFind == std::wstring::npos)
			{
				temp = str.substr(nPos, str.size()-nPos);
				strList.push_back(temp);
				break;
			}
			else 
			{
				temp = str.substr(nPos, nFind - nPos);
				strList.push_back(temp);
				nPos = str.find_first_of(strSub, nFind);
			}
		}
	}
}