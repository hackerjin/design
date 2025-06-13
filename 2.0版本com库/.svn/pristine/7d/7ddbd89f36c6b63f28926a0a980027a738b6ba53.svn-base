#include "stdafx.h"
#include "Unpacking.h"
#include "SkyrayUtil.h"
#include "Packing.h"

// -----------------------------------------------------------------------------------------------------

CUnpacking::CUnpacking(const char *pData, UINT nDataLen)
{
	m_pBuffer = new char[nDataLen];
	memcpy_s(m_pBuffer, nDataLen, pData, nDataLen);
	m_nBufferSize = nDataLen;
	m_nBufferIndex = 0;
}

// -----------------------------------------------------------------------------------------------------

CUnpacking::~CUnpacking()
{
	delete []m_pBuffer;
}

// -----------------------------------------------------------------------------------------------------

BOOL CUnpacking::Pop(char &nValue)
{
	if((m_nBufferIndex+sizeof(char)) > m_nBufferSize)
		return FALSE;

	memcpy_s(&nValue, sizeof(char), &m_pBuffer[m_nBufferIndex], sizeof(char));
	m_nBufferIndex += sizeof(char);
	return TRUE;
}

// -----------------------------------------------------------------------------------------------------

BOOL CUnpacking::Pop(short &nValue)
{
	if((m_nBufferIndex+sizeof(short)) > m_nBufferSize)
		return FALSE;
	
	short	nShort;

	memcpy_s((char *)&nShort, sizeof(short), &m_pBuffer[m_nBufferIndex], sizeof(short));
	m_nBufferIndex += sizeof(short);

	nValue = ::ntohs(nShort);
	return TRUE;
}

// -----------------------------------------------------------------------------------------------------

BOOL CUnpacking::Pop(int &nValue)
{
	if((m_nBufferIndex+sizeof(int)) > m_nBufferSize)
		return FALSE;
	
	int		nInt;

	memcpy_s((char *)&nInt, sizeof(int), &m_pBuffer[m_nBufferIndex], sizeof(int));
	m_nBufferIndex += sizeof(int);

	nValue = ::ntohl(nInt);
	return TRUE;
}

// -----------------------------------------------------------------------------------------------------

BOOL CUnpacking::Pop(char *pString, UINT &nLen)
{
	std::string		strString;
	UINT			nStringLen;
	bool			bReturn = FALSE;

	Skyray::UTF8Decode(&m_pBuffer[m_nBufferIndex], strString);
	nStringLen = strString.length() + 1;

	if(pString && (nLen >= nStringLen))
	{
		UINT		nCpyLen = sizeof(char)*nStringLen;

		memcpy_s(pString, nCpyLen, strString.c_str(), nCpyLen);
		
		bReturn = TRUE;
		m_nBufferIndex += nCpyLen;
	}

	nLen = nStringLen;
	return bReturn;
}

// -----------------------------------------------------------------------------------------------------

BOOL CUnpacking::Pop(wchar_t *pString, UINT &nLen)
{
	std::wstring	strString;
	UINT			nStringLen;
	bool			bReturn = FALSE;

	Skyray::UTF8Decode(&m_pBuffer[m_nBufferIndex], strString);
	nStringLen = strString.length() + 1;

	if(pString && (nLen >= nStringLen))
	{
		UINT		nCpyLen = sizeof(wchar_t)*nStringLen;

		memcpy_s(pString, nCpyLen, strString.c_str(), nCpyLen);

		bReturn = TRUE;
		m_nBufferIndex += nCpyLen;
	}

	nLen = nStringLen;
	return bReturn;
}

// -----------------------------------------------------------------------------------------------------

BOOL CUnpacking::PopBuffer(char *pData, UINT nDataLen)
{
	if((NULL == pData) || (0 == nDataLen))
		return FALSE;

	//if((m_nBufferIndex+nDataLen) >= m_nBufferSize)
	if((m_nBufferIndex+nDataLen) > m_nBufferSize)//修改Dpp100读取数据的错误
		return FALSE;

	memcpy_s(pData, nDataLen, &m_pBuffer[m_nBufferIndex], nDataLen);
	m_nBufferIndex += nDataLen;
	return TRUE;
}

// -----------------------------------------------------------------------------------------------------

NetLib::IPacking* CUnpacking::CreatePacking()
{
	NetLib::IPacking *pPacking = new CPacking();

	pPacking->Push(m_pBuffer, m_nBufferSize);
	return pPacking;
}