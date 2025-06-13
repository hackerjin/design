#include "stdafx.h"
#include "Packing.h"

#include "SkyrayUtil.h"

// -----------------------------------------------------------------------------------------------------

CPacking::CPacking()
{
	m_pBuffer = m_acDefaultBuffer;
	m_nBufferIndex = 0;
	m_nBufferSize = m_uDefaultBufferSize;
}

// -----------------------------------------------------------------------------------------------------

CPacking::~CPacking()
{
	if(m_pBuffer != m_acDefaultBuffer)
	{
		delete []m_pBuffer;
		m_pBuffer = NULL;
	}
}

// -----------------------------------------------------------------------------------------------------

void CPacking::Push(char nValue)
{
	AddData(&nValue, sizeof(char));
}

// -----------------------------------------------------------------------------------------------------

void CPacking::Push(short nValue)
{
	short			nShort;

	nShort = ::htons(nValue);
	AddData((char *)&nShort, sizeof(short));
}

// -----------------------------------------------------------------------------------------------------

void CPacking::Push(int nValue)
{
	int				nInt;

	nInt = ::htonl(nValue);
	AddData((char *)&nInt, sizeof(int));
}

// -----------------------------------------------------------------------------------------------------

void CPacking::Push(const char *pValue)
{
	if(pValue)
	{
		std::string			strString;

		strString = pValue;
		AddData(strString.c_str(), sizeof(char)*(strString.length()+1));
	}
}

// -----------------------------------------------------------------------------------------------------

void CPacking::Push(const wchar_t *pValue)
{
	if(pValue)
	{
		std::string			strString;

		Skyray::UTF8Encode(pValue, strString);
		AddData(strString.c_str(), sizeof(char)*(strString.length()+1));
	}
}

// -----------------------------------------------------------------------------------------------------

void CPacking::Push(const char *pData, UINT uDataLen)
{
	if(pData && (uDataLen>0))
		AddData(pData, uDataLen);
}

// -----------------------------------------------------------------------------------------------------

void CPacking::AddData(const char *pData, UINT uDataLen)
{
	UINT				nBufferSize;		

	nBufferSize = m_nBufferIndex+uDataLen;
	if(nBufferSize > m_nBufferSize)
	{
		UINT			nNewBufferLen = 2*nBufferSize;
		char			*pNewBuffer = new char[nNewBufferLen];

		memcpy_s(pNewBuffer, nNewBufferLen, m_pBuffer, m_nBufferIndex);
		if(m_pBuffer != m_acDefaultBuffer)
			delete []m_pBuffer;

		m_pBuffer = pNewBuffer;
		m_nBufferSize = nNewBufferLen;
	}

	memcpy_s(&m_pBuffer[m_nBufferIndex], (m_nBufferSize - m_nBufferIndex), pData, uDataLen);
	m_nBufferIndex += uDataLen;
}